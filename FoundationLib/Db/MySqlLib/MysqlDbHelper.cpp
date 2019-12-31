#include "StdAfx.h"
#include "MysqlDbHelper.h"
#include "AppConfig.h"

CMysqlDbHelper::CMysqlDbHelper(void)
{
}

CMysqlDbHelper::~CMysqlDbHelper(void)
{
}

Connection *CMysqlDbHelper::getConnection(char *url, char *user, char *pwd)
{
	try
	{
		sql::mysql::MySQL_Driver *driver=NULL; 
		sql::Connection *conn=NULL; 

		driver = sql::mysql::get_mysql_driver_instance();
		conn = driver->connect(url, user, pwd);
		return conn;
	}
	catch (sql::SQLException &e)
	{
		return NULL;
	}
}

void CMysqlDbHelper::closeConnection(Connection *conn)
{
	if(!conn)
		return;

	try
	{
		conn->close();
	}
	catch(sql::SQLException &e)
	{

	}
}
