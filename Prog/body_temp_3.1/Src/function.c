#include "main.h"
#include "function.h"
#include "stdio.h"
#include "string.h"
#include "Si7021_driver.h"
#include "tim.h"
#include "dac.h"
#include "max30100_for_stm32_hal.h"
#include "i2c.h"

/*Глобальные переменные телеметрии человека*/
float temp=0.0;																															//Глобальная переменная температуры тела
uint8_t SpO2=0;																															//Глобальная переменная процента содержания кислорода в крови
uint16_t PUp=0;																															//Глобальная переменная верхнего значения давления
uint16_t Pdown=0;																														//Глобальная переменная нижнего значения давления
uint16_t Puls=0;																														//Глобальная переменная пульса
/*Глобальные переменные телеметрии человека*/

char *wav;																																	//ссылка на массив для передачи wav массива в прерывание
uint32_t size_wav=0;																												//размер переданного массива
uint32_t wav_byte=0;																												//инкремент для воспроизведения следующего байта массива
uint8_t wav_valume=0;																												//громкость воспроизведения 0..15

void init_perif()
{
	GPIOA->ODR|=(1<<5);																								//выключение TPA301
	WIFI_OFF;
	TEMP_OFF;
	uint8_t wdt_si7021=0;
	while (rst_Si7021()!=0) {																					//инициализация датчика температуры
		wdt_si7021++;
		if(wdt_si7021>10) NVIC_SystemReset();														//если кол-во попыток чтения датчика превышено, то перезагружаем ядро контроллера
		HAL_Delay(200);
	}
	while (!MAX30100_Init(&hi2c2, &huart1)) HAL_Delay(200);						//инициализация датчика пульса и кислорода
	wifi_on();																												//первоначальная инициализация и включение wifi модуля
	NVIC_EnableIRQ(USART1_IRQn); USART1->CR1|=USART_CR1_RXNEIE;       //разрешение прерывания по приёму данных UART1. Прерывание для debug
	
}

void play_wav(const char *wav_arr/*массив wav файла*/, uint32_t size_wave /*размер wav массива*/, uint8_t volume/*громкость воспроизведения 0..15*/) //воспроизвести массив wav файла
{
	wav=(char *)wav_arr;
	size_wav=size_wave;
	wav_byte=0;
	wav_valume=volume;
	//останавливаем все прерывания и таймеры
	NVIC_DisableIRQ(USART2_IRQn);																							//остановить прерывания по UARTу wifi
	HAL_TIM_Base_Stop_IT(&htim4);																							//остановить прерывание таймера 4
	//останавливаем все прерывания и таймеры
	HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0);									//обнуляем ЦАП
	HAL_DAC_Start(&hdac,DAC_CHANNEL_1);																				//включаем оцифровку ЦАП
//	for(uint16_t i=0;i<2000;i++){
//		HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,i);
//		HAL_Delay(1);
//	}
	GPIOA->ODR&=~(1<<5);																											//включаем микросхему TPA301
	HAL_Delay(10);
	HAL_TIM_Base_Start_IT(&htim2);																						//включаем прерывание таймера 2
}


void debug(uint8_t *str, uint8_t is_it)
{
#ifdef DEBUG_ON
	if(is_it){
		HAL_UART_Transmit_IT(&huart1,str,strlen((char*)str));
	}else{
		HAL_UART_Transmit(&huart1,str,strlen((char*)str),100);
	}
#endif
	//printf("%s",str);
}

uint8_t send_wait_ok(uint8_t *str)																						//функция отправки сообщения в WIFI с последующим ожиданием ответа ОК
{
	uint32_t iwait_ok=0;																												//если данный инкремент больше тысячи, то не дождались ОК
	sys_flags|=FLAG_WAIT_OK;																										//говорим, что требуется ожидать сообщения OK от WIFI 
	sys_flags&=~FLAG_OK;																												//сбрасываем системный флаг ОК
	HAL_UART_Transmit(&huart2,str,strlen((char*)str),100);											//посылаем команду из буфера команд в WIFI
	debug(str,0);
	while(sys_flags&FLAG_WAIT_OK){ 																							//ожидаем сообщения OK. Поднятия флага в системном регистре
		iwait_ok++;																																//если данный инкремент больше тысячи, то не дождались ОК
		if(iwait_ok>=DELAY_OK_SEND) break;
		HAL_Delay(1);
	}
	
	if(iwait_ok<DELAY_OK_SEND){
		sys_flags&=~FLAG_OK;																											//если дождались, то сбрасываем флаг ОК
		debug((uint8_t*)STR_OK,0);
		return 1;
	}else {
		debug((uint8_t*)STR_ERROR,0);
		return 0;
	}
}

