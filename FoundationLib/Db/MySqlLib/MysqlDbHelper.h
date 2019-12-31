#pragma once

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h> 

using namespace sql;

class CMysqlDbHelper
{
public:
	CMysqlDbHelper(void);
	~CMysqlDbHelper(void);

	static Connection *getConnection(char *url, char *user, char *pwd);
	static void closeConnection(Connection *conn);
};
