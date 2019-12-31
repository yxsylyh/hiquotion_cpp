// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__802AB3A6_91F1_45FF_B13D_1C14304CC771__INCLUDED_)
#define AFX_LOG_H__802AB3A6_91F1_45FF_B13D_1C14304CC771__INCLUDED_

#include "LogBuilder.h"
#include "FileLog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*

  若使用文件日志类，请使用本类，本类是日志类的入口

  需要先定义该类的对象

*/

class CLog  
{
public:
	CLog();
	CLog(std::string m_projectName);
	virtual ~CLog();

	// 设置工程名
	void setProjectName(std::string projectName);

	void write(std::string logMsg);
	void writeLn(std::string logMsg);
	
	void write(LogLevel expectedLevel, std::string logMsg);
	void writeLn(LogLevel expectedLevel, std::string logMsg);
	
	void writeException(int code, std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	void writeException(std::string message, std::string fromMethod="", std::string fromClass="");
	void writeInfo(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	void writeWarning(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	void writeDebug(std::string message, std::string fromMethod="", std::string fromClass="", std::string fromProject="");
	
	void writeLogHead();
	void writeLogEnd();

private:
	std::string m_projectName;

	CLogBuilder logBuilder;
	CFileLog *fileLog;

};

#endif // !defined(AFX_LOG_H__802AB3A6_91F1_45FF_B13D_1C14304CC771__INCLUDED_)