void send(uint8_t *str)
{
	HAL_UART_Transmit(&huart2,str,strlen((char*)str),100);											//посылаем команду из буфера команд в WIFI
}

void send_server(uint8_t *str, uint8_t len)																		//посылка сообщения на сервер
{
	if(sys_flags&FLAG_TCP){
		uint32_t iwait_ok=0;																											//если данный инкремент больше тысячи, то не дождались '>'
		sys_flags|=FLAG_WAITSEND;																									//говорим, что требуется ожидать сообщения OK от WIFI 
		sys_flags&=~FLAG_RD_SEND;																									//сбрасываем системный флаг ОК
		uint8_t i=0;
		char buf[BUFFER_SEND]={0};																								//буфер для формирования строки команды
		//char buf1[BUFFER_SEND]={0};																								//буфер для копирования переданной строки

		sprintf(buf,"%s%d\r\n",SEND_WIFI,len);																		//посылаем в модуль команду на передачу данных с размером буфера
		send((uint8_t*)buf);																											//посылаем в модуль команду на передачу данных с размером буфера
		while(!(sys_flags&FLAG_RD_SEND)){ 																				//ожидаем сообщения '>'. Поднятия флага в системном регистре
			iwait_ok++;																															//если данный инкремент больше тысячи, то не дождались '>'
			if(iwait_ok>=DELAY_OK_SEND) break;
			HAL_Delay(10);
		}
		for(uint8_t i=0;i<BUFFER_SEND;i++) buf[i]='\0';
		for(i=0;i<len;i++) buf[i]=str[i];																					//копирование переданной строки в буфер до символа '\0'
		if(iwait_ok<=DELAY_OK_SEND){ 																							//если дождались, то сбрасываем флаг '>'
			sys_flags&=~FLAG_RD_SEND;																								//сбрасываем флаг ожидания 																		
			HAL_UART_Transmit(&huart2,(uint8_t*)buf,BUF_SEND_SIZE,100);							//посылаем серверу пакет из BUF_SEND_SIZE байт
			HAL_Delay(10);
		}else 
			send((uint8_t*)"+++\r\n");																							//если не дождались '>', то закрываем диалог ввода 
	}
}
uint16_t crc16(uint8_t *data, uint16_t len)																		//вычисление crc16 для контрольной суммы пакетов передачи и приёма по wifi
{
    uint16_t crc = 0xFFFF;
    while (len--){
        crc ^= *data++ << 8;
        for (uint8_t i = 0; i < 8; i++) crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

void build_packet(uint32_t *uid,float temp)																		//функция формирует пакет для посылки и посылает его на сервер
{
	//if(temp<100)temp=Temp_serv;
	//PUp=Pup;
	Pdown=Pdown;
	Puls=Puls_serv;
	uint8_t send_arrey[BUF_SEND_SIZE]={0};
	send_arrey[0]=START_BYTE;
	memcpy(send_arrey+1,uid, sizeof(uint32_t)*3);              									//копирование uid
	memcpy(send_arrey+13,&temp, sizeof(float));             										//копирование температуры в массив
	send_arrey[17]=SpO2;
	memcpy(send_arrey+18,&PUp, sizeof(uint16_t));             									//копирование верхнего давления в массив
	memcpy(send_arrey+20,&Pdown, sizeof(uint16_t));             								//копирование нижнего давления в массив
	memcpy(send_arrey+22,&Puls, sizeof(uint16_t));             								//копирование пульса в массив
	uint16_t crc=crc16(send_arrey,BUF_SEND_SIZE-3);															//вычисление crc16 подготовленного пакета
	memcpy(send_arrey+24,&crc, sizeof(uint16_t));         											//копирование температуры в массив
//	for(uint8_t i=0;i<BUF_SEND_SIZE;i++){
//		uint8_t bbb[100]={0}; sprintf((char*)bbb,"%x ",send_arrey[i]); debug(bbb,0);
//	}
//	debug((uint8_t*)"\r\n",0);
	send_server((uint8_t*)send_arrey,BUF_SEND_SIZE);
}

uint8_t wifi_init()																														//функция инициализации и настройки WIFI модуля
{
	wifi_error=0;	tcp_error=0;																									//сброс счётчика неудачных подключений к WIFI и серверу
	uint8_t *set_wifi[]={ATE0,CWMODE,CIPMODE,CIPMUX};														//массив команд необхолдимых для настройки WIFI
	cout_uart2=0; 
	BUFF2_NULL;
	WIFI_OFF; WIFI_ON;
  WIFI_RES; WIFI_SET;																													//сброс WIFI	
	debug((uint8_t*)STR_START_INIT,0);
	for(uint8_t i=0;i<sizeof(set_wifi)/4;i++)	{																	//цикл перебора команд для настройки WIFI
		uint8_t err_init=0;
		while(!send_wait_ok(set_wifi[i])){																				//если не получаем ответ ОК, то
			err_init++;																															//пробуем ещё несколько раз инициализировать
			if(err_init>5) return 0;																								//модуль wifi, если нет, то выходим
		}
	}			
	debug((uint8_t*)STR_END_INIT,0);
	
	com_flags&=~COM_RS_WIFI;																										//сброс флага команды на сброс WIFI
	com_flags|=COM_CON_WIFI;																										//возведение флага команды на подключение к WIFI
	return 1;
}

void connection(uint8_t *ap, uint8_t *pass)																		//подключение к точке доступа
{
	tcp_delay=0;
	sys_flags&=~(FLAG_OK|FLAG_WAIT_OK|FLAG_TCP|FLAG_GET_IP);										//сбрасываем флаги ОК, ожидания ОК, флаг TCP и флаг подключения к AP
	char buf[255]={0};																													//буффер для соединения строк
	sprintf(buf,"%s\"%s\",\"%s\"\r\n", CONNECT_AP,ap,pass);											//соединение команды, точки доступа и пароля в строку
	send_wait_ok(DISCON_AP);	HAL_Delay(100);																		//отключиться от точки доступа и подождать 100мс
	send((uint8_t *)buf);																												//команда на подключение к точке доступа
	debug((uint8_t*)buf,0);
	debug((uint8_t*)STR_WIFI_CON,0);
	com_flags&=~COM_CON_WIFI;																										//сброс флага команды на подключение к WIFI
	wifi_error++;
	if(wifi_error>MAX_WIFI_ERROR){ 																							//если привысили максимальное кол-во попыток подключения, то сбрасываем WIFI
		/*тут уходим в сон!*/
		com_flags|=COM_RS_WIFI;
	}
}

void build_tcp(uint8_t *addr, uint8_t *port)																	//создание TCP соединения
{
	delay_send=0;
	debug((uint8_t*)STR_BUILD_TCP,0);
	tcp_delay=0;
	sys_flags&=~(FLAG_OK|FLAG_WAIT_OK|FLAG_TCP);																//сбрасываем флаги ОК, ожидания ОК и флаг TCP
	char buf[255]={0};																													//буффер для соединения строк
	sprintf(buf,"%s\"%s\",%s\r\n", BUILD_TCP,addr,port);												//соединение команды, адреса сервера и порта сервера
	HAL_Delay(100);
	send(CLOSED_TCP);	HAL_Delay(300);																						//разорвать все соединения TCP и подождать 300мс
	send((uint8_t *)buf);																												//команда на подключение к точке доступа
	com_flags&=~COM_BUILD_TCP;
	tcp_error++;
	if(tcp_error>MAX_TCP_ERROR){																								//если привысили максимальное кол-во попыток подключения, то сбрасываем WIFI
		/*тут уходим в сон!*/
		tcp_error=0;
		com_flags|=COM_CON_WIFI;
	}
}

void send_temp(uint8_t sendtemp)																							//если соединение установлено, то посылаем на сервер температуру и ждём ответ
{
	float temp=0.0f;
	uint32_t uid[3]={*(uint32_t *)(UID_BASE),																		//массив уникального номера устройства
	*(uint32_t *)(UID_BASE + 0x04),*(uint32_t *)(UID_BASE + 0x08)};							//массив уникального номера устройства
	for(uint8_t i=0;i<5;i++) temp+=r_single_Si7021();														//делаем 5 измерений температуры
	temp/=5;																																		//вычисляем среднее из пяти измерений
	char buf[100]={0};

	uint8_t i=0;
	for(i=0;i<3;i++){
		uint8_t wait_client_ok=0;
		sys_flags&=~FLAG_CLIENTOK;
		build_packet(uid,sendtemp?temp:100.0);												//посылаем пакет на сервер
		while(!(sys_flags&FLAG_CLIENTOK)){																				//крутимся пока флаг равен нулю
			wait_client_ok++;
			if (wait_client_ok>30) break;																						//если прошло больше 3000 секунд и подтверждение от сервера не пришло то выходим и повторяем попытку
			HAL_Delay(100);
		}
		if(sys_flags&FLAG_CLIENTOK){																							//если ответ CLIENT_OK получен, то выходим из функции
			sys_flags&=~FLAG_CLIENTOK;
			//debug("client_ok\r\n",0);
			delay_send=0;
			return;
		}
		//debug("resend client_ok\r\n",0);
	}
	//debug("no client_ok\r\n",0);
	com_flags|=COM_BUILD_TCP;																										//если CLIENT_OK не получен после 3х попыток отправки на сервер, то сбрасываем TCP подключение
}

void debug_uid()
{
	uint8_t buf[50]={0};
	uint32_t uid[3]={*(uint32_t *)(UID_BASE),																		//массив уникального номера устройства
	*(uint32_t *)(UID_BASE + 0x04),*(uint32_t *)(UID_BASE + 0x08)};							//массив уникального номера устройства
	sprintf((char*)buf,"UID=%d %d %d \r\n",uid[0],uid[1],uid[2]);
	debug(buf,0);
}

void commands(uint8_t enable)																																//функция обработки системных команд 
{
	if(enable){
		if((sys_flags&FLAG_GET_IP)&&!(sys_flags&FLAG_TCP)){													//если зависли и не можем подключиться к серверу
			tcp_error++;
			if (tcp_error>15) com_flags|=COM_BUILD_TCP;
		}else tcp_error=0;
		
		if(com_flags&COM_RS_WIFI) {																									//если есть команда на сброс WIFI
			while(!wifi_init());																			
		}else if(com_flags&COM_CON_WIFI) {																					//подключение к точке доступа
			connection(WIFI_AP,WIFI_PASS);										
		}else if(com_flags&COM_WITE_WIFI){																					//ожидание полной готовности WIFI после получения IP адреса от точки доступа. Требуется из-за особенностей модуля!
			sys_flags|=FLAG_WAIT_OK;																									//говорим, что требуется ожидать сообщения OK от WIFI, тк после получения IP модуль некоторое время ещё занят!
			sys_flags&=~FLAG_OK;																											//сбрасываем системный флаг ОК
			send((uint8_t*)"AT\r\n");																									//на всякий случай шлём АТ для получения ОК, для предотвращения зависания, если не требуется WIFI  вернёт busy p..
			uint8_t wait_OK_tmp=0;
			while(!(sys_flags&FLAG_OK)){ 																							//после получения IP адреса, следует дождаться полной готовности модуля и прихода ОК
				HAL_Delay(5);
				wait_OK_tmp++;
				if(wait_OK_tmp>200){
					wait_OK_tmp=0;
					debug((uint8_t*)"wifi_busy=(\r\n",0);
					send((uint8_t*)"AT\r\n");
				}
			}
			debug((uint8_t*)STR_SET_IP,0);
			sys_flags&=~FLAG_OK;																											//если дождались, то сбрасываем флаг ОК
			com_flags&=~COM_WITE_WIFI;																								//говорим, что дождались WIFI, сбросом флага ожидания
			com_flags|=COM_BUILD_TCP;
		}else if(com_flags&COM_BUILD_TCP){																					//создание TCP соединения
			if(HAL_GetTick()-tcp_delay>MAX_TCP_DELAY||tcp_error==0)										//если задержка между подключениями TCP выдержена, или если tcp_error=0, что значит сервер разорвал подключение
				build_tcp(SERVER_ADDR,SERVER_PORT);
		}else if(sys_flags&FLAG_TCP&&com_flags&COM_SEND_ID){												//если соединение с сервером установлено
			com_flags&=~COM_SEND_ID;
			send_temp(0);
		}else if(sys_flags&FLAG_TCP){																								//если соединение с сервером установлено
			if(sys_flags&FLAG_REC_COM){
				sys_flags&=~FLAG_REC_COM;
				HAL_Delay(300);
				send_server((uint8_t*)"OK_COM",6);																			//отвечаем серверу об удачном приёме флагов команд
				send_server((uint8_t*)"OK_COM",6);																			//отвечаем серверу об удачном приёме флагов команд
				send_server((uint8_t*)"OK_COM",6);																			//отвечаем серверу об удачном приёме флагов команд
				
			}
	#ifdef SEND_SERVER_ON
			delay_send++;
			if(delay_send>10)	{delay_send=0; send_temp(1);}
	#endif //SEND_SERVER_ON
			
			
	#ifdef STENBY_ON		
			//stendby_rtc();
	#endif //STENBY_ON
		}else if(sys_flags==0&&com_flags==0){
			//com_flags|=COM_RS_WIFI;
			com_flags|=COM_CON_WIFI;
		}
			
		/*обработка команд от сервера*/
		if(com_serv&SERV_PLAY1){
			com_serv&=~SERV_PLAY1;
			//GPIOD->ODR^=(1<<0);
			play_wav(wav_ism_puls,sizeof(wav_ism_puls),20);
		}
		/*обработка команд от сервера*/
		
		HAL_Delay(300);
	}
}

void wifi_on()																																	//первоначальное включение wifi
{
	WIFI_OFF;
	WIFI_RES;
	NVIC_EnableIRQ(USART2_IRQn); USART2->CR1|=USART_CR1_RXNEIE;       //разрешение прерывания по приёму данных UART2. Прерывание для WIFI
	HAL_Delay(200);
	WIFI_ON;
	WIFI_SET;
}
