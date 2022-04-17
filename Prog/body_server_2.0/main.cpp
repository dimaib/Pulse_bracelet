#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mutex>
#include <ctime>

/*пользовательские заголовки*/
//#include <mysql.h>																	//файл с API mysql баз данных
#include "database.h"																	//файл с функциями для работы с базой данных
#include "function.h"																	//файл со служебными функциями
#include "thread_function.h"															//файл с подпрограммами потоков
/*пользовательские заголовки*/

#include "main.h"

#pragma comment(lib, "Ws2_32.lib")														//Необходимо, чтобы линковка происходила с DLL-библиотекой. Для работы с сокетам

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	setlocale(LC_CTYPE, "russian");														//для правильного вывода ресского текста в консоль
	system("title Сервер обработки body temp");											//установить заголовок окна
	if (!database_init()) {																//если база данных не инициализирована
		printf("Ошибка инициализации базы данных!\r\n"); 
		system("pause");  
		return 0; 
	} else {
		printf("База данных успешно инициализирована!\r\n");
		mysql_close(conn);
	}

	if (socket_init()) {																//инициализация сетевого протокола
		printf("Ошибка инициализации сетевого протокола, программа будет завершена!\r\n");
		return 1;
	}
																
	thread func_thread(wotch_dog);														//создание потока сторожевого таймера
	func_thread.detach();																//отсоединение потока от функции
	thread func_synhro(synhro_application);												//создание потока синхронизации открытых соединений с устройством
	func_synhro.detach();																//отсоединение потока от функции


	char buf[100] = {0};																//буффер ответа клиенту на запрос подключения
	printf("Сервер запущен!\r\n");
	char buf_send[32];	

	for (;; Sleep(75)) {
		if (Connect = accept(Listen, NULL, NULL)) {										//одобрение входящего подключения
			mut.lock();																	//блокировка потока
			ClientCount++;																//прибавляем кол-во клиентов
			printf("Пользователь подключен #%d\t\t\t-=%d=-\r\n", buf_user_id[0], ClientCount);
			application[buf_user_id[0]].Connections = Connect;							//ID подключения
			application[buf_user_id[0]].buf_wdt_user = clock();							//время создания подключения, для сторожевого таймера
			sprintf_s(buf_send,"con_ok\r\n");
			send(application[buf_user_id[0]].Connections, buf_send,(int)strlen(buf_send),NULL);	//ответ клиенту об удачном подключении
			thread func_thread(SendMessageToClient, buf_user_id[0]);					//создание потока нового клиента
			func_thread.detach();														//отсоединение потока от функции
			for (int i = 0; i < BUF_USER_SIZE; i++) {									//обработка очереди подключений
				if (buf_user[i] == -1) { buf_user[i] = buf_user_id[0]; break; }			//поиск свободной позиции в массиве и помещаем туда номер подключения
			}
			for (int i = 0; i < BUF_USER_SIZE - 1; i++) buf_user_id[i] = buf_user_id[i + 1];//удаление нулевого элемента и смещение очереди влево 
			buf_user_id[BUF_USER_SIZE - 1] = -1;
			debug_connect_buffer(DEBUG_CON_INFO);										//вывод отладочной информации об очереди и буферах подключений
			mut.unlock();																//разблокировка потока
		}
	}
	return 0;
}