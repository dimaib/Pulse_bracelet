#ifndef THREAD_FUNCTION_H
#define THREAD_FUNCTION_H

#include "main.h"
#include <mysql.h>
#include "function.h"

/*Функции потоков*/

void wotch_dog()																						//поток для отслеживания подвисших подключений и закрытия их
{
	for (;; Sleep(WDT_SPEED)) {
		mut.lock();
		hot_keys();																						//обработка горячих клавиш
		for (int i = 0; i < BUF_USER_SIZE; i++) {
			if (application[i].Connections && (clock() - application[i].buf_wdt_user > WDT_MS_MAX)) {	//если соединение существует и не обновлялось больше чем WDT_MS_MAX мс
				printf("Подключение #%d неактивно и будет закрыто\r\n", i);
				application[i].buf_wdt_user = 0;														//обнулить таймер
				for (uint8_t i = 0; i < 3; i++) application[i].uid[i] = 0;								//обнулить массив uid
				application[i].wait_OK = 0;
				application[i].flag_com_app = 0;
				closesocket(application[i].Connections);												//закрытие неактивного соединения по таймауту
				application[i].Connections = 0;															//обнулить соединение
				application[i].Name = "";
			}
		}
		mut.unlock();
	}
}

void send_app_command(int id,uint32_t flags)															//посылаем пакет с флагами команд устройству
{
	uint8_t packet[7] = { 0 };									//массив пакета
	packet[0] = 0xCC;											//стартовый бит для пакета с командами
	packet[1] = flags & 0xFF;									//байт флагов
	packet[2] = (flags >> 8) & 0xFF;							//байт флагов
	packet[3] = (flags >> 16) & 0xFF;							//байт флагов
	packet[4] = (flags >> 24) & 0xFF;							//байт флагов
	set_crc_in_byte(packet, 7);									//подсчёт crc16 пакета и вставка суммы в пакет
	send(application[id].Connections, (char*)packet, 7, NULL);	//шлём устройству пакет с командами
}

void synhro_application()																				//поток для синхронизации открытых соединений с устройствами
{
	for (;; Sleep(WDT_SPEED)) {
		mut.lock();
		for (int i = 0; i < BUF_USER_SIZE; i++) {														//просматриваем все подключения и ищем активные с активным uid-ом
			if (application[i].uid[0] && application[i].uid[1] && application[i].uid[2]) {				//если найден активный uid
				uint32_t flag_commands_app = database_read_flags(application[i].uid, -1);			//ищем uid в базе и загружаем флаги команд для устройства
				if (flag_commands_app != application[i].flag_com_app) {									//если флаги команд обновились, то требуется послать их серверу
					application[i].flag_com_app = flag_commands_app;
					application[i].wait_OK = 1;															//активируем таймаут на ответ устройства об удачном приёме
					send_app_command(i, application[i].flag_com_app);									//шлём устройству пакет с флагами команд
				}else if (application[i].wait_OK) {														//отслеживаем таймаут ответа
					application[i].wait_OK++;
					if (application[i].wait_OK > 20) {													//если устройство не отвечает:
						send_app_command(i, application[i].flag_com_app);								//повторяем отправку флагов команд
						application[i].wait_OK = 1;														//обнуляем таймаут
					}
				}
			}
		}
		mut.unlock();
	}
}

