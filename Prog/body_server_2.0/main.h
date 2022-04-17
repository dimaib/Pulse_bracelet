/*
Пакет телеметрии от устройства:

 ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
| 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 |
 ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 00		-	Стартовый бит							uint8_t
 01..04	-	UID устройства							uint32_t
 05..08	-	UID устройства							uint32_t
 09..12	-	UID устройства							uint32_t
 13..16	-	Температура								float
 17		-	Процент содержания кислорода в крови	uint8_t
 18..19	-	Верхнее давление						uint16_t
 20..21	-	Нижнее давление							uint16_t
 22..23	-	Пульс									uint16_t
 24..25	-	CRC16									uint16_t
*/




#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mutex>
#include <ctime>
#include <conio.h>

#ifndef MAIN_H
#define MAIN_H

using namespace std;

/*Переменные и константы*/
#define BUF_SIZE			1024								//размер буфера приёма
#define BUF_USER_SIZE		5								//максимальное кол-во подключений
#define SERVER_PORT			"7770"								//порт сервера для подключения клиентов

#define WDT_MS_MAX			10000								//Время таймаута неактивного соединения
#define WDT_SPEED			500									//задержка выполнения потока WDT. Сторожевой таймер проверяет состояние соединений с данной задержкой

#define DEBUG_CON_INFO		0									//включение/отключение вывода информации об очереди и буферах подключений
#define DEBUG_RESIVE_HEX	1									//включение/отключение вывода принятой информации от сокета в шеснадцатиричном формате

#define MAX_RFID			200									//максимальное кол-во карт для посылки в устройство
#define BUF_RECIV_SIZE		26									//размер пакета принимаемого от устройства

#define NAME_DB			"body_2.0"								//имя базы данных
#define HOST_DB			"localhost"								//хост базы данных
#define LOGIN_DB		"dimaib"								//логин базы данных
#define PASS_DB			"23092309"								//пароль базы данных

#define CLIENT_OK		"t_ok\r\n"								//ответаная строка клинту об успешном приёме данных

int buf_user_id[BUF_USER_SIZE] = { 0 };							//буфер хранения очереди подключений
int buf_user[BUF_USER_SIZE] = { 0 };							//буфер хранения подключений
//long buf_wdt_user[BUF_USER_SIZE] = { 0 };						//буфер хранения времени последней активности подключения. Для отслеживания неактивных подключений
int ClientCount = 0;											//текущее кол-во подключений														

/*Переменные и константы*/



/*Структуры для сокетов*/
SOCKET Connect;													//сокет для одобрения подключения
SOCKET Listen;													//сокет для прослушивания порта
mutex mut;														//структура мутекса, для синхронизации работы потоков

struct _application {											//массив структуры подключения устройств
	SOCKET Connections;											//массив активных подключений
	uint32_t uid[3];
	uint32_t buf_wdt_user;										//буфер хранения времени последней активности подключения. Для отслеживания неактивных подключений
	uint32_t flag_com_app;										//флаги команд устройству
	uint8_t wait_OK;											//ожидание ответа от устройства, что флаги команд дошли
	string Name;												//имя пациента
	uint8_t K_Puls;												//эталонное значение с танометра
	uint8_t K_PUp;												//эталонное значение с танометра
	uint8_t K_PDown;											//эталонное значение с танометра
}*application;
/*Структуры для сокетов*/

#include "function.h"
//#include "thread_function.h"
																															
/*Служебные функции*/
void debug_connect_buffer(uint8_t flag)																				//вывод отладочной информации об очереди подключений
{
	if (flag) {
		printf("buf_user_id:");	for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", buf_user_id[i]);
		printf("\r\nbuf_user:"); for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", buf_user[i]);
		printf("\r\nConnections:");	for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", (int)application[i].Connections);
		printf("\r\nbuf_wdt_user:"); for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", application[i].buf_wdt_user); printf("\r\n");
	}
}

int socket_init()																						//функция инициализации сокета
{
	for (int i = 0; i < BUF_USER_SIZE; i++) { buf_user_id[i] = i; buf_user[i] = -1; }					//инициализация очереди подключений
	WSADATA data;
	//WORD version = MAKEWORD(1, &data);
	int res = WSAStartup(MAKEWORD(1, &data), &data);
	//if (res != 0) { cout << "Ошибка инициализации Ws2_32.lib\r\n"; return 1; }
	struct addrinfo hints;
	struct addrinfo* result;
	application = (_application*)calloc(BUF_USER_SIZE, sizeof(_application));
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	getaddrinfo(NULL, SERVER_PORT, &hints, &result);
	Listen = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(Listen, result->ai_addr, (int)result->ai_addrlen);
	listen(Listen, SOMAXCONN);
	freeaddrinfo(result);
	return 0;
}

void datetostr(uint8_t* date,uint8_t *buf)														//перевод даты из формата yyyy-mm-dd в формат dd.mm.yyyy
{
	uint8_t s[5] = { 0 };
	uint8_t d = 0;
	uint8_t m = 0;
	uint16_t y = 0;
	for (int i = 0; i < 4; i++)s[i] = date[i]; s[4] = '\0'; y = atoi((char*)s);
	s[0] = date[5]; s[1] = date[6]; s[2] = '\0'; m = atoi((char*)s);
	s[0] = date[8]; s[1] = date[9]; s[2] = '\0'; d = atoi((char*)s);

	
	sprintf((char*)buf, "%d.%d.%d", d, m, y);
	printf("%s\r\n", buf);
}
/*Служебные функции*/
#endif
