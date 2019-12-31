// OCCIWrapper.cpp: implementation of the COCCIWrapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OCCIWrapper.h"
#include "DbConfig.h"
#include <C++\FoudationLib\LogLib\Remark.h>
#include <c++\foudationlib\exception\myexception.h>

extern CRemark remark;
// extern CLogList logs;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// env
// conn
// stmt
// rs

// 一般的使用顺序

// 1、执行或执行更新连接
// 创建Statement
// 执行或执行更新
// 关闭Statement
// 关闭连接

// 2、查询
// 创建Statement
// 查询获取记录集
// 如果更新了记录集中的记录，则执行更新
// 关闭记录集
// 关闭Statement
// 关闭连接


// 如果没连接，返回假
// 如果没有sql，返回假
// 如果没有stmt，返回假
// 如果没有rs，返回假

COCCIWrapper::COCCIWrapper()
: env(0),conn(0),stmt(0),rs(0),isConnected(FALSE),errMsg(0)
{
// 	memset(m_uid,0x00,32);
// 	memset(m_pwd,0x00,32);
// 	memset(m_sid,0x00,32);
// 	env  = NULL;
// 	conn = NULL;

// 	className="COCCIWrapper";
// 	classCode="03";
	
	CDbConfig config;
// 	remark.doLog("从配置文件获取数据库连接的用户名密码等");
	m_uid=config.getUserName();
	m_pwd=config.getPwd();
	m_sid=config.getOraName();

	string msg="用户名："+m_uid+"，密码："+m_pwd+"，SID："+m_sid;
	remark.doLog(LOGLEVEL_SHOWINFO,msg);

// 	remark.doLog("用户名为："+m_uid);
// 	remark.doLog("密码为："+m_pwd);
// 	remark.doLog("Ora名为："+m_sid);

	if(m_uid=="" || m_pwd=="" || m_sid=="")
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"获取数据库配置信息失败！用户名、密码或SID为空！");
//		throw CMyException("e","0",className,classCode,className,"00","01","获取数据库配置信息失败！","配置文件不存在，或配置文件格式不正确！",1);
// 		throw CException(EXCEPTION_INTERNAL,"获取数据库配置信息失败！","配置文件不存在，或配置文件格式不正确！");
// 		exit(-1);
	}
}

COCCIWrapper::~COCCIWrapper()
{
	m_uid="";
	m_pwd="";
	m_sid="";
	Disconnect();
}

// 连接ORACLE数据库
BOOL COCCIWrapper::Connect()
{
// 	try
// 	{
		remark.doLog(LOGLEVEL_SHOWINFO,"创建数据库环境");
		env = Environment::createEnvironment (Environment::DEFAULT);
		if(!env)
		{
// 			remark.doLog("连接数据库失败！获取Oracle环境变量为空！");
// 			throw CMyException("e","0",className,classCode,"Connect","01","01","连接数据库失败！","获取Oracle环境变量为空！",1);
			throw CMyException(EXCEPTION_INTERNAL,"连接数据库失败！","获取Oracle环境变量为空！");
// 			exit(-1);
		}
		//if(env==NULL) {	printf("%s","Can not create env!\n");return FALSE;}

		remark.doLog(LOGLEVEL_SHOWINFO,"创建数据库连接");
		conn = env->createConnection (m_uid, m_pwd, m_sid);
		if(!conn)
		{
// 			remark.doLog("连接数据库失败！Connection为空！");
// 			throw CMyException("e","0",className,classCode,"Connect","01","02","连接数据库失败！","Connection为空！",1);
			throw CMyException(EXCEPTION_INTERNAL,"连接数据库失败！","Connection为空！");
// 			exit(-1);
		}

		//if(conn==NULL){	printf("%s","Can not create connection !\n");return TRUE;}
// 	}
// 	catch(SQLException *e)
// 	{
// 		string msg;
// 		msg="连接失败！\n\n原因为：\n" + e->getMessage();
// // 		remark.doLog(msg.c_str());
// //		AfxMessageBox(msg.c_str());
// 		if(conn)
// 		{
// 			env->terminateConnection(conn);
// 			conn=NULL;
// 		}
// 		if(env)
// 		{
// 			env->terminateEnvironment(env);
// 			env=NULL;
// 		}
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		string msg;
// 		msg="连接失败！\n\n未知原因。\n";
// // 		remark.doLog("连接失败！未知原因。");
// //		AfxMessageBox(msg.c_str());
// 		if(conn)
// 		{
// 			env->terminateConnection(conn);
// 			conn=NULL;
// 		}
// 		if(env)
// 		{
// 			env->terminateEnvironment(env);
// 			env=NULL;
// 		}
// 		return FALSE;
// 	}

	isConnected=TRUE;
	return true;
}

