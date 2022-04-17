/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "usart.h"
//#include "usbd_cdc_if.h"
#include "function.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/*Глобальные переменные и массивы*/
uint8_t dat2=0; 																											//переменная для приёма байта по UART2
char buf_uart2[BUFFER_MAX]={0}; 																			//буфер для приёма строки по UART2
uint16_t cout_uart2=0; 																								//счётчик принятых байт по UART2

uint16_t com_flags=1; 																								//буфер команд для esp
uint16_t sys_flags=0;																									//системные флаги. Состояния системных событий и переферии

uint8_t wifi_error=0;																									//счётчик неудачных попыток подключения к точке доступа
uint8_t tcp_error=0;																									//счётчик неудачных попыток подключения к серверу
uint16_t time_wd=0;																										//счётчик молчания сервера
uint32_t tcp_delay=0;																									//ожидание между неудачными подключениями TCP в мс. SysTick
/*Глобальные переменные и массивы*/
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles RTC interrupt through EXTI lines 17, 19 and 20.
  */
void RTC_IRQHandler(void)
{
  /* USER CODE BEGIN RTC_IRQn 0 */

  /* USER CODE END RTC_IRQn 0 */
  HAL_RTC_AlarmIRQHandler(&hrtc);
  /* USER CODE BEGIN RTC_IRQn 1 */

  /* USER CODE END RTC_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	/*Приём данных от esp8266*/
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	if(USART2->ISR & USART_ISR_RXNE){ 																								//Если прерывание вызвано по приёму USART2
		dat2=USART2->RDR;																																//считать принятый символ
		if(!((dat2==0x0D || dat2==0x0A) && cout_uart2==0)){
			buf_uart2[cout_uart2++]=dat2;																									//добавляем принятый символ в буффер приёма
		}
		if(cout_uart2>1&&cout_uart2<BUFFER_MAX-1){
			/*парсинг принятой строки*/
			if(buf_uart2[cout_uart2-2]==0x0D && buf_uart2[cout_uart2-1]==0x0A){						//если принятый символ не конец стоки и не перевод карретки, то
				buf_uart2[cout_uart2]='\0';																									//добавить нулевой символ, для корректной обработки строки																//выводим принятое
				if(!(strstr(buf_uart2,"Recv ")||strstr(buf_uart2,"SEND OK")||
					strstr(buf_uart2,"busy p...")))																						//если в сообщении есть нежелательные строки для вывода
						buf_uart2[cout_uart2]='\0';
				cout_uart2=0; 																															//обнуляем счётчик принятых символов. т.е. заканчиваем приём			
				if(strstr(buf_uart2,"OK\r\n") && sys_flags&FLAG_WAIT_OK){										//если приняли ОК
					sys_flags&=~FLAG_WAIT_OK;
					sys_flags|=FLAG_OK;
				}else if(strstr(buf_uart2,WIFI_GOT_IP)){
					sys_flags|=FLAG_GET_IP;										 																//Подключено к точке доступа
					com_flags|=COM_WITE_WIFI;																									//команда на ожидание полной готовности WIFI
					wifi_error=0;	tcp_error=0;																								//сброс счётчика неудачных подключений к WIFI и серверу
				}else if(strstr(buf_uart2,"+CWLAP:")){
					debug((uint8_t*)buf_uart2,1);
					cout_uart2=0;
				}else if(strstr(buf_uart2,WIFI_DISC)){
					sys_flags&=~FLAG_GET_IP;																									//Соединение с точкой доступа разорванно
					if(!(com_flags&COM_CON_WIFI))	com_flags=COM_CON_WIFI;											//если событие разрыва с точкой доступа произошло не вовремя подключения, то пытаемся переконектиться
				}else if(strstr(buf_uart2,TCP_OK)) {
					debug((uint8_t*)STR_TCP_OK,1);
					sys_flags|=FLAG_TCP;																											//TCP соединение создано
					wifi_error=0;	tcp_error=0;																								//сброс счётчика неудачных подключений к WIFI и серверу
				}else if(strstr(buf_uart2,TCP_OFF)||strstr(buf_uart2,TCP_OFF1)||strstr(buf_uart2,TCP_OFF2)){
					debug((uint8_t*)STR_TCP_ERROR,1);
					sys_flags&=~FLAG_TCP;																											//TCP соединение разорвано
					com_flags|=COM_BUILD_TCP;
					tcp_delay=HAL_GetTick();
				}else if(strstr(buf_uart2,NOPASS)){																					//если неверный пароль для точки доступа
					debug((uint8_t*)"Invalid password! Reboot device...\r\n",1);
				}else if(strstr(buf_uart2,NOAPP)){																					//если данной точки доступа не существует
					debug((uint8_t*)"Point does not exist! Reconnect...\r\n",1);
					com_flags=COM_CON_WIFI;
					sys_flags|=FLAG_OK;
				}else if(strstr(buf_uart2,TIMEOUT)){																				//если слишком большое время ожидания
					debug((uint8_t*)"Timeout error! Reconnect...\r\n",1);
					com_flags=COM_CON_WIFI;
					sys_flags|=FLAG_OK;			
				}else if(strstr(buf_uart2,CLIENT_OK)){																			//если приняты данные с сервера
					sys_flags|=FLAG_CLIENTOK;
				}
				BUFF2_NULL;																																	//обнуляем буфер приёма
			}else if(sys_flags&FLAG_WAITSEND&&cout_uart2==2&&buf_uart2[0]=='>'&&buf_uart2[1]==' '){//если пришло приглашение на ввод даннх >
				cout_uart2=0;																																//обнуляем счётчик принятых символов. т.е. заканчиваем приём
				BUFF2_NULL;																																	//обнуляем буфер приёма
				sys_flags&=~FLAG_WAITSEND;
				sys_flags|=FLAG_RD_SEND;
			}
			/*парсинг принятой строки*/
		}else if(cout_uart2>=BUFFER_MAX){
			BUFF2_NULL;
			cout_uart2=0;
			debug((uint8_t*)STR_BUF_OVER,1);
		}
	}

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
