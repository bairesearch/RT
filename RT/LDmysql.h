/*******************************************************************************
 * 
 * This file is part of BAIPROJECT.
 * 
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3c1a 11-October-2012
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