void SendMessageToClient(int ID)																		//функция потока, для обработки соединения
{
	uint8_t* buffer = new uint8_t[BUF_SIZE];
	for (;; Sleep(75)) {

		for (int i = 0; i < BUF_SIZE; i++) buffer[i] = '\0';
		int result = application[ID].Connections ? recv(application[ID].Connections, (char*)buffer, BUF_SIZE, NULL) : NULL;		//если ID подключения не равно нулю, то считываем данные, иначе разрываем соединение
		if (result != SOCKET_ERROR && result != NULL) {
			//for (uint8_t i = 0; i < 26; i++)printf("%x ", buffer[i]); printf("\r\n");
			/*Парсинг принятой строки*/
			if (buffer[0] == 0xAA) {																	//если стартовый байт 0xAA (10101010)
				if (valid_crc16(buffer, BUF_RECIV_SIZE)) {
					//uint32_t uid[3] = { 0 };															//переменная для хранения UIDa устройства
					mut.lock();
					float temp = 0.0;																	//переменная для хранения температуры пациента
					uint8_t SpO2 = 0;
					uint16_t PUp = 0;
					uint16_t Pdown = 0;
					uint16_t Puls = 0;
					memcpy(application[ID].uid, buffer + 1, sizeof(float) * 3);							//копирование uid
					memcpy(&temp, buffer + 13, sizeof(float));											//копирование температуры в массив
					memcpy(&PUp, buffer + 18, sizeof(uint16_t));										//копирование верхнего давления в массив
					SpO2 = buffer[17];																	//копирование содержания кислорода в крови в массив
					memcpy(&Pdown, buffer + 20, sizeof(uint16_t));										//копирование нижнего давления в массив
					memcpy(&Puls, buffer + 22, sizeof(uint16_t));										//копирование пульса в массив
					//Puls -= 40;
					PUp = (Puls - application[ID].K_Puls > -50) ? Puls + abs(application[ID].K_Puls - application[ID].K_PUp) : 0;
					Pdown = (Puls - application[ID].K_Puls > -50) ? Puls + abs(application[ID].K_Puls - application[ID].K_PDown) : 0;
					send(application[ID].Connections, CLIENT_OK, strlen(CLIENT_OK), NULL);
					send(application[ID].Connections, CLIENT_OK, strlen(CLIENT_OK), NULL);
					database_read_flags(application[ID].uid, ID);
					printf("%s\ttemp=%.2f\tpuls=%d\tOxygen=%d\tPUp=%d\tPDown=%d\r\n", application[ID].Name, temp, Puls, SpO2, PUp, Pdown);
					if (temp<100&&database_init()&&Puls>10) {											//подключение к базе данных
						char buf_time[20] = { 0 };														//буфер для хранения даты и времени
						char buf_query[500] = { 0 };													//буфер для хранения строки запроса к базе данных
						datetime_now_to_bd(buf_time);													//формирование строки времени под формат базы данных
						sprintf(buf_query,
							"INSERT INTO `body_2.0`.`telemetry` (`date_time`, `uid0`, `uid1`, `uid2`, `temp`, `oxygen`, `puls`, `pressure_up`, `pressure_down`) VALUES ('%s', '%ld', '%ld', '%ld', '%.2f', '%d', '%d', '%d', '%d');"
							, buf_time, application[ID].uid[0], application[ID].uid[1], application[ID].uid[2], temp, SpO2, Puls, PUp, Pdown);			//формирование строки запроса в БД на добавление новой записи															//вывод сформированной строки
						if (mysql_query(conn, buf_query)) printf("%s\r\n", mysql_error(conn));			//если не удалось отправить строку в БД
						mysql_close(conn);																//закрыть соединение с БД
						//send(application[ID].Connections, CLIENT_OK,strlen(CLIENT_OK),NULL);
					}
					mut.unlock();
				}
				else printf("Контрольная сумма пакета не верна!\r\n");									//если посчитанная контрольная сумма не совпадает с принятой
			}
			else if (strstr((char*)buffer, "OK_COM")) {													//если от устройства пришёл ответ об удачно принятых флагах
				application[ID].wait_OK = 0;
				application[ID].flag_com_app = 0;
				mut.lock();
				if (database_init()) {																//подключение к базе данных
					char buf_query[500] = { 0 };													//буфер для хранения строки запроса к базе данных
					sprintf(buf_query, "UPDATE application SET commands = 0 WHERE (uid0=%lu AND uid1=%lu AND uid2=%lu);",
						application[ID].uid[0], application[ID].uid[1], application[ID].uid[2]);	//формирование строки запроса в БД на обнуление команд устройству														//вывод сформированной строки
					if (mysql_query(conn, buf_query)) printf("%s\r\n", mysql_error(conn));			//если не удалось отправить строку в БД
					printf("OK command #%d\r\n",ID);
					mysql_close(conn);																//закрыть соединение с БД
				}
				mut.unlock();
			}
			/*Парсинг принятой строки*/

#if DEBUG_RESIVE_HEX																					//вывод информации в шестнадцатиричном формате
			//printf("%d:\t", ID); for (int i = 0; i<BUF_RECIV_SIZE; i++) printf("%x ", buffer[i]); printf("\r\n");//вывод строки посимвольно пока не достигнем символа NULL
#else																									//вывод информации в строковом формате
			printf("%d:\t%s", ID, buffer);
			//cout << ID <<" - " << buffer;
#endif

			application[ID].buf_wdt_user = clock();
		}
		else {
			mut.lock();
			ClientCount--;
			//printf("Соединение разорвано #%d\t\t\t\t-=%d=-\r\n", ID, ClientCount);
			application[ID].Connections = NULL;
			application[ID].buf_wdt_user = 0;
			for (int i = 0; i < BUF_USER_SIZE; i++) {
				if (buf_user[i] == ID) {
					for (int ii = i; ii < BUF_USER_SIZE - 1; ii++) buf_user[ii] = buf_user[ii + 1];
				}
			}
			for (int i = BUF_USER_SIZE - 1; i; i--) buf_user_id[i] = buf_user_id[i - 1];
			buf_user_id[0] = ID;
			debug_connect_buffer(DEBUG_CON_INFO);														//вывод отладочной информации об очереди и буферах подключений
			mut.unlock();
			break;
		}
	}
	delete[] buffer;
}
/*Функции потоков*/

#endif // !THREAD_FUNCTION_H
