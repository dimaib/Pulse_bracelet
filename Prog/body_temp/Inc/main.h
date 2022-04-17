/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>

void connection(uint8_t *AP, uint8_t *PASS);
uint8_t send_wait_ok(uint8_t *str);
void build_tcp(uint8_t *addr, uint8_t *port);

/*Настройка устройства*/
#define DEBUG_ON																																			//Включение\отключение вывода информации в дебаг
#define STENBY_ON
#define SEND_SERVER_ON
/*Настройка устройства*/

/*Настройка пинов*/
#define WIFI_RES			GPIOA->ODR&=~(1<<4); HAL_Delay(500)															//сброс WI-FI
#define WIFI_ON				GPIOA->ODR|=(1<<4); HAL_Delay(500)															//включение WI-FI

#define WIFI_DIS			GPIOA->ODR&=~(1<<5); HAL_Delay(200)															//запрет WI-FI
#define WIFI_EN				GPIOA->ODR|=(1<<5); HAL_Delay(400)															//разрешение WI-FI

/*Настройка пинов*/
//#define BUFFER_TEMP_SIZE	10																													//размер буфера для хранения температуры за сутки
#define BUFFER_MAX 				60 																													//размер буфера приёма. Не должно превышать uint16_t
#define BUFFER_SEND				40																													//размер буфера для отправки сообщений на сервер

#define DELAY_OK_SEND			500																													//таймаут ожидания ответа OK или '>'

#define BUFF2_NULL				for(uint16_t i=0;i<BUFFER_MAX;i++) buf_uart2[i]=NULL				//обнуление буффера приёма по UART2

/*Объявление переменных-------------------------------------------------------*/

//объявление строковых констант
#define STR_OK						"OK!\r\n"
#define STR_ERROR					"ERROR!\r\n"
#define STR_START_INIT		"WIFI setup - START\r\n***********************\r\n"
#define STR_END_INIT			"***********************\r\nWIFI setup - END\r\n"
#define STR_WIFI_CON			"Connect WIFI\r\n"
#define STR_SET_IP				"IP addres OK!\r\n"
#define STR_BUILD_TCP			"Creating a TCP to the server\r\n"
#define STR_TCP_ERROR			"Creating TCP to the server ERROR\r\n"
#define STR_TCP_OK				"Creating TCP to the server OK\r\n"
#define STR_BUF_OVER			"Buffer is overloaded. Stop recive..\r\n"
#define CLIENT_OK					"TEMP_ACCEPT\r\n"																			//ответаная строка от сервера об успешном приёме данных
//объявление строковых констант


/*константы AT-команд для esp*/
#define ATE0  				(uint8_t*)"ATE0\r\n" 																						//отключить эхо
#define CWMODE 				(uint8_t*)"AT+CWMODE=1\r\n"																			//..
#define CIPMODE 			(uint8_t*)"AT+CIPMODE=0\r\n"																		//..
#define CIPMUX 				(uint8_t*)"AT+CIPMUX=0\r\n"																			//..
#define CWAUTOCONN 		(uint8_t*)"AT+CWAUTOCONN=0\r\n"																	//..
//#define CWJAP 				(uint8_t*)"AT+CWJAP=\"INTERPORT\",\"VlasovaNV65\"\r\n"				//подключиться к точке доступа
#define CONNECT_AP		(uint8_t*)"AT+CWJAP="																						//подключиться к точке доступа
#define GET_IP 				(uint8_t*)"AT+CIFSR\r\n"																				//узнать полученый IP адрес
#define BUILD_TCP 		(uint8_t*)"AT+CIPSTART=\"TCP\","																//установить TCP соединение
#define CLOSED_TCP 		(uint8_t*)"AT+CIPCLOSE\r\n"																			//разорвать TCP соединение
#define DISCON_AP			(uint8_t*)"AT+CWQAP\r\n"																				//отключиться от точки доступа
#define SEND_WIFI			(uint8_t*)"AT+CIPSEND="																					//отправить данные по TCP


/*константы AT-команд для esp*/
/*
#define WIFI_AP  			(uint8_t*)"dimaib"     																					//имя точки доступа
#define WIFI_PASS 		(uint8_t*)"23092309"   																					//пароль точки доступа
#define SERVER_ADDR		(uint8_t*)"192.168.31.184"																			//сетевой адрес сервера
#define SERVER_PORT		(uint8_t*)"7770"																								//сетевой порт сервера
*/
#define WIFI_AP  			(uint8_t*)"Mi A3"     																					//имя точки доступа
#define WIFI_PASS 		(uint8_t*)"20119288"   																					//пароль точки доступа
#define SERVER_ADDR		(uint8_t*)"192.168.43.200"																			//сетевой адрес сервера
#define SERVER_PORT		(uint8_t*)"7770"																								//сетевой порт сервера

#define START_BYTE		0xAA																														//стартовый байт при передачи по wifi 10101010
#define BUF_SEND_SIZE 19																															//размер посылки серверу