// 断开连接
BOOL COCCIWrapper::Disconnect()
{
//	if(env==NULL || conn == NULL){return FALSE;}
	if(conn)
	{
		remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭数据库连接");
		env->terminateConnection (conn);
		conn=NULL;		
	}
	if(env)
	{
		remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭数据库环境");
		Environment::terminateEnvironment (env);
		env=NULL;
	}
	isConnected=FALSE;
	return TRUE;
}

// 根据sql语句创建Statement对象
BOOL COCCIWrapper::createStmt(int count,const char * sql,...)
{
// 	try
// 	{
		if(!conn) return FALSE;
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭曾经打开的 Statement");
			conn->terminateStatement(stmt);
			stmt=NULL;
		}

		remark.doLog(LOGLEVEL_SHOWDEBUG,"创建 Statement");
		stmt = conn->createStatement (sql);
		if(!stmt)
		{
 			remark.doLog(LOGLEVEL_SHOWERROR,"创建Statement失败！");
// 			throw CMyException("e","0",className,classCode,"createStmt","02","01","创建Statement失败！","",1);
 			throw CMyException(EXCEPTION_INTERNAL,"创建Statement失败！","createStmt");
// 			exit(-1);
			return FALSE;
		}

// 		const char *tmp = sql;
// 		int icount = 0 ;
// 		while(*tmp)
// 		{
// 			if(*tmp++ == ':' ) icount +=2; 
// 		}

		remark.doLog(LOGLEVEL_SHOWDEBUG,"向创建的 Statement 中写入值");
		va_list argptr;     //你的类型链表
		va_start(argptr,sql);//初始化你的marker链表

		for(int i = 1 ; i <= count ; i ++ )
		{
			char *s = va_arg( argptr, char* );
			if(!s)
			{
				remark.doLog(LOGLEVEL_SHOWERROR,"CreateStmt 参数有误！可能是漏写了变量的类型，也可能是可变参数的个数与指定的个数不匹配！");
				closeStmt();
				return FALSE;
			}
			switch (*s)
			{
			case 'S':
			case 's':
				stmt->setString (i,va_arg( argptr, char* ));
				//printf("%s\n",va_arg( argptr, char* ));
				break;
			case 'N':
			case 'n':
				stmt->setInt(i,va_arg( argptr, int ));
				//printf("%d\n",va_arg( argptr,int ));
				break;
			default:
				{
					//printf("unknown para type %s \n" ,s);
					va_end(argptr);//结束，与va_start合用
					closeStmt();
					remark.doLog(LOGLEVEL_SHOWERROR,"Statement参数有误！未知参数");
// 					throw CMyException("e","0",className,classCode,"createStmt","02","02","参数有误！","未知参数",1);
 					throw CMyException(EXCEPTION_INTERNAL,"创建 Statement 的参数有误！","未知参数");
//					exit(-1);
					return FALSE;
				}
			}
		}
		va_end(argptr);//结束，与va_start合用
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("CreateStmt error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeStmt();
// 		return FALSE;
// 	}
// // 	catch(CMyException *e)
// // 	{
// // // 		e->showDebugMessage();
// // 		closeStmt();
// // 		return FALSE;
// // 	}
// 	catch(...)
// 	{
// 		errMsg="CreateStmt error : Unknown error.\n";
// 		printf(errMsg);
// 		closeStmt();
// 		return FALSE;
// 	}
	return TRUE;
}

