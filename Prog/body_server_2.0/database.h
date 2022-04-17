#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>

MYSQL* conn;																			//структура дескриптора и подключения к базе данных
MYSQL_RES* res;
MYSQL_ROW row;

int database_init();

#include <string.h>
#include "main.h"
#include "stdlib.h"

uint32_t database_read_flags(uint32_t *uid, int ID)
{
	conn = mysql_init(NULL);
	if (conn == NULL || !mysql_real_connect(conn, HOST_DB, LOGIN_DB, PASS_DB, NAME_DB, NULL, NULL, 0)) {
		printf("%s\r\n", mysql_error(conn));
		return 0;
	}
	mysql_set_character_set(conn, "cp1251");
	char buf_query[300] = {0};
	sprintf(buf_query, "SELECT * FROM application WHERE uid0=%d AND uid1=%d AND uid2=%d;", uid[0], uid[1], uid[2]);
	//sprintf(buf_query, "SELECT * FROM application;");
	mysql_query(conn, buf_query);										//делаем запрос к таблице
	if (res = mysql_store_result(conn)) {
		int i = 0;
		for (i = 0; row = mysql_fetch_row(res); i++) {
			mysql_num_fields(res);
			mysql_close(conn);
			if (ID > -1) { 
				application[ID].Name = row[4];
				application[ID].K_Puls = atoi(row[6]);
				application[ID].K_PUp = atoi(row[7]);
				application[ID].K_PDown = atoi(row[8]);
			}
			return atoi(row[5]);
		}
		mysql_close(conn);
	}
	else { printf("%s\r\n", mysql_error(conn)); mysql_close(conn); }
	return 0;
}

int database_init()																		//инициализация базы данных
{
	conn = mysql_init(NULL);
	if (conn == NULL || !mysql_real_connect(conn, HOST_DB, LOGIN_DB, PASS_DB, NAME_DB, NULL, NULL, 0)) {
		printf("%s\r\n", mysql_error(conn));
		return 0;
	}
	mysql_set_character_set(conn, "cp1251");
	return 1;
}

int betta_test()																		//функция проверки базы у Дениса
{
	conn = mysql_init(NULL);
	if (conn == NULL || !mysql_real_connect(conn, "185.72.146.161", "po4talewai2_test", "345Disa2109", "po4talewai2_test", NULL, NULL, 0)) {
		printf("%s\r\n", mysql_error(conn));
		return 0;
	}
	mysql_set_character_set(conn, "cp1251");

	mysql_query(conn, "SELECT * FROM dima_base");										//делаем запрос к таблице
	if (res = mysql_store_result(conn)) {
		int i = 0;
		for (i = 0; row = mysql_fetch_row(res); i++) {
			mysql_num_fields(res);
			printf("%s\t%s\r\n", row[0], row[1]);
			if (row[1] == (char*)'1') return 1; else return 0;
		}
		mysql_close(conn);
	}
	else { printf("%s\r\n", mysql_error(conn)); mysql_close(conn); }

	return 0;
}

#endif	//DATABASE_H