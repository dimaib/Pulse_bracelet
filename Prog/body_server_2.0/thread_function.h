#ifndef THREAD_FUNCTION_H
#define THREAD_FUNCTION_H

#include "main.h"
#include <mysql.h>
#include "function.h"

/*������� �������*/

void wotch_dog()																						//����� ��� ������������ ��������� ����������� � �������� ��
{
	for (;; Sleep(WDT_SPEED)) {
		mut.lock();
		hot_keys();																						//��������� ������� ������
		for (int i = 0; i < BUF_USER_SIZE; i++) {
			if (application[i].Connections && (clock() - application[i].buf_wdt_user > WDT_MS_MAX)) {	//���� ���������� ���������� � �� ����������� ������ ��� WDT_MS_MAX ��
				printf("����������� #%d ��������� � ����� �������\r\n", i);
				application[i].buf_wdt_user = 0;														//�������� ������
				for (uint8_t i = 0; i < 3; i++) application[i].uid[i] = 0;								//�������� ������ uid
				application[i].wait_OK = 0;
				application[i].flag_com_app = 0;
				closesocket(application[i].Connections);												//�������� ����������� ���������� �� ��������
				application[i].Connections = 0;															//�������� ����������
				application[i].Name = "";
			}
		}
		mut.unlock();
	}
}

void send_app_command(int id,uint32_t flags)															//�������� ����� � ������� ������ ����������
{
	uint8_t packet[7] = { 0 };									//������ ������
	packet[0] = 0xCC;											//��������� ��� ��� ������ � ���������
	packet[1] = flags & 0xFF;									//���� ������
	packet[2] = (flags >> 8) & 0xFF;							//���� ������
	packet[3] = (flags >> 16) & 0xFF;							//���� ������
	packet[4] = (flags >> 24) & 0xFF;							//���� ������
	set_crc_in_byte(packet, 7);									//������� crc16 ������ � ������� ����� � �����
	send(application[id].Connections, (char*)packet, 7, NULL);	//��� ���������� ����� � ���������
}

void synhro_application()																				//����� ��� ������������� �������� ���������� � ������������
{
	for (;; Sleep(WDT_SPEED)) {
		mut.lock();
		for (int i = 0; i < BUF_USER_SIZE; i++) {														//������������� ��� ����������� � ���� �������� � �������� uid-��
			if (application[i].uid[0] && application[i].uid[1] && application[i].uid[2]) {				//���� ������ �������� uid
				uint32_t flag_commands_app = database_read_flags(application[i].uid, -1);			//���� uid � ���� � ��������� ����� ������ ��� ����������
				if (flag_commands_app != application[i].flag_com_app) {									//���� ����� ������ ����������, �� ��������� ������� �� �������
					application[i].flag_com_app = flag_commands_app;
					application[i].wait_OK = 1;															//���������� ������� �� ����� ���������� �� ������� �����
					send_app_command(i, application[i].flag_com_app);									//��� ���������� ����� � ������� ������
				}else if (application[i].wait_OK) {														//����������� ������� ������
					application[i].wait_OK++;
					if (application[i].wait_OK > 20) {													//���� ���������� �� ��������:
						send_app_command(i, application[i].flag_com_app);								//��������� �������� ������ ������
						application[i].wait_OK = 1;														//�������� �������
					}
				}
			}
		}
		mut.unlock();
	}
}