Statement *COCCIWrapper::createStatement(int count,const char * sql,...)
{
	remark.doLog(LOGLEVEL_SHOWDEBUG,"创建 Statement");
	Statement *stmt = conn->createStatement (sql);
	if(!stmt)
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"创建Statement失败！");
		return FALSE;
	}

	remark.doLog(LOGLEVEL_SHOWDEBUG,"向创建的 Statement 中写入值");
	va_list argptr;     //你的类型链表
	va_start(argptr,sql);//初始化你的marker链表

	for(int i = 1 ; i <= count ; i ++ )
	{
		char *s = va_arg( argptr, char* );
		if(!s)
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"CreateStmt 参数有误！可能是漏写了变量的类型，也可能是可变参数的个数与指定的个数不匹配！");
			break;
		}
		switch (*s)
		{
		case 'S':
		case 's':
			stmt->setString (i,va_arg( argptr, char* ));
			//printf("%s\n",va_arg( argptr, char* ));
			break;
		case 'N':
		case 'n':
			stmt->setInt(i,va_arg( argptr, int ));
			//printf("%d\n",va_arg( argptr,int ));
			break;
		default:
			{
				//printf("unknown para type %s \n" ,s);
				va_end(argptr);//结束，与va_start合用
				closeStmt();
				remark.doLog(LOGLEVEL_SHOWERROR,"Statement参数有误！未知参数");
				return FALSE;
			}
		}
	}
	va_end(argptr);//结束，与va_start合用
	return stmt;
}

// 执行Statement
BOOL COCCIWrapper::stmtExecute()
{
	if(!stmt)
		throw CMyException(EXCEPTION_INTERNAL,"无法调用数据库执行方法！","Statement 指针为空！");
// 	try
// 	{
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"调用数据库执行方法");
			stmt->execute();
		}
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		CString errMsg;
// 		errMsg.Format("StmtExecute error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// //		AfxMessageBox(errMsg);
// // 		printf("StmtExecute error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeStmt();
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="StmtExecute error : Unknown error.\n";
// 		printf(errMsg);
// 		closeStmt();
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::stmtExecute(Statement *stmt)
{
	if(!stmt)
		return FALSE;

	remark.doLog(LOGLEVEL_SHOWDEBUG,"调用数据库执行方法");
	stmt->execute();
	return TRUE;
}

