#pragma once

#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cppconn/exception.h> 
#include <cppconn/resultset.h> 
#include <cppconn/statement.h> 
#include <cppconn/prepared_statement.h> 

using namespace sql;

#include <string>
using namespace std;

class DataBuf : public std::streambuf
{
public:
	DataBuf(char* d, size_t s)
	{
		setg(d, d, d+s);
	}
};

class CDbOperation
{
public:
	CDbOperation(void);
	~CDbOperation(void);

	void beginTransaction();
	void endTransaction();

	void commit();
	void rollback();

	// 执行查询操作，复杂的sql语句可以用这个函数，否则请用query
	// 返回值：
	// null：获取连接失败，或执行失败
	// ResultSet对象
	ResultSet *executeQuery(char *sql, int count, ...);
	ResultSet *executeQuery(char *sql, int count, va_list argptr);

	// 执行写入或更新操作，复杂的sql语句可以用这个函数，否则请用insert和update
	// 返回值：
	// -1：获取数据库连接失败 
	// -2：失败
	// >=0：成功，返回受影响的行数
	uint64_t execute(char *sql, int count, ...);
	uint64_t execute(char *sql, int count, va_list argptr);

	void closeResultSet(ResultSet *rs);

	// 数据库写入
	// 只能写入单个表
	// Can use columns parameter like this:
	//     String columns = "col1,col2,col3"; // col count must equals to values parameter
	// Can use values parameter like this:
	//     String conditions = "value1,value2,value3"; // value count must equals to columns parameter
	// Can use ... parameter like this:
	//     'n',3,'s',"second para",'n',5
	// 返回值：
	// -1：获取数据库连接失败 
	// -2：失败
	// >=0：成功，返回受影响的行数
	int insert(char *table, char *columns, char *values, int count, ...);

	// 数据库更新
	// 只能更新单个表
	// Can use values parameter like this:
	//     String values = "col1=?,col2=?"; // etc
	// Can use ... parameter like this:
	//     'n',3,'s',"second para"  // etc
	// 返回值：
	// -1：获取数据库连接失败 
	// -2：失败
	// >=0：成功，返回受影响的行数
	int update(char *table, char *values, char *whereConditions, int count, ...);

	// 数据库查询
	// 支持多表联合查询
	// Can use selectedColumns parameter like this:
	//     String selectedColumns = "col1,col2,col3"; // etc
	// Can use ... parameter like this:
	//     'n',3,'s',"second para",'n',4
	// 返回值：
	// null：获取连接失败，或执行失败
	// ResultSet对象
	ResultSet *select(char *selectedColumns, char *fromTables, char *whereCondition, int count, ...);

protected:
	BOOL getConnection();
	void closeConnection();
	void closeConnection(Connection *conn);

// 	PreparedStatement *prepareArgs(PreparedStatement *stmt, int count, ...);
	PreparedStatement *prepareArgs(PreparedStatement *stmt, int count, va_list argptr);

	void closeStatement(Statement *stmt);

	string m_url;
	string m_user;
	string m_pwd;

	Connection *m_conn;

	BOOL m_isTransaction;

	PreparedStatement *m_stmt;
};