void SendMessageToClient(int ID)																		//������� ������, ��� ��������� ����������
{
	uint8_t* buffer = new uint8_t[BUF_SIZE];
	for (;; Sleep(75)) {

		for (int i = 0; i < BUF_SIZE; i++) buffer[i] = '\0';
		int result = application[ID].Connections ? recv(application[ID].Connections, (char*)buffer, BUF_SIZE, NULL) : NULL;		//���� ID ����������� �� ����� ����, �� ��������� ������, ����� ��������� ����������
		if (result != SOCKET_ERROR && result != NULL) {
			//for (uint8_t i = 0; i < 26; i++)printf("%x ", buffer[i]); printf("\r\n");
			/*������� �������� ������*/
			if (buffer[0] == 0xAA) {																	//���� ��������� ���� 0xAA (10101010)
				if (valid_crc16(buffer, BUF_RECIV_SIZE)) {
					//uint32_t uid[3] = { 0 };															//���������� ��� �������� UIDa ����������
					mut.lock();
					float temp = 0.0;																	//���������� ��� �������� ����������� ��������
					uint8_t SpO2 = 0;
					uint16_t PUp = 0;
					uint16_t Pdown = 0;
					uint16_t Puls = 0;
					memcpy(application[ID].uid, buffer + 1, sizeof(float) * 3);							//����������� uid
					memcpy(&temp, buffer + 13, sizeof(float));											//����������� ����������� � ������
					memcpy(&PUp, buffer + 18, sizeof(uint16_t));										//����������� �������� �������� � ������
					SpO2 = buffer[17];																	//����������� ���������� ��������� � ����� � ������
					memcpy(&Pdown, buffer + 20, sizeof(uint16_t));										//����������� ������� �������� � ������
					memcpy(&Puls, buffer + 22, sizeof(uint16_t));										//����������� ������ � ������
					//Puls -= 40;
					PUp = (Puls - application[ID].K_Puls > -50) ? Puls + abs(application[ID].K_Puls - application[ID].K_PUp) : 0;
					Pdown = (Puls - application[ID].K_Puls > -50) ? Puls + abs(application[ID].K_Puls - application[ID].K_PDown) : 0;
					send(application[ID].Connections, CLIENT_OK, strlen(CLIENT_OK), NULL);
					send(application[ID].Connections, CLIENT_OK, strlen(CLIENT_OK), NULL);
					database_read_flags(application[ID].uid, ID);
					printf("%s\ttemp=%.2f\tpuls=%d\tOxygen=%d\tPUp=%d\tPDown=%d\r\n", application[ID].Name, temp, Puls, SpO2, PUp, Pdown);
					if (temp<100&&database_init()&&Puls>10) {											//����������� � ���� ������
						char buf_time[20] = { 0 };														//����� ��� �������� ���� � �������
						char buf_query[500] = { 0 };													//����� ��� �������� ������ ������� � ���� ������
						datetime_now_to_bd(buf_time);													//������������ ������ ������� ��� ������ ���� ������
						sprintf(buf_query,
							"INSERT INTO `body_2.0`.`telemetry` (`date_time`, `uid0`, `uid1`, `uid2`, `temp`, `oxygen`, `puls`, `pressure_up`, `pressure_down`) VALUES ('%s', '%ld', '%ld', '%ld', '%.2f', '%d', '%d', '%d', '%d');"
							, buf_time, application[ID].uid[0], application[ID].uid[1], application[ID].uid[2], temp, SpO2, Puls, PUp, Pdown);			//������������ ������ ������� � �� �� ���������� ����� ������															//����� �������������� ������
						if (mysql_query(conn, buf_query)) printf("%s\r\n", mysql_error(conn));			//���� �� ������� ��������� ������ � ��
						mysql_close(conn);																//������� ���������� � ��
						//send(application[ID].Connections, CLIENT_OK,strlen(CLIENT_OK),NULL);
					}
					mut.unlock();
				}
				else printf("����������� ����� ������ �� �����!\r\n");									//���� ����������� ����������� ����� �� ��������� � ��������
			}
			else if (strstr((char*)buffer, "OK_COM")) {													//���� �� ���������� ������ ����� �� ������ �������� ������
				application[ID].wait_OK = 0;
				application[ID].flag_com_app = 0;
				mut.lock();
				if (database_init()) {																//����������� � ���� ������
					char buf_query[500] = { 0 };													//����� ��� �������� ������ ������� � ���� ������
					sprintf(buf_query, "UPDATE application SET commands = 0 WHERE (uid0=%lu AND uid1=%lu AND uid2=%lu);",
						application[ID].uid[0], application[ID].uid[1], application[ID].uid[2]);	//������������ ������ ������� � �� �� ��������� ������ ����������														//����� �������������� ������
					if (mysql_query(conn, buf_query)) printf("%s\r\n", mysql_error(conn));			//���� �� ������� ��������� ������ � ��
					printf("OK command #%d\r\n",ID);
					mysql_close(conn);																//������� ���������� � ��
				}
				mut.unlock();
			}
			/*������� �������� ������*/

#if DEBUG_RESIVE_HEX																					//����� ���������� � ����������������� �������
			//printf("%d:\t", ID); for (int i = 0; i<BUF_RECIV_SIZE; i++) printf("%x ", buffer[i]); printf("\r\n");//����� ������ ����������� ���� �� ��������� ������� NULL
#else																									//����� ���������� � ��������� �������
			printf("%d:\t%s", ID, buffer);
			//cout << ID <<" - " << buffer;
#endif

			application[ID].buf_wdt_user = clock();
		}
		else {
			mut.lock();
			ClientCount--;
			//printf("���������� ��������� #%d\t\t\t\t-=%d=-\r\n", ID, ClientCount);
			application[ID].Connections = NULL;
			application[ID].buf_wdt_user = 0;
			for (int i = 0; i < BUF_USER_SIZE; i++) {
				if (buf_user[i] == ID) {
					for (int ii = i; ii < BUF_USER_SIZE - 1; ii++) buf_user[ii] = buf_user[ii + 1];
				}
			}
			for (int i = BUF_USER_SIZE - 1; i; i--) buf_user_id[i] = buf_user_id[i - 1];
			buf_user_id[0] = ID;
			debug_connect_buffer(DEBUG_CON_INFO);														//����� ���������� ���������� �� ������� � ������� �����������
			mut.unlock();
			break;
		}
	}
	delete[] buffer;
}
/*������� �������*/

#endif // !THREAD_FUNCTION_H