// 执行Statement更新
BOOL COCCIWrapper::stmtExecuteUpdate()
{
	if(!stmt)
		throw CMyException(EXCEPTION_INTERNAL,"无法调用数据库的 执行更新 方法！","Statement 指针为空！");
// 	try
// 	{
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"调用数据库的 执行更新 方法");
			stmt->executeUpdate();
		}
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("StmtExecuteUpdate error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeStmt();
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="StmtExecuteUpdate error : Unknown error.\n";
// 		printf(errMsg);
// 		closeStmt();
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::stmtExecuteUpdate(Statement *stmt)
{
	if(!stmt)
		return FALSE;

	remark.doLog(LOGLEVEL_SHOWDEBUG,"调用数据库的 执行更新 方法");
	stmt->executeUpdate();
	return TRUE;
}

// 关闭Statement
BOOL COCCIWrapper::closeStmt()
{
// 	try
// 	{
		if(conn)
			if(stmt)
			{
				if(rs)
				{
					remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭 Statement 前先关闭记录集");
					stmt->closeResultSet(rs);
					rs=NULL;
				}
				remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭 Statement");
				conn->terminateStatement(stmt);
				stmt=NULL;
			}
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("CloseStmt error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		if(stmt)
// 		{
// 			conn->terminateStatement(stmt);
// 			stmt=NULL;
// 		}
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="CloseStmt error : Unknown error.\n";
// 		printf(errMsg);
// 		if(stmt)
// 		{
// 			conn->terminateStatement(stmt);
// 			stmt=NULL;
// 		}
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::closeStmt(Statement *stmt)
{
	if(conn)
		if(stmt)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭 Statement");
			conn->terminateStatement(stmt);
			stmt=NULL;
		}

		return TRUE;
}

// 根据查询获取记录集
ResultSet *COCCIWrapper::stmtQuery()
{
	if(!stmt) return NULL;

// 	try
// 	{
		if(rs)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭 Statement 前先关闭记录集");
			stmt->closeResultSet(rs);
			rs=NULL;
		}
		remark.doLog(LOGLEVEL_SHOWDEBUG,"执行数据库查询");
		rs=stmt->executeQuery();
// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("StmtQuery error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeRecordSet();
// 		closeStmt();
// 		return NULL;
// 	}
// 	catch(...)
// 	{
// 		errMsg="StmtQuery error : Unknown error.\n";
// 		printf(errMsg);
// 		closeRecordSet();
// 		closeStmt();
// 		return NULL;
// 	}
	return rs;
}

ResultSet *COCCIWrapper::stmtQuery(Statement *stmt)
{
	if(!stmt)
		return NULL;

	remark.doLog(LOGLEVEL_SHOWDEBUG,"执行数据库查询");
	ResultSet *rs=stmt->executeQuery();
	return rs;
}

BOOL COCCIWrapper::createStmtByMultiConditions(string whereConditions,CStringArray *whereValues,CStringArray *types)
{
	// 	try
	// 	{
	if(!conn) return FALSE;
	if(stmt)
	{
		remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭曾经打开的 Statement");
		conn->terminateStatement(stmt);
		stmt=NULL;
	}
	
	remark.doLog(LOGLEVEL_SHOWDEBUG,"创建 Statement");
	stmt = conn->createStatement(whereConditions.c_str());
	if(!stmt)
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"创建Statement失败！");
		// 			throw CMyException("e","0",className,classCode,"createStmt","02","01","创建Statement失败！","",1);
		throw CMyException(EXCEPTION_INTERNAL,"创建Statement失败！","createStmt");
		// 			exit(-1);
		return FALSE;
	}
	
	remark.doLog(LOGLEVEL_SHOWDEBUG,"向创建的 Statement 中写入值");

	int count=whereValues->GetSize();
	
	for(int i = 1 ; i <= count ; i ++ )
	{
		char *s = (LPTSTR)(LPCTSTR)types->GetAt(i-1);
		if(!s)
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"createStmtByMultiConditions 参数有误！types 中包含空字符项！");
			closeStmt();
			return FALSE;
		}
		switch (*s)
		{
		case 'S':
		case 's':
			{
				CString tmp=whereValues->GetAt(i-1);
				stmt->setString(i,tmp.GetBuffer(tmp.GetLength()));
				//printf("%s\n",va_arg( argptr, char* ));
				break;
			}
		case 'N':
		case 'n':
		{
			CString tmp=whereValues->GetAt(i-1);
			int ntmp=atol((LPTSTR)(LPCTSTR)tmp);
			stmt->setInt(i,ntmp);
			//printf("%d\n",va_arg( argptr,int ));
			break;
		}
		default:
			{
				//printf("unknown para type %s \n" ,s);
				closeStmt();
				remark.doLog(LOGLEVEL_SHOWERROR,"types 有误！未知参数");
				// 					throw CMyException("e","0",className,classCode,"createStmt","02","02","参数有误！","未知参数",1);
				throw CMyException(EXCEPTION_INTERNAL,"查询参数有误！","未知参数");
				//					exit(-1);
				return FALSE;
			}
		}
	}

	// 	}
	// 	catch(SQLException e)
	// 	{
	// 		//errMsg=e.getMessage().c_str();
	// 		printf("CreateStmt error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
	// 		closeStmt();
	// 		return FALSE;
	// 	}
	// // 	catch(CMyException *e)
	// // 	{
	// // // 		e->showDebugMessage();
	// // 		closeStmt();
	// // 		return FALSE;
	// // 	}
	// 	catch(...)
	// 	{
	// 		errMsg="CreateStmt error : Unknown error.\n";
	// 		printf(errMsg);
	// 		closeStmt();
	// 		return FALSE;
	// 	}
	return TRUE;
}

