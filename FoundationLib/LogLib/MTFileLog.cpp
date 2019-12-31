#include "stdafx.h"
#include "MTFileLog.h"
#include "filelog.h"

CMTFileLog::CMTFileLog(string logFile, string extName, BOOL isOverWritten,BOOL ShowTimeBeforeLevel)
: CFileLog(logFile, extName, isOverWritten, ShowTimeBeforeLevel)
{
}

CMTFileLog::~CMTFileLog(void)
{
}

void CMTFileLog::write(LogLevel expectedLevel,string logMsg, DWORD threadID)
{
	if(expectedLevel>=CFileLog::m_level)
	{
		CString stime="";
		string msg="";
		if(CFileLog::m_ShowTimeBeforeLevel)
		{
			CTime time=CTime::GetCurrentTime();
			stime.Format("[Thread %d] %s",threadID,time.Format("%Y-%m-%d %X"));
			msg=stime.GetBuffer(stime.GetLength());
			msg+= " - ";
		}
		msg+=CLogLevel::LogLevel2String(expectedLevel)+logMsg;
		CFileLog::write(msg);
	}
}

void CMTFileLog::writeLn(LogLevel expectedLevel,string logMsg, DWORD threadID)
{
	if(expectedLevel>=CFileLog::m_level)
	{
		string msg=logMsg+"\n";
		write(expectedLevel,msg,threadID);
	}
}
