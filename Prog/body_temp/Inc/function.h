#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "main.h"
#include "stdio.h"

void debug(uint8_t *str, uint8_t is_it);																			//вывод сообщений в дебаг
uint8_t send_wait_ok(uint8_t *str);																						//функция отправки сообщения в WIFI с последующим ожиданием ответа ОК
void send(uint8_t *str);																											//отправка данных в WIFI модуль
void send_server(uint8_t *str, uint8_t len);																	//посылка сообщения на сервер
uint8_t wifi_init(void);																											//функция инициализации и настройки WIFI модуля
void connection(uint8_t *ap, uint8_t *pass);																	//подключение к точке доступа
void build_tcp(uint8_t *addr, uint8_t *port);																	//создание TCP соединения
void commands(void);																													//функция обработки системных команд 
void build_packet(uint32_t *uid,float temp);																	//функция формирует пакет для посылки и посылает его на сервер
void stendby_rtc(void);																												//функция вводит контроллер в stenby режим
void debug_uid(void);

#endif	//FUNCTIONS_H