// 获取BLOB字段的大小
int COCCIWrapper::getBlobSize(int colIndex)
{
	if(colIndex<=0) return -1;
	if(!rs) return -1;

	int blobLength=0;

	// 	try
	// 	{
	// 通常调用函数会用了下面的语句
	// 		if(!rs->next()) return -1;

	Blob blob;
	remark.doLog(LOGLEVEL_SHOWDEBUG,"获取 BLOB 大小");
	blob=rs->getBlob(colIndex);

	if(blob.isNull())
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"BLOB 字段为空！");
		return -1;
	}

	if(!blob.isInitialized())
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"BLOG 字段未初始化！");
		return -1;
	}

	blobLength=blob.length();
	if(blobLength<0)
	{
		remark.doLog(LOGLEVEL_SHOWERROR,"BLOB 字段大小为负！");
		return -1;
	}
// 		blob.read(blobLength,blobData,blobLength);

	// 	}
	// 	catch(SQLException e)
	// 	{
	// 		CString s=e.getMessage().c_str();
	// 		AfxMessageBox(s);
	// 		printf("GetBlob error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
	// 		closeRecordSet();
	// 		closeStmt();
	// 		return -1;
	// 	}
	// 	catch(...)
	// 	{
	// 		errMsg="GetBlob error : Unknown error.\n";
	// 		printf(errMsg);
	// 		closeRecordSet();
	// 		closeStmt();
	// 		return -1;
	// 	}

	return blobLength;
}

// 获取BLOB字段的数据
int COCCIWrapper::getBlob(int colIndex,unsigned char *blobData)
{
	if(colIndex<=0) return -1;
	if(!blobData) return -1;
	if(!rs) return -1;

	int blobLength=0;

// 	try
// 	{
		// 通常调用函数会用了下面的语句
// 		if(!rs->next()) return -1;

		Blob blob;
		remark.doLog(LOGLEVEL_SHOWDEBUG,"获取 BLOB ");
		blob=rs->getBlob(colIndex);

		if(blob.isNull())
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"BLOB 字段为空！");
			return -1;
		}

		if(!blob.isInitialized())
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"BLOG 字段未初始化！");
			return -1;
		}

		blobLength=blob.length();
		
		if(blobLength<0)
		{
			remark.doLog(LOGLEVEL_SHOWERROR,"BLOB 字段大小为负！");
			return -1;
		}
// 		if(!blob.isNull())
// 			if(blob.isInitialized())
// 			{
// 				blobLength=blob.length();
// 				if(blobLength>0)

		if(blobLength==0)
		{
// 			remark.doLog((LOGLEVEL_SHOWWARNING,"BLOB 字段长度为 0。"))
			return -1;
		}
		
		blob.read(blobLength,blobData,blobLength);

		// 			}
// 	}
// 	catch(SQLException e)
// 	{
// 		CString s=e.getMessage().c_str();
// 		AfxMessageBox(s);
// 		printf("GetBlob error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeRecordSet();
// 		closeStmt();
// 		return -1;
// 	}
// 	catch(...)
// 	{
// 		errMsg="GetBlob error : Unknown error.\n";
// 		printf(errMsg);
// 		closeRecordSet();
// 		closeStmt();
// 		return -1;
// 	}

	return blobLength;
}

