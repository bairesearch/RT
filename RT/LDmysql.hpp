/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: LDmysql.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3l2a 12-June-2017
 *
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
	private: bool performSQLrealSelectQuery(const char* sqlCommand, const unsigned long stringLength);	//ignores string escape character
	public: bool performSQLinsertQuery(const char* sqlCommand);
	public: bool performSQLrealInsertQuery(const char* sqlCommand, const unsigned long stringLength);	//ignores string escape character
	public: long performSQLgetNumRowsQuery(const string tableName);
	public: void performSQLdeleteAllRowsQuery(const string tableName);
	public: void endMySQLserverConnection();
};

#endif