#define MAX_WIFI_ERROR	3																															//максимальное кол-во неудачных попыток подключения к точке доступа, после чего требуется перезагрузить WIFI
#define MAX_TCP_ERROR		3																															//максимальное кол-во неудачных попыток подключения к серверу, после чего требуется перезагрузить WIFI
#define MAX_TIME_WDT		3000																													//максимальное время молчания или бездействия сервера
#define MAX_TCP_DELAY		3000																													//максимальное время ожидания между неудачными подключениями TCP в мс. SysTick

/*Константы строк выдаваемые esp*/
#define WIFI_DISC			"WIFI DISCONNECT"																								//при успешном получении IP-адреса
#define WIFI_GOT_IP		"WIFI GOT IP"																										//при разрыве соединения
#define WIFI_OK				"OK"																														//ответ ОК
#define TCP_OK				"Connection succesful"																					//TCP соединение установлено
#define TCP_OFF				"CLOSED"																												//TCP соединение разорвано
#define TCP_OFF1			"COSED"																													//TCP соединение разорвано
#define TCP_OFF2			"link is not valid"																							//TCP соединение разорвано

#define TIMEOUT				"+CWJAP:1"																											//ошибка подключения по таймауту
#define NOPASS				"+CWJAP:2"																											//не верный пароль к точке доступа
#define NOAPP					"+CWJAP:3"																											//точки доступа не существует
#define READY_SEND		"> \r"																													//строка извещает о том, что пора отправлять
/*Константы строк выдаваемые esp*/

/*Буферы и переменные необходимые для работы UART*/
extern uint8_t dat2; 																																	//переменная для приёма байта по UART2
extern char buf_uart2[BUFFER_MAX]; 																										//буфер для приёма строки по UART2
extern uint16_t cout_uart2; 																													//счётчик принятых байт по UART2
/*Буферы и переменные необходимые для работы UART*/

extern uint8_t wifi_error;																														//счётчик неудачных попыток подключения к точке доступа
extern uint8_t tcp_error;																															//счётчик неудачных попыток подключения к серверу
extern uint16_t time_wdt;																															//счётчик молчания сервера
extern uint32_t	tcp_delay;																														//ожидание между неудачными подключениями TCP в мс. SysTick

extern uint16_t com_flags;		 																												//буфер команд для esp
/*[15][14][13][12][11][10][09][08][07][06][05][04][03][02][01][00]*/
/*Адреса размещения команд в регистре команд*/
#define COM_RS_WIFI		(1<<0)	//[00] COM_RS_WIFI 		- команда на сброс и настройку WIFI
#define COM_CON_WIFI	(1<<1)	//[01] COM_CON_WIFI 	- команда на подключение к WIFI
#define COM_WITE_WIFI	(1<<2)	//[02] COM_WAIT_WIFI 	- команда ожидания WIFI после получения IP адреса от точки доступа
#define COM_BUILD_TCP	(1<<3)	//[03] COM_BUILD_TCP 	- команда на создание TCP
#define COM_GET_IP		(1<<4)	//[04] COM_GET_IP 		- команда на запрос текущего IP адреса
/*Адреса размещения команд в регистре команд*/

extern uint16_t sys_flags;																														//системные флаги. Состояния системных событий и переферии
/*[15][14][13][12][11][10][09][08][07][06][05][04][03][02][01][00]*/
/*Адреса размещения флагов в регистре флагов*/
#define FLAG_OK				(1<<0)	//[00] FLAG_OK 				- флаг получения ОК. 
#define FLAG_WAIT_OK	(1<<1)	//[01] FLAG_WAIT_OK		- флаг ожидания ОК. Возводим этот флаг, когда требуется дождаться ответа от esp - ОК. Сбрасываем его, когда ОК получен
#define FLAG_GET_IP		(1<<2)	//[02] FLAG_GET_IP 		- флаг состояния WI-FI. 1 - подключено к точке доступа, 0 - не подключено к точке доступа
#define FLAG_TCP			(1<<3)	//[03] FLAG_TCP 			- флаг состояния TCP соединения с сервером
#define FLAG_RD_SEND	(1<<4)	//[04] FLAG_RD_SEND		- флаг получения приглашения на ввод
#define FLAG_WAITSEND (1<<5)	//[05] FLAG_WAITSEND	- флаг ожидания '>'. Возводим этот флаг, когда требуется дождаться ответа от esp - '>'. Сбрасываем его, когда '>' получен
#define FLAG_CLIENTOK (1<<6)	//[06] FLAG_CLIENTOK	-	флаг поднимается если от сервера пришёл ответ CLIENT_OK. Это ответ на удачный приём посылки
/*Адреса размещения флагов в регистре флагов*/

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_tx;
/*Объявление переменных-------------------------------------------------------*/


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WIFI_RST_Pin GPIO_PIN_4
#define WIFI_RST_GPIO_Port GPIOA
#define WIFI_EN_Pin GPIO_PIN_5
#define WIFI_EN_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
