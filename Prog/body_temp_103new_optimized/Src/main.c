/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "dac.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "function.h"	
#include "Si7021_driver.h"
#include "printfdebug.h"
#include "max30100_for_stm32_hal.h"
#include "hr_spo2_math.h"


float Puls_serv=0.0;
float Temp_serv=0.0;
uint8_t delay_send=0;
uint8_t math_start=0;																		//флаг того, что массивы пульса и кислорода заполнены, пора их обсчитывать
extern float32_t chanel_ir[BLOCK_SIZE];									//массив с показаниями пульса
extern float32_t chanel_red[BLOCK_SIZE];								//массив с показаниями кислорода

uint16_t wdt_wifi=0;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

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
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{
        micros *=(SystemCoreClock / 1000000) / 5;
        while (micros--);
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
	
	//WIFI_DIS;	
	//GPIOA->ODR|=(1<<1);
	DelayMicro(1);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	UART_HandleTypeDef huar;
	huar=huart1;
	while(1){
		HAL_UART_Transmit(&huar,"123\r\n",5,100);
		HAL_Delay(100);
	}
	//GPIOA->ODR|=(1<<5);																								//выключение TPA301
	//WIFI_EN;
	hr_filter_init();																									//инициализация фильтров для вычисления пульса и кислорода в крови
	//while (rst_Si7021()!=0) HAL_Delay(200);														//инициализация датчика температуры
	while (!MAX30100_Init(&hi2c2, &huart1)) HAL_Delay(200);						//инициализация датчика пульса и кислорода
	//wifi_on();																												//первоначальная инициализация и включение wifi модуля

	NVIC_EnableIRQ(USART1_IRQn); USART1->CR1|=USART_CR1_RXNEIE;       //разрешение прерывания по приёму данных UART1. Прерывание для debug
	
	debug((uint8_t*)"Start system\r\n",0);
	char buf[100]={0};
	//sprintf(buf,"%d\r\n",MAX30100_ReadReg(MAX30100_REVISION));
	//debug((uint8_t*)buf,0);
	
  while (1)
  {	
		UART_HandleTypeDef huar;
		huar=huart1;
		
		HAL_UART_Transmit(&huart1,"123\r\n",5,100);
		if(math_start){															//если массив с данными пульса и кислорода накопили и TCP соединение создано
			
			hr_math_(chanel_red,chanel_ir);																//обработать массивы пульса и кислорода

			math_start=0;																									//сбросить флаг 
			sprintf(buf,"Temp: %.1f\tPuls: %d\tSpO2=%d\r\n",r_single_Si7021(),(uint16_t)Puls_serv,SpO2);
			//debug((uint8_t*)buf,0);		
		}
		
		wdt_wifi++;																											//сторожевой таймер вайфая, сбрасывается, если был приём от вайфая
		if(wdt_wifi>=30) {wdt_wifi=0; sys_flags=0; com_flags=0;}				//если в течении некоторого времени не было приёма от вайфая, то сбрасываем все флаги состояний, что инициализирует перезагрузку вайфая
		commands(0);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
