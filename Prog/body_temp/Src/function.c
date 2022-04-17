#include "main.h"
#include "function.h"
#include "stdio.h"
#include "string.h"
#include "Si7021_driver.h"
#include "rtc.h"

//extern float temp_buf[BUFFER_TEMP_SIZE];																			//массив для хранения показаний температуры за сутки

void debug(uint8_t *str, uint8_t is_it)
{
#ifdef DEBUG_ON
	if(is_it){
		HAL_UART_Transmit_IT(&huart1,str,strlen((char*)str));
	}else{
		HAL_UART_Transmit(&huart1,str,strlen((char*)str),100);
	}
#endif
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
			send((uint8_t*)buf);
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
	uint8_t send_arrey[BUF_SEND_SIZE]={0};
	send_arrey[0]=START_BYTE;
	memcpy(send_arrey+1,uid, sizeof(uint32_t)*3);              										//копирование uid
	memcpy(send_arrey+13,&temp, sizeof(float));             										//копирование температуры в массив
	for(uint8_t i=1;i<14;i++) if(send_arrey[i]=='\0') send_arrey[i]=0xFF;
	uint16_t crc=crc16(send_arrey,16);																					//вычисление crc16 подготовленного пакета
	memcpy(send_arrey+17,&crc, sizeof(uint16_t));         											//копирование температуры в массив
	send_server((uint8_t*)send_arrey,BUF_SEND_SIZE);
}

uint8_t wifi_init()																														//функция инициализации и настройки WIFI модуля
{
	wifi_error=0;	tcp_error=0;																									//сброс счётчика неудачных подключений к WIFI и серверу
	uint8_t *set_wifi[]={ATE0,CWMODE,CIPMODE,CIPMUX};														//массив команд необхолдимых для настройки WIFI
	cout_uart2=0; 
	BUFF2_NULL;
  WIFI_RES; WIFI_ON;																													//сброс WIFI	
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
		com_flags|=COM_RS_WIFI;
	}
}

void send_temp()																															//если соединение установлено, то посылаем на сервер температуру и ждём ответ
{
	float temp=0.0f;
	uint8_t buf[20]={0};
	uint32_t uid[3]={*(uint32_t *)(UID_BASE),																		//массив уникального номера устройства
	*(uint32_t *)(UID_BASE + 0x04),*(uint32_t *)(UID_BASE + 0x08)};							//массив уникального номера устройства
	for(uint8_t i=0;i<5;i++) temp+=r_single_Si7021();														//делаем 5 измерений температуры
	temp/=5;																																		//вычисляем среднее из пяти измерений
	sprintf((char*)buf,"temperature=%.2f\r\n",r_single_Si7021());
	debug(buf,0);
	uint8_t i=0;
	for(i=0;i<3;i++){
		uint8_t wait_client_ok=0;
		sys_flags&=~FLAG_CLIENTOK;
		build_packet(uid,r_single_Si7021());																			 //посылаем пакет на сервер
		while(!(sys_flags&FLAG_CLIENTOK)){																				//крутимся пока флаг равен нулю
			wait_client_ok++;
			if (wait_client_ok>30) break;																						//если прошло больше 3000 секунд и подтверждение от сервера не пришло то выходим и повторяем попытку
			HAL_Delay(100);
		}
		if(sys_flags&FLAG_CLIENTOK){																							//если ответ CLIENT_OK получен, то выходим из функции
			sys_flags&=~FLAG_CLIENTOK;
			//debug("client_ok\r\n",0);
			return;
		}
		//debug("resend client_ok\r\n",0);
	}
	//debug("no client_ok\r\n",0);
	com_flags|=COM_BUILD_TCP;																										//если CLIENT_OK не получен после 3х попыток отправки на сервер, то сбрасываем TCP подключение
}


void stendby_rtc()																														//функция вводит контроллер в stenby режим
{
	//Сброс времени RTC на стандартные значения 01:00:00
	RTC_TimeTypeDef sTime = {0};
  sTime.Hours = 1;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) Error_Handler();
	//Сброс времени RTC на стандартные значения 01:00:00
	
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);																					//подготовка к stendby режиму
	HAL_PWR_EnterSTANDBYMode();																									//ввод контроллера в stenby режим. Пробуждение после срабатывания прерывания прерывания от RTC
}

void debug_uid()
{
	uint8_t buf[50]={0};
	uint32_t uid[3]={*(uint32_t *)(UID_BASE),																		//массив уникального номера устройства
	*(uint32_t *)(UID_BASE + 0x04),*(uint32_t *)(UID_BASE + 0x08)};							//массив уникального номера устройства
	sprintf((char*)buf,"UID=%d %d %d \r\n",uid[0],uid[1],uid[2]);
	debug(buf,0);
}

void commands()																																//функция обработки системных команд 
{
	HAL_Delay(100);
	if(com_flags&COM_RS_WIFI) {																									//если есть команда на сброс WIFI
		while(!wifi_init());																			
	}else if(com_flags&COM_CON_WIFI) {																					//подключение к точке доступа
		connection(WIFI_AP,WIFI_PASS);										
	}else if(com_flags&COM_WITE_WIFI){																					//ожидание полной готовности WIFI после получения IP адреса от точки доступа. Требуется из-за особенностей модуля!
		sys_flags|=FLAG_WAIT_OK;																									//говорим, что требуется ожидать сообщения OK от WIFI, тк после получения IP модуль некоторое время ещё занят!
		sys_flags&=~FLAG_OK;																											//сбрасываем системный флаг ОК
		send((uint8_t*)"AT\r\n");																									//на всякий случай шлём АТ для получения ОК, для предотвращения зависания, если не требуется WIFI  вернёт busy p..
		while(!(sys_flags&FLAG_OK)) HAL_Delay(1);																	//после получения IP адреса, следует дождаться полной готовности модуля и прихода ОК
		debug((uint8_t*)STR_SET_IP,0);
		sys_flags&=~FLAG_OK;																											//если дождались, то сбрасываем флаг ОК
		com_flags&=~COM_WITE_WIFI;																								//говорим, что дождались WIFI, сбросом флага ожидания
		com_flags|=COM_BUILD_TCP;
	}else if(com_flags&COM_BUILD_TCP){																					//создание TCP соединения
		if(HAL_GetTick()-tcp_delay>MAX_TCP_DELAY||tcp_error==0)										//если задержка между подключениями TCP выдержена, или если tcp_error=0, что значит сервер разорвал подключение
			build_tcp(SERVER_ADDR,SERVER_PORT);
	}else if(sys_flags&FLAG_TCP){																								//если соединение с сервером установлено
#ifdef SEND_SERVER_ON
		send_temp();
#endif //SEND_SERVER_ON
		
		
#ifdef STENBY_ON		
		stendby_rtc();
#endif //STENBY_ON
	}
}
