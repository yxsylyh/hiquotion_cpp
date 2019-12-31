// Remark.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Log.h"
#include <c++\FoundationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog::CLog()
{
	m_projectName="";

	fileLog=logBuilder.getFileLog();
}

CLog::CLog(std::string projectName)
:m_projectName(projectName)
{
	fileLog=logBuilder.getFileLog();
}

CLog::~CLog()
{

}

// 设置工程名
void CLog::setProjectName(std::string projectName)
{
	m_projectName=projectName;
}

void CLog::write(std::string logMsg)
{
	if(fileLog)
		fileLog->write(logMsg);
}

void CLog::writeLn(std::string logMsg)
{
	if(fileLog)
		fileLog->writeLn(logMsg);
}

void CLog::write(LogLevel expectedLevel, std::string logMsg)
{
	if(fileLog)
		fileLog->write((expectedLevel,logMsg));
}

void CLog::writeLn(LogLevel expectedLevel, std::string logMsg)
{
	if(fileLog)
		fileLog->writeLn(expectedLevel,logMsg);
}

void CLog::writeException(int code, std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	if(fileLog)
		fileLog->writeException(code,message,fromMethod,fromClass,fromProject);
}

void CLog::writeInfo(std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	if(fileLog)
		fileLog->writeInfo(message,fromMethod,fromClass,fromProject);
}

void CLog::writeWarning(std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	if(fileLog)
		fileLog->writeWarning(message,fromMethod,fromClass,fromProject);
}

void CLog::writeDebug(std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	if(fileLog)
		fileLog->writeDebug(message,fromMethod,fromClass,fromProject);
}

void CLog::writeException(std::string message, std::string fromMethod, std::string fromClass)
{
	if(fileLog)
		fileLog->writeException(message,fromMethod,fromClass,m_projectName);
}

void CLog::writeLogHead()
{
	if(!fileLog)
		return;

	fileLog->writeLn("===================================");
	
	if(m_projectName.size()>0)
	{
		fileLog->write(m_projectName);
		fileLog->writeLn(" 程序开始");
	}
	else
		fileLog->writeLn("程序开始");

	CTime time=CTime::GetCurrentTime();
	CString stime=time.Format("%Y-%m-%d %X");
#ifdef _UNICODE
	fileLog->writeLn((LPCSTR)stime.GetBuffer(stime.GetLength()));
#else
	fileLog->writeLn((LPTSTR)(LPCSTR)stime);
#endif
}

void CLog::writeLogEnd()
{
	if(!fileLog)
		return;
	
	fileLog->writeLn("程序退出");
	fileLog->writeLn("===================================");
	// 输出空行
	fileLog->writeLn("");
}
