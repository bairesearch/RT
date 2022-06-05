 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDmysql.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3q1a 05-June-2022
 * /
 *******************************************************************************/


#ifndef HEADER_LD_MYSQL
#define HEADER_LD_MYSQL

#include "SHAREDglobalDefs.hpp"

#ifndef LINUX
	#include <winsock.h>
#endif
#include <mysql/mysql.h>


extern MYSQL* connection;
extern MYSQL mysql;
extern MYSQL_RES* result;


class LDmysqlClass
{
	private: void testMySQLserverConnection();

	public: bool initiateMySQLserverConnection(const char* mysqlServerIpAddressAndPort, const char* username, const char* password, const char* databaseName);
	private: bool performSQLselectQuery(const char* sqlCommand, const char* sqlCommandOutput);	//not complete - debug only
	private: bool performSQLselectQuery(const char* sqlCommand);
	private: bool performSQLrealSelectQuery(const char* sqlCommand, const uint64_t stringLength);	//ignores string escape character
	public: bool performSQLinsertQuery(const char* sqlCommand);
	public: bool performSQLrealInsertQuery(const char* sqlCommand, const uint64_t stringLength);	//ignores string escape character
	public: int64_t performSQLgetNumRowsQuery(const string tableName);
	public: void performSQLdeleteAllRowsQuery(const string tableName);
	public: void endMySQLserverConnection();
};

#endif
