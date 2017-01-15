/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDmysql.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3h15b 29-February-2016
 *
 *******************************************************************************/


#include "SHAREDglobalDefs.h"

#ifndef LINUX
	#include <winsock.h>
#endif
#include <mysql/mysql.h>


extern MYSQL* connection;
extern MYSQL mysql;
extern MYSQL_RES* result;


void testMySQLserverConnection();

bool initiateMySQLserverConnection(char* mysqlServerIpAddressAndPort, char* username, char* password, char* databaseName);
bool performSQLselectQuery(char* sqlCommand, char* sqlCommandOutput);	//not complete - debug only
bool performSQLselectQuery(char* sqlCommand);
bool performSQLrealSelectQuery(char* sqlCommand, unsigned long stringLength);	//ignores string escape character
bool performSQLinsertQuery(char* sqlCommand);
bool performSQLrealInsertQuery(char* sqlCommand, unsigned long stringLength);	//ignores string escape character
long performSQLgetNumRowsQuery(string tableName);
void performSQLdeleteAllRowsQuery(string tableName);
void endMySQLserverConnection();
