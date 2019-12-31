// OCCIWrapper.h: interface for the COCCIWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCCIWRAPPER_H__9447E470_A278_4FD5_B908_82FD5D505235__INCLUDED_)
#define AFX_OCCIWRAPPER_H__9447E470_A278_4FD5_B908_82FD5D505235__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COCCIWrapper  
{
public:
	COCCIWrapper();
	virtual ~COCCIWrapper();
public:
	// 连接ORACLE数据库
	BOOL Connect();
	// 断开连接
	BOOL Disconnect();
	// 根据sql语句创建Statement对象
	BOOL createStmt(int count,const char * sql,...);
	BOOL createStmtByMultiConditions(string whereConditions,CStringArray *whereValues,CStringArray *types);
	Statement *createStatement(int count,const char * sql,...);
	// 执行Statement
	BOOL stmtExecute();
	BOOL stmtExecute(Statement *stmt);
	// 执行Statement更新
	BOOL stmtExecuteUpdate();
	BOOL stmtExecuteUpdate(Statement *stmt);
	// 关闭Statement
	BOOL closeStmt();
	BOOL closeStmt(Statement *stmt);
	// 根据查询获取记录集
	ResultSet *stmtQuery();
	ResultSet *stmtQuery(Statement *stmt);
	// 获取BLOB字段的大小
	int getBlobSize(int colIndex);
	// 获取BLOB字段的数据
	int getBlob(int colIndex,unsigned char *blobData);
	// 更新BLOB字段，内部记录集会调用next()方法
	BOOL updateBlob(int blobCount,...);
	// 关闭记录集
	BOOL closeRecordSet();
	BOOL closeRecordSet(Statement *stmt, ResultSet *rs);

	// 提交操作
	BOOL Commit();
	// 操作回滚
	BOOL Rollback();

// 	BOOL Connect(char *uid, char * pwd, char *sid);

	BOOL isConnected;

	const char *errMsg;

// 	string className;
// 	string classCode;
	
private:
	string m_uid;
	string m_pwd;
	string m_sid;
	Environment *env;
	Connection  *conn;

	Statement *stmt;
	ResultSet *rs;
};

#endif // !defined(AFX_OCCIWRAPPER_H__9447E470_A278_4FD5_B908_82FD5D505235__INCLUDED_)
