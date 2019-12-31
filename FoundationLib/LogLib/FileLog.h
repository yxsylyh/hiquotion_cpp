// Log.h: interface for the CFileLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_)
#define AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_MSG_LEN 2000

#include "ILog.h"
//////////////////////////////////////////////////////////////////////////
//
// CFileLog 日志类
//
// 用来创建日志文件
//
// 继承自 ILog 接口
//
// 利用构造函数创建日志文件，
// 可以选择是覆盖（isOverWritten=true）还是追加（isOverWritten=false）
//
// 利用 write(),writeLn() 和 debugWrite(),debugWriteLn() 写日志行文本
//
//////////////////////////////////////////////////////////////////////////

class CFileLog : public ILog
{
public:
	CFileLog();
	CFileLog(std::string logFile, std::string extName, BOOL isOverWritten=FALSE,BOOL ShowTimeBeforeLevel=FALSE);
	virtual ~CFileLog();

	virtual std::string getLogName();

	void setLogLevel(LogLevel level);
	static LogLevel getDefaultLogLevel();     // 静态实现

	void write(std::string logMsg);
	void writeLn(std::string logMsg);
	
	virtual void write(LogLevel expectedLevel, std::string logMsg);
	virtual void writeLn(LogLevel expectedLevel, std::string logMsg);

// 	void debugWrite(string logMsg);
// 	void debugWriteLn(string logMsg);

protected:
	CStdioFile log;

	LogLevel m_level;
	BOOL m_ShowTimeBeforeLevel;

};

#endif // !defined(AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_)
