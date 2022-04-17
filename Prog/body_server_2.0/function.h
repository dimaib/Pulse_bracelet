#ifndef FUNCTION_H
#define FUNCTION_H

#include "main.h"
#include "function.h"
#include <mysql.h>
#include "database.h"

uint8_t crc8(uint8_t* data)														//��������� crc8 dalas/maxim
{
	uint8_t crc = 0;
	uint8_t tmp = 0;
	for (uint8_t i = 0; i < 7; i++) {
		tmp = data[i] ^ crc;
		crc = 0;
		if (tmp & 0x01) crc ^= 0x5e;
		if (tmp & 0x02) crc ^= 0xbc;
		if (tmp & 0x04) crc ^= 0x61;
		if (tmp & 0x08) crc ^= 0xc2;
		if (tmp & 0x10) crc ^= 0x9d;
		if (tmp & 0x20) crc ^= 0x23;
		if (tmp & 0x40) crc ^= 0x46;
		if (tmp & 0x80) crc ^= 0x8c;
	}
	return crc;
}

void test()
{
	if (database_init()) {
		char buf_query[200] = { 0 };
		sprintf(buf_query,
			"INSERT INTO `body_temp`.`telemetry` (`date_time`, `uid0`, `uid1`, `uid2`, `temp`) VALUES ('%s', '%ld', '%ld', '%ld', '32.45');"
			, "2020.07.24 00:00:00", 1000L, 2000L, 3000L);
		if (mysql_query(conn, buf_query)) printf("�� ������� �������� ������ � ����\r\n%s\r\n", mysql_error(conn));	//���� �� ������� ��������� ������ � ��
		mysql_close(conn);
	}
}

int valid()
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	int y = localtm->tm_year + 1900;
	int m = localtm->tm_mon + 1;
	int d = localtm->tm_mday;
	printf("%d %d %d\r\n",d,m,y);
	if ((y == 2020)&&!(m > 8)) return 0; else return 1;
}

void datetime_now_to_bd(char* buf)													//������� ��� ������������ ���� � ������� ��� ���� ������
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	
	sprintf(buf, "%d.%02d.%02d %02d:%02d:%02d", localtm->tm_year + 1900, localtm->tm_mon + 1, localtm->tm_mday, localtm->tm_hour, localtm->tm_min, localtm->tm_sec);
}

uint16_t crc16(uint8_t* data, uint16_t len)											//������� crc16
{
	uint16_t crc = 0xFFFF;
	while (len--) {
		crc ^= *data++ << 8;
		for (uint8_t i = 0; i < 8; i++) crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
	}
	return crc;
}

void set_crc_in_byte(uint8_t* data, uint16_t len)									//������� ��������� crc16 ������� � ����������� � � ��� ��������� �����
{
	uint16_t crc = crc16((uint8_t*)data, len - 2);									//���������� crc16 ������
	data[len - 2] = (uint16_t)crc & 0x00ff;											//������� ���� ����������� �����
	data[len - 1] = ((uint16_t)crc >> 8) & 0x00ff;									//������� ���� ����������� �����
}

uint8_t valid_crc16(uint8_t* data, uint16_t len)									//������� ��������� crc16 ������ � ���������� � � ����� ���������� ������� ������
{
	uint16_t crc = data[len - 1];													//������� ���� crc
	crc <<= 8; crc |= data[len - 2];												//������� ���� crc
	return crc == crc16(data, len - 3);												//���� ����� �����, �� ���������� 1, ����� 0
}

/*������ ������� ������:
[Esc]	-	���������� ������
[t]		-	����� �� ����� ������� � �����������
*/
void hot_keys()																		//������� ��������� ������� ������
{
	while (_kbhit()) {																//��������� ������� �������
		int is_key = _getch();
		printf("%d\r\n",is_key);
		if (is_key == 27) {															//���� ����� esc, �� ������ ������ � ������������� ������
			printf("[Esc] - ���������� ������; [Enter] - �����");
			Sleep(500);																//��������� 500��, �� ��������� ���������� �������
			while (1) {																//����������� ����
				int key = _getch();													//��������� ������� �������
				if (key == 13) { mut.unlock(); exit(0); }							//���� ����� Enter, �� ������� �� ���������
				else if (key == 27) break;											//���� ����� Esc, �� ����������� �� ������������ ����� � ���������� ������
			}
			printf("\r\n");
		}else if (is_key==116) {													//������� �� ������� t. ������� ������ �� ������� telemetry
			if (database_init()) {
				mysql_query(conn, "SELECT * FROM telemetry");						//������ ������ � �������
				if (res = mysql_store_result(conn)) {
					int i = 0;
					printf("#########������ ���� ������########\r\n");
					printf("[id]\t[date time]\t\t[uid[0]]\t[uid[1]]\t[uid[2]]\t[temp]\r\n");
					for (i = 0; row = mysql_fetch_row(res); i++) {
						mysql_num_fields(res);
						printf("%s\t%s\t%s\t\t%s\t%s\t%s\r\n", row[0], row[1], row[2], row[3], row[4], row[5]);
					}
					printf("[id]\t[date time]\t\t[uid[0]]\t[uid[1]]\t[uid[2]]\t[temp]\r\n");
					printf("########��������� ���� ������#######\r\n");
					mysql_close(conn);
				}
				else { printf("%s\r\n", mysql_error(conn)); mysql_close(conn);}
			}
			
		}
	}
}
#endif	//FUNCTION_H
