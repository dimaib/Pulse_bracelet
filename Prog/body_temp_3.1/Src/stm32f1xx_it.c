/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "function.h"
#include "max30100_for_stm32_hal.h"
#include "dac.h"
#include "hr_spo2_math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/*Глобальные переменные и массивы*/
uint8_t dat2=0; 																											//переменная для приёма байта по UART2
char buf_uart2[BUFFER_MAX]={0}; 																			//буфер для приёма строки по UART2
uint16_t cout_uart2=0; 																								//счётчик принятых байт по UART2

uint16_t com_flags=1; 																								//буфер команд для esp
uint16_t sys_flags=0;																									//системные флаги. Состояния системных событий и переферии
uint32_t com_serv=0;																									//системные флаги. Состояния системных событий и переферии

uint8_t wifi_error=0;																									//счётчик неудачных попыток подключения к точке доступа
uint8_t tcp_error=0;																									//счётчик неудачных попыток подключения к серверу
uint16_t time_wd=0;																										//счётчик молчания сервера
uint32_t tcp_delay=0;																									//ожидание между неудачными подключениями TCP в мс. SysTick
extern uint16_t wdt_wifi;


extern char *wav;																											//массив с wav файлом
extern uint32_t size_wav;																							//размер wav массива
extern uint32_t wav_byte;																							//инкремент текущего воспроизводимого байта wav
extern uint8_t wav_valume;																						//коэф. домножения wav байта, для DAC. �?ли просто громкость воспроизведения

uint32_t wdt_com=0;																											//общий сторожевой таймер


volatile int i=0;
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
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
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
		//GPIOD->ODR^=(1<<0);
		//HAL_Delay(50);
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
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
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM2 global interrupt.
  */
uint8_t flg=0;
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	//прерывание таймера, для воспроизведения wav звуковой дорожки
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
	
	HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,wav[wav_byte]*wav_valume);		//кладём в ЦАП значение из массива wav
	wav_byte++;
	if(wav_byte>3000&&flg==0){
		wav_byte=0;
		flg=1;
	}
	if(wav_byte>=size_wav){																										//если проиграли массив до конца
		GPIOA->ODR|=(1<<5);																											//выключаем микросхему TPA301
		wav_byte=0;
		flg=0;
		HAL_DAC_Stop(&hdac,DAC_CHANNEL_1);																			//остановить оцефровку ЦАП
		HAL_TIM_Base_Stop_IT(&htim2);																						//остановить прерывание таймера 2
		HAL_TIM_Base_Start_IT(&htim4);																					//остановить прерывание таймера 4
		NVIC_EnableIRQ(USART2_IRQn); USART2->CR1|=USART_CR1_RXNEIE;       			//разрешение прерывания по приёму данных UART2. Прерывание для WIFI
	}
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */
	wdt_com++;
	if(wdt_com>WDT_COM_TIM) NVIC_SystemReset();
	if(!(GPIOB->IDR&(1<<12))) {
		MAX30100_InterruptCallback();
	}
  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
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
	if(USART2->SR & USART_SR_RXNE){ 																									//Если прерывание вызвано по приёму USART2
		dat2=USART2->DR;																																//считать принятый символ
		if(!((dat2==0x0D || dat2==0x0A) && cout_uart2==0)){
			buf_uart2[cout_uart2++]=dat2;																									//добавляем принятый символ в буффер приёма
		}
		if(cout_uart2>1&&cout_uart2<BUFFER_MAX-1){
			/*парсинг принятой строки*/
			if(buf_uart2[cout_uart2-2]==0x0D && buf_uart2[cout_uart2-1]==0x0A){						//если принятый символ не конец стоки и не перевод карретки, то
				wdt_wifi=0;
				buf_uart2[cout_uart2]='\0';																									//добавить нулевой символ, для корректной обработки строки																//выводим принятое
				//printf("%s\r\n",buf_uart2);
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
					com_flags|=COM_SEND_ID;
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
				}else if(strstr(buf_uart2,"+IPD,7")) {
					uint8_t packet[7]={0};
					for(uint8_t i=0;i<7;i++) packet[i]=buf_uart2[i+7];	//парсинг принятого пакета с флагами команд
					uint16_t crc_=(packet[6]<<8)|packet[5];							//парсинг принятого пакета с флагами команд
					if(crc_== crc16(packet,5)){													//если прислан правильный пакет и контрольная сумма совпадает
						sys_flags|=FLAG_REC_COM;													//поднимаем флаг, что надо отвечать серверу о принятом пакете
						com_serv=packet[4];																//переносим полученые данные в флаги команд
						com_serv=(com_serv<<8)|packet[3];
						com_serv=(com_serv<<8)|packet[2];
						com_serv=(com_serv<<8)|packet[1];
						debug((uint8_t*)"Recive new command\r\n",1);
					}
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
