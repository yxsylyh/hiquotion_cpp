// Log.h: interface for the CFileLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_)
#define AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_MSG_LEN 2000

//////////////////////////////////////////////////////////////////////////
#include "LogLevel.h"
#include <string>

//
// CFileLog 日志类
//
// 用来创建日志文件
//
// 利用构造函数创建日志文件，
// 可以选择是覆盖（isOverWritten=true）还是追加（isOverWritten=false）
//
// 利用 write(),writeLn() 和 debugWrite(),debugWriteLn() 写日志行文本
//
//////////////////////////////////////////////////////////////////////////

class CFileLog  
{
public:
	CFileLog();
	virtual ~CFileLog();

	BOOL open(std::string logFile, BOOL isOverWritten=FALSE,BOOL ShowTimeBeforeLevel=FALSE);
	BOOL isOpen() const { return m_isOpen; }

	virtual std::string getLogName();

	void setLogLevel(LogLevel level);
	static LogLevel getDefaultLogLevel();     // 静态实现

	void write(std::string logMsg);
	void writeLn(std::string logMsg);
	
	void write(LogLevel expectedLevel, std::string logMsg);
	void writeLn(LogLevel expectedLevel, std::string logMsg);

	void writeException(int code, std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	void writeInfo(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	void writeWarning(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	void writeDebug(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");

	void writeException(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");

protected:
	std::string arrangeMsg(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	
private:
	CStdioFile log;
	BOOL m_isOpen;
	LogLevel m_level;
	BOOL m_ShowTimeBeforeLevel;

};

#endif // !defined(AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_)
