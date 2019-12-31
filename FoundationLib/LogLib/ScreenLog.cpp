// ScreenLog.cpp: implementation of the CScreenLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScreenLog.h"
#include "LogLevel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScreenLog::CScreenLog(BOOL ShowTimeBeforeLevel) : m_level(LOGLEVEL_SHOWDEBUG), m_ShowTimeBeforeLevel(ShowTimeBeforeLevel)
{

}

CScreenLog::~CScreenLog()
{

}

string CScreenLog::getLogName()
{
	return "CScreenLog";
}

void CScreenLog::setLogLevel(LogLevel level)
{
	m_level=level;
}

LogLevel CScreenLog::getDefaultLogLevel()
{
	return LOGLEVEL_SHOWWARNING;
}

void CScreenLog::write(string logMsg)
{
// 	char str[MAX_MSG_LEN]={0};
// 	sprintf(str,"%s\n",logMsg);
	try
	{
// 		CString tmp=logMsg.c_str();
		printf("%s",logMsg.c_str());
	}
	catch (CFileException* e)
	{
		char emsg[MAX_MSG_LEN];
		e->GetErrorMessage(emsg,MAX_MSG_LEN);
		printf("%s\n",emsg);
	}
	catch (CException* e)
	{
		char emsg[MAX_MSG_LEN];
		e->GetErrorMessage(emsg,MAX_MSG_LEN);
		printf("%s\n",emsg);
	}
}

void CScreenLog::writeLn(string logMsg)
{
// 	try
// 	{
// 		log.WriteString("\n");
// 	}
// 	catch (CFileException* e)
// 	{
// 		char emsg[100];
// 		e->GetErrorMessage(emsg,100);
// 		printf("%s\n",emsg);
// 	}
// 	catch (CException* e)
// 	{
// 		char emsg[100];
// 		e->GetErrorMessage(emsg,100);
// 		printf("%s\n",emsg);
// 	}
	string msg=logMsg+"\n";
	write(msg);
}

void CScreenLog::write(LogLevel expectedLevel,string logMsg)
{
	if(expectedLevel>=m_level)
	{
		CString stime="";
		string msg="";
		if(m_ShowTimeBeforeLevel)
		{
			CTime time=CTime::GetCurrentTime();
			stime=time.Format("%Y-%m-%d %X");
			msg=stime.GetBuffer(stime.GetLength());
			msg+= " - ";
		}
		msg+=CLogLevel::LogLevel2String(expectedLevel)+logMsg;
		write(msg);
	}
}

void CScreenLog::writeLn(LogLevel expectedLevel,string logMsg)
{
	if(expectedLevel>=m_level)
	{
		string msg=logMsg+"\n";
		write(expectedLevel,msg);
	}
}


// void CScreenLog::debugWrite(string logMsg)
// {
// #ifdef _DEBUG
// 	write(logMsg);
// #endif
// }
// 
// void CScreenLog::debugWriteLn(string logMsg)
// {
// 	string msg=logMsg+"\n";
// 	debugWrite(msg);
// }