// 更新BLOB，使用了内部的rs记录集，会直接向下移动一下
// 上层代码不需要移动一下了
BOOL COCCIWrapper::updateBlob(int blobCount,...)
{
	if(blobCount<=0) return FALSE;
	if(!rs) return FALSE;

	int skipBlob=0;

// 	try
// 	{
		if(!rs->next()) return FALSE;

		remark.doLog(LOGLEVEL_SHOWDEBUG,"更新BLOB");
		va_list argptr;     //你的类型链表
		va_start(argptr,blobCount);//初始化你的marker链表

		Blob blob;
		int blobLen=0;

		for(int i=1;i<=blobCount;i++)
		{
			blobLen = va_arg( argptr, int );
			if(blobLen<=0)
			{
				remark.doLog(LOGLEVEL_SHOWDEBUG,"该Blob长度非正，跳过。");
				skipBlob++;
				va_arg( argptr, unsigned char* );
				continue;
// 				remark.doLog(LOGLEVEL_SHOWERROR,"Blob长度非正！");
//				throw CMyException("e","0",className,classCode,"UpdateBlob","03","01","更新Blob失败！","Blob长度非正！",1);
// 				closeRecordSet();
// 				closeStmt();
// 				exit(-1);
// 				va_end(argptr);//结束，与va_start合用
// 				return FALSE;
			}
			blob=rs->getBlob(i);
			blob.write(blobLen,va_arg( argptr, unsigned char* ),blobLen);
		}

		remark.doLog(LOGLEVEL_SHOWDEBUG,"Blob 更新完毕");
		va_end(argptr);//结束，与va_start合用

// 	}
// 	catch(SQLException e)
// 	{
// 		//errMsg=e.getMessage().c_str();
// 		printf("UpdateBlob error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		closeRecordSet();
// 		closeStmt();
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="UpdateBlob error : Unknown error.\n";
// 		printf(errMsg);
// 		closeRecordSet();
// 		closeStmt();
// 		return FALSE;
// 	}
	
	return TRUE;
}

// 关闭记录集
BOOL COCCIWrapper::closeRecordSet()
{
	if(stmt)
		if(rs)
		{
// 			try
// 			{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭记录集");
				stmt->closeResultSet(rs);
				rs=NULL;
// 			}
// 			catch(SQLException e)
// 			{
// 				//errMsg=e.getMessage().c_str();
// 				printf("CloseResultSet error!\n errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 				rs=NULL;
// 				closeStmt();
// 				return FALSE;
// 			}
// 			catch(...)
// 			{
// 				errMsg="CloseResultSet error : Unknown error.\n";
// 				printf(errMsg);
// 				rs=NULL;
// 				closeStmt();
// 				return FALSE;
// 			}
		}
		
	return TRUE;
}

BOOL COCCIWrapper::closeRecordSet(Statement *stmt, ResultSet *rs)
{
	if(stmt)
		if(rs)
		{
			remark.doLog(LOGLEVEL_SHOWDEBUG,"关闭记录集");
			stmt->closeResultSet(rs);
			rs=NULL;
		}

		return TRUE;
}

BOOL COCCIWrapper::Commit()
{	
	if (!conn) return FALSE;
	
// 	try
// 	{
	remark.doLog(LOGLEVEL_SHOWDEBUG,"数据库事务提交");
		conn->commit();
// 	}
// 	catch(SQLException e)
// 	{
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		return FALSE;
// 	}
	return TRUE;
}

BOOL COCCIWrapper::Rollback()
{
	if(!conn) return FALSE;
	
// 	try
// 	{
	remark.doLog(LOGLEVEL_SHOWDEBUG,"数据库事务回滚");
		conn->rollback();
// 	}
// 	catch(SQLException e)
// 	{
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		return FALSE;
// 	}
	return TRUE;
}

