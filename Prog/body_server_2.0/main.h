/*
����� ���������� �� ����������:

 ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
| 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 |
 ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 00		-	��������� ���							uint8_t
 01..04	-	UID ����������							uint32_t
 05..08	-	UID ����������							uint32_t
 09..12	-	UID ����������							uint32_t
 13..16	-	�����������								float
 17		-	������� ���������� ��������� � �����	uint8_t
 18..19	-	������� ��������						uint16_t
 20..21	-	������ ��������							uint16_t
 22..23	-	�����									uint16_t
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

/*���������� � ���������*/
#define BUF_SIZE			1024								//������ ������ �����
#define BUF_USER_SIZE		5								//������������ ���-�� �����������
#define SERVER_PORT			"7770"								//���� ������� ��� ����������� ��������

#define WDT_MS_MAX			10000								//����� �������� ����������� ����������
#define WDT_SPEED			500									//�������� ���������� ������ WDT. ���������� ������ ��������� ��������� ���������� � ������ ���������

#define DEBUG_CON_INFO		0									//���������/���������� ������ ���������� �� ������� � ������� �����������
#define DEBUG_RESIVE_HEX	1									//���������/���������� ������ �������� ���������� �� ������ � ���������������� �������

#define MAX_RFID			200									//������������ ���-�� ���� ��� ������� � ����������
#define BUF_RECIV_SIZE		26									//������ ������ ������������ �� ����������

#define NAME_DB			"body_2.0"								//��� ���� ������
#define HOST_DB			"localhost"								//���� ���� ������
#define LOGIN_DB		"dimaib"								//����� ���� ������
#define PASS_DB			"23092309"								//������ ���� ������

#define CLIENT_OK		"t_ok\r\n"								//��������� ������ ������ �� �������� ����� ������

int buf_user_id[BUF_USER_SIZE] = { 0 };							//����� �������� ������� �����������
int buf_user[BUF_USER_SIZE] = { 0 };							//����� �������� �����������
//long buf_wdt_user[BUF_USER_SIZE] = { 0 };						//����� �������� ������� ��������� ���������� �����������. ��� ������������ ���������� �����������
int ClientCount = 0;											//������� ���-�� �����������														

/*���������� � ���������*/



/*��������� ��� �������*/
SOCKET Connect;													//����� ��� ��������� �����������
SOCKET Listen;													//����� ��� ������������� �����
mutex mut;														//��������� �������, ��� ������������� ������ �������

struct _application {											//������ ��������� ����������� ���������
	SOCKET Connections;											//������ �������� �����������
	uint32_t uid[3];
	uint32_t buf_wdt_user;										//����� �������� ������� ��������� ���������� �����������. ��� ������������ ���������� �����������
	uint32_t flag_com_app;										//����� ������ ����������
	uint8_t wait_OK;											//�������� ������ �� ����������, ��� ����� ������ �����
	string Name;												//��� ��������
	uint8_t K_Puls;												//��������� �������� � ���������
	uint8_t K_PUp;												//��������� �������� � ���������
	uint8_t K_PDown;											//��������� �������� � ���������
}*application;
/*��������� ��� �������*/

#include "function.h"
//#include "thread_function.h"
																															
/*��������� �������*/
void debug_connect_buffer(uint8_t flag)																				//����� ���������� ���������� �� ������� �����������
{
	if (flag) {
		printf("buf_user_id:");	for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", buf_user_id[i]);
		printf("\r\nbuf_user:"); for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", buf_user[i]);
		printf("\r\nConnections:");	for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", (int)application[i].Connections);
		printf("\r\nbuf_wdt_user:"); for (int i = 0; i < BUF_USER_SIZE; i++) printf("\t[%d]", application[i].buf_wdt_user); printf("\r\n");
	}
}

int socket_init()																						//������� ������������� ������
{
	for (int i = 0; i < BUF_USER_SIZE; i++) { buf_user_id[i] = i; buf_user[i] = -1; }					//������������� ������� �����������
	WSADATA data;
	//WORD version = MAKEWORD(1, &data);
	int res = WSAStartup(MAKEWORD(1, &data), &data);
	//if (res != 0) { cout << "������ ������������� Ws2_32.lib\r\n"; return 1; }
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

void datetostr(uint8_t* date,uint8_t *buf)														//������� ���� �� ������� yyyy-mm-dd � ������ dd.mm.yyyy
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
/*��������� �������*/
#endif
