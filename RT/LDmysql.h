/*******************************************************************************
 *
 * File Name: LDmysql.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a7b 09-June-2012
 *
 *******************************************************************************/

#include "SHAREDglobalDefs.h"

#ifndef LINUX
	#include <winsock.h>
#endif
#include <mysql/mysql.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;


extern MYSQL * connection;
extern MYSQL mysql;
extern MYSQL_RES *result;


void testMySQLserverConnection();

bool initiateMySQLserverConnection(char * mysqlserveripaddressAndPort, char * username, char * password, char * databaseName);
bool performSQLSelectQuery(char * sqlCommand, char *sqlCommandOutput);	//not complete - debug only
bool performSQLSelectQuery(char * sqlCommand);
bool performSQLRealSelectQuery(char * sqlCommand, unsigned long stringLength);	//ignores string escape character
bool performSQLInsertQuery(char * sqlCommand);
bool performSQLRealInsertQuery(char * sqlCommand, unsigned long stringLength);	//ignores string escape character
long performSQLGetNumRowsQuery(string tableName);
void performSQLdeleteAllRowsQuery(string tableName);
void endMySQLserverConnection();
