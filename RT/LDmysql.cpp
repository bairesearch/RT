/*******************************************************************************
 *
 * File Name: LDmysql.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a7a 06-June-2012
 *
 * to test sql connection;
 * 1. uncomment int main()
 * 2. g++ -o LDmysqlTest LDmysql.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql
 *
 *******************************************************************************/


#include "LDmysql.h"


/*
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/statement.h>
//#include <cppconn/mysql_util.h>
sql::mysql::MySQL_Driver *driver;
sql::Connection	*con;
sql::Statement *stmt;
*/


MYSQL *connection;
MYSQL mysql;
MYSQL_RES *result;


/*
int main()
{
	testMySQLserverConnection();
}
*/

void testMySQLserverConnection()
{
		//tcp://127.0.0.1:3306"
	initiateMySQLserverConnection("localhost", "rich", "Esteban7", "objectRecog");
	char sqlCommandOutput[1000];
	performSQLSelectQuery("SELECT `pBinxy`, `ID` FROM `objectRecog`.`snapshot` WHERE ( ( `pBinxy` = 823 ) )", sqlCommandOutput);
	cout << "sqlCommandOutput = " << sqlCommandOutput << endl;
	endMySQLserverConnection();
}


bool initiateMySQLserverConnection(char * mysqlserveripaddressAndPort, char * username, char * password, char * databaseName)
{

	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql,mysqlserveripaddressAndPort,username,password,databaseName,0,0,0);
	if(connection == NULL)
	{
		cout << mysql_error(&mysql) << endl;
		return false;
	}

	/*
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect(mysqlserveripaddressAndPort, username, password);
	stmt = con->createStatement();
	string databaseLoadString = "USE ";
	databaseLoadString = databaseLoadString + databaseName;
	stmt->execute(databaseLoadString);
	*/

	return true;
}

//not complete - debug only
bool performSQLSelectQuery(char * sqlCommand, char *sqlCommandOutput)
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
		//printf("%s\n", row[1]);
		//sqlCommandOutput[index] = row[0];
		index++;
	}
	//sqlCommandOutput[index] = '\0';

	/*
	stmt->execute(sqlCommand);
	*/

	return true;
}

bool performSQLSelectQuery(char * sqlCommand)
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

bool performSQLRealSelectQuery(char * sqlCommand, unsigned long stringLength)
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
 


//not yet working...
long performSQLGetNumRowsQuery(string tableName)
{
	MYSQL_ROW row;
	int query_state;

	string sqlQueryString = "";
	sqlQueryString = sqlQueryString + "SELECT ID, COUNT(*) FROM " + tableName;
	char * sqlCommand = const_cast<char*>(sqlQueryString.c_str());

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return 0;
	}

	int index = 0;
	long numRowsInTable;
	result = mysql_store_result(connection);

	if((row = mysql_fetch_row(result)) != NULL)
	{
		numRowsInTable = long(atof(row[1]));	//0
	}



	return numRowsInTable;

}

void performSQLdeleteAllRowsQuery(string tableName)
{
	MYSQL_ROW row;
	int query_state;

	string sqlQueryString = "";
	sqlQueryString = sqlQueryString + "DELETE FROM " + tableName;
	char * sqlCommand = const_cast<char*>(sqlQueryString.c_str());

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
	}

}











bool performSQLInsertQuery(char * sqlCommand)
{
	int query_state;

	query_state = mysql_query(connection, sqlCommand);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return false;
	}

	return true;
}


bool performSQLRealInsertQuery(char * sqlCommand, unsigned long stringLength)
{
	int query_state;

	query_state = mysql_real_query(connection, sqlCommand, stringLength);
	if (query_state !=0)
	{
		cout << mysql_error(connection) << endl;
		return false;
	}

	return true;
}



void endMySQLserverConnection()
{
	mysql_close(connection);


	/*
	delete stmt;
	delete con;
	*/
}
