/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDmysql.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3m16b 24-April-2019
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
