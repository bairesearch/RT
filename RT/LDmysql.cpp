 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDmysql.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3q1a 05-June-2022
 * /
 *
 * to test sql connection;
 * 1. uncomment int main()
 * 2. g++ -o LDmysqlTest LDmysql.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql
 *
 *******************************************************************************/


#include "LDmysql.hpp"



MYSQL* connection;
MYSQL mysql;
MYSQL_RES* result;


/*
int main()
{
	testMySQLserverConnection();
}
*/

void LDmysqlClass::testMySQLserverConnection()
{
	initiateMySQLserverConnection("localhost", "MYSQLUSERNAME", "MYSQLPASSWORD", "objectRecog");
	char sqlCommandOutput[1000];
	const char* sqlCommand = "SELECT `pBinxy`, `ID` FROM `objectRecog`.`snapshot` WHERE ( ( `pBinxy` = 823 ) )";
	performSQLselectQuery(sqlCommand, sqlCommandOutput);
	cout << "sqlCommandOutput = " << sqlCommandOutput << endl;
	endMySQLserverConnection();
}


bool LDmysqlClass::initiateMySQLserverConnection(const char* mysqlServerIpAddressAndPort, const char* username, const char* password, const char* databaseName)
{

	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql,mysqlServerIpAddressAndPort,username,password,databaseName,0,0,0);
	if(connection == NULL)
	{
		cout << mysql_error(&mysql) << endl;
		return false;
	}

	return true;
}

//not complete - debug only
bool LDmysqlClass::performSQLselectQuery(const char* sqlCommand, const char* sqlCommandOutput)
{
	MYSQL_ROW row;
	int query_state;

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return false;
	}

	int index = 0;
	result = mysql_store_result(connection);
	while((row = mysql_fetch_row(result)) != NULL)
	{
		cout << row[0] << endl;
		cout << row[1] << endl;
		index++;
	}

	return true;
}

bool LDmysqlClass::performSQLselectQuery(const char* sqlCommand)
{
	MYSQL_ROW row;
	int query_state;

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return false;
	}

	return true;
}

bool LDmysqlClass::performSQLrealSelectQuery(const char* sqlCommand, const uint64_t stringLength)
{
	MYSQL_ROW row;
	int query_state;

	query_state = mysql_real_query(connection, sqlCommand, stringLength);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return false;
	}

	return true;
}



//int64_t performSQLgetNumRowsQuery(string tableName, string columnName)
int64_t LDmysqlClass::performSQLgetNumRowsQuery(const string tableName)
{
	MYSQL_ROW row;
	int query_state;

	string sqlQueryString = "";
	#ifdef SQL_MYSQL_VERSION_5_7_PLUS
	//sqlQueryString = sqlQueryString + "SELECT COUNT(" + columnName + ") FROM " + tableName;
	sqlQueryString = sqlQueryString + "SELECT COUNT(*) FROM " + tableName;
	#else
	sqlQueryString = sqlQueryString + "SELECT ID, COUNT(*) FROM " + tableName;
	#endif
	char* sqlCommand = const_cast<char*>(sqlQueryString.c_str());

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return 0;
	}

	int index = 0;
	int64_t numRowsInTable;
	result = mysql_store_result(connection);

	if((row = mysql_fetch_row(result)) != NULL)
	{
		#ifdef SQL_MYSQL_VERSION_5_7_PLUS
		numRowsInTable = int64_t(atof(row[0]));
		#else
		numRowsInTable = int64_t(atof(row[1]));
		#endif
	}

	return numRowsInTable;
}


void LDmysqlClass::performSQLdeleteAllRowsQuery(const string tableName)
{
	MYSQL_ROW row;
	int query_state;

	string sqlQueryString = "";
	sqlQueryString = sqlQueryString + "DELETE FROM " + tableName;
	char* sqlCommand = const_cast<char*>(sqlQueryString.c_str());

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
	}

}











bool LDmysqlClass::performSQLinsertQuery(const char* sqlCommand)
{
	int query_state;

	#ifdef LD_DEBUG
	//cout << "performSQLinsertQuery{}: sqlCommand = " << sqlCommand << endl;
	#endif

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return false;
	}

	return true;
}


bool LDmysqlClass::performSQLrealInsertQuery(const char* sqlCommand, const uint64_t stringLength)
{
	int query_state;

	#ifdef LD_DEBUG
	/*
	cout << "performSQLrealInsertQuery{}:";
	for(int i=0; i<stringLength; i++)
	{
		cout << sqlCommand[i];
	}
	cout << endl;
	*/
	#endif

	query_state = mysql_real_query(connection, sqlCommand, stringLength);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return false;
	}

	return true;
}



void LDmysqlClass::endMySQLserverConnection()
{
	mysql_close(connection);


	/*
	delete stmt;
	delete con;
	*/
}
