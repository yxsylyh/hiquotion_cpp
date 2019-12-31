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
	// 执行Statement
	BOOL stmtExecute();
	// 执行Statement更新
	BOOL stmtExecuteUpdate();
	// 关闭Statement
	BOOL closeStmt();
	// 根据查询获取记录集
	ResultSet *stmtQuery();
	// 获取BLOB字段的大小
	int getBlobSize(int colIndex);
	// 获取BLOB字段的数据
	int getBlob(int colIndex,char *blobData);
	// 更新BLOB字段
	BOOL updateBlob(int blobCount,...);
	// 关闭记录集
	BOOL closeRecordSet();

	// 设置 Statement 使用事务，即 setAutoCommit(false)
	BOOL setTransaction();

	// 提交操作
	BOOL Commit();
	// 操作回滚
	BOOL Rollback();

// 	BOOL Connect(char *uid, char * pwd, char *sid);

	BOOL isConnected;

	BOOL isInitSucceed;

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