// BOOL COCCIWrapper::Insert(const char *sql, ...)
// {
// // 'S' string 'N' number
// 	if(!sql) return FALSE;
// 	const char *tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2; 
// 	}
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"Insert","02","01","插入失败！","创建Statement失败！",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 		va_list argptr;     //你的类型链表
// 		va_start(argptr,sql);//初始化你的marker链表
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"Insert","02","02","参数有误！","未知参数",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//结束，与va_start合用
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// 			}
// 		}
// 		stmt->execute();
// 		va_end(argptr);//结束，与va_start合用
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Insert2table error : Unknown error.\n";
// 		printf(errMsg);
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// BOOL COCCIWrapper::Update(const char *sql, ...)
// {
// 	if(!sql) return FALSE;
// 
// 	const char * tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2;
// 	}
// 
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"Update","03","01","更新失败！","创建Statement失败！",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 		va_list argptr;     //你的类型链表
// 		va_start(argptr,sql);//初始化你的marker链表
// // 		Blob *pblob;
// 	//	int k;
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			int tmp = 0 ;
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// // 			case 'B':
// // 			case 'b':
// // 				//stmt->setAutoCommit(true);
// // 				tmp = va_arg( argptr, int );
// // 				pblob = new Blob(conn);
// // 				if(!pblob) return FALSE;
// // 				*pblob=stmt->getBlob(i);
// // 				pblob->setEmpty();
// // 	// 			k = pblob->isInitialized();
// // 	// 			k = pblob->isOpen();
// // 	// 			k= pblob->length();
// // 				pblob->write(tmp,va_arg( argptr, unsigned char* ),tmp);
// // 				stmt->setBlob(i,*pblob);
// // 				i--;
// // 				pblob->close();
// // 				delete pblob;
// // 				//printf("%s\n",va_arg( argptr, char* ));
// // 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"Update","03","01","参数有误！","未知参数",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//结束，与va_start合用
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// 			}
// 		}
// 		va_end(argptr);//结束，与va_start合用
// 		stmt->executeUpdate();
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Insert2table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Update2table error : Unknown error.\n";
// 		printf(errMsg);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// BOOL COCCIWrapper::UpdateBlob(int blobCount,const char *sql, ...)
// {
// 	if(blobCount<=0) return FALSE;
// 	if(!sql) return FALSE;
// 
// 	Statement *stmt;
// 
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// //		if(!stmt) {printf("UpdateBlob fail : can not create statement!");return FALSE;}
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"UpdateBlob","04","01","更新Blob失败！","创建Statement失败！",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 
// 		va_list argptr;     //你的类型链表
// 		va_start(argptr,sql);//初始化你的marker链表
// 
// 		ResultSet* rs=stmt->executeQuery();
// 		if(!rs)
// 		{
// 			throw CMyException("e","0",className,classCode,"UpdateBlob","04","02","更新Blob失败！","执行查询失败，记录集为空！",1);
// 			if(!stmt)
// 				conn->terminateStatement (stmt);
// 			exit(-1);
// 			return FALSE;
// 		}
// // 		{
// // 			printf("UpdateBlob fail : can not create resultset!");
// // 			if(!stmt)
// // 				conn->terminateStatement (stmt);
// // 			return FALSE;
// // 		}
// 
// 		Blob blob;
// 		int blobLen=0;
// 		if(rs->next())
// 		{
// 			for(int i=1;i<=blobCount;i++)
// 			{
// 				blobLen = va_arg( argptr, int );
// 				if(blobLen<=0)
// 				{
// 					throw CMyException("e","0",className,classCode,"UpdateBlob","04","03","更新Blob失败！","Blob长度非正！",1);
// 					if(!stmt)
// 						conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// // 				{
// // 					printf("UpdateBlob fail : bloLen <= 0 !");
// // 					if(!stmt)
// // 						conn->terminateStatement (stmt);
// // 					return FALSE;
// // 				}
// 				blob=rs->getBlob(i);
// // 				if(!blob)
// // 				{
// // 					throw CMyException("e","0",className,classCode,"UpdateBlob","04","04","更新Blob失败！","获取Blob失败！",1);
// // 					if(!stmt)
// // 						conn->terminateStatement (stmt);
// // 					exit(-1);
// // 					return FALSE;
// // 				}
// // 				{
// // 					printf("UpdateBlob fail : getBlob() returns NULL!");
// // 					if(!stmt)
// // 						conn->terminateStatement (stmt);
// // 					return FALSE;
// // 				}
// // 				blob->write(blobLen,va_arg( argptr, unsigned char* ),blobLen);
// 				blob.write(blobLen,va_arg( argptr, unsigned char* ),blobLen);
// 			}
// 		}
// 		stmt->executeUpdate();
// 		stmt->closeResultSet(rs);
// 		va_end(argptr);//结束，与va_start合用
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("UpdateBlob errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage());
// 		va_end(argptr);//结束，与va_start合用
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="UpdateBlob error : Unknown error.\n";
// 		printf(errMsg);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// BOOL COCCIWrapper::tdelete(const char * sql,...)
// {
// 	// 'S' string 'N' number
// 	if(!sql) return FALSE;
// 	const char *tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2; 
// 	}
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return FALSE;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"tdelete","05","01","删除失败！","创建Statement失败！",1);
// 			exit(-1);
// 			return FALSE;
// 		}
// 		va_list argptr;     //你的类型链表
// 		va_start(argptr,sql);//初始化你的marker链表
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"tdelete","05","02","参数有误！","未知参数",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//结束，与va_start合用
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return FALSE;
// 				}
// 			}
// 		}
// 		stmt->execute();
// 		va_end(argptr);//结束，与va_start合用
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Delete from table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Delete from table error : Unknown error.\n";
// 		printf(errMsg);
// 		conn->terminateStatement (stmt);
// 		return FALSE;
// 	}
// 	conn->terminateStatement (stmt);
// 	return TRUE;
// }
// 
// ResultSet *COCCIWrapper::query(const char * sql,...)
// {
// 	if(!sql) return FALSE;
// 	const char *tmp = sql;
// 	int icount = 0 ;
// 	while(*tmp)
// 	{
// 		if(*tmp++ == ':' ) icount +=2; 
// 	}
// 	Statement *stmt;
// 	try
// 	{
// 		if(!conn) return NULL;
// 		stmt = conn->createStatement (sql);
// 		if(!stmt)
// 		{
// 			throw CMyException("e","0",className,classCode,"tdelete","05","01","查询失败！","创建Statement失败！",1);
// 			exit(-1);
// 			return NULL;
// 		}
// 		va_list argptr;     //你的类型链表
// 		va_start(argptr,sql);//初始化你的marker链表
// 		for(int i = 1 ; i <= icount/2 ; i ++ )
// 		{
// 			char *s = va_arg( argptr, char* );
// 			switch (*s)
// 			{
// 			case 'S':
// 			case 's':
// 				stmt->setString (i,va_arg( argptr, char* ));
// 				//printf("%s\n",va_arg( argptr, char* ));
// 				break;
// 			case 'N':
// 			case 'n':
// 				stmt->setInt(i,va_arg( argptr, int ));
// 				//printf("%d\n",va_arg( argptr,int ));
// 				break;
// 			default:
// 				{
// 					throw CMyException("e","0",className,classCode,"tdelete","05","02","参数有误！","未知参数",1);
// 					//printf("unknown para type %s \n" ,s);
// 					va_end(argptr);//结束，与va_start合用
// 					conn->terminateStatement (stmt);
// 					exit(-1);
// 					return NULL;
// 				}
// 			}
// 		}
// 		ResultSet* rs=stmt->executeQuery();
// 		if(!rs)
// 		{
// 			throw CMyException("e","0",className,classCode,"UpdateBlob","05","03","查询失败！","执行查询失败，记录集为空！",1);
// 			if(!stmt)
// 				conn->terminateStatement (stmt);
// 			exit(-1);
// 			return NULL;
// 		}
// 		// 		stmt->execute();
// 		va_end(argptr);//结束，与va_start合用
// 	}
// 	catch(SQLException e)
// 	{
// 		errMsg=e.getMessage().c_str();
// 		printf("Delete from table errnum %d errmsg %s\n",e.getErrorCode(),e.getMessage().c_str());
// 		conn->terminateStatement (stmt);
// 		return NULL;
// 	}
// 	catch(...)
// 	{
// 		errMsg="Delete from table error : Unknown error.\n";
// 		printf(errMsg);
// 		conn->terminateStatement (stmt);
// 		return NULL;
// 	}
// 	conn->terminateStatement (stmt);
// 	return rs;
// }
