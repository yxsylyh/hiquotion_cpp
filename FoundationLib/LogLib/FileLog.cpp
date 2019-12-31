// Log.cpp: implementation of the CFileLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileLog.h"
#include "LogLevel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileLog::CFileLog()
: m_level(LOGLEVEL_SHOWDEBUG), m_ShowTimeBeforeLevel(TRUE)
{
	std::string name="ga.log";
	BOOL isOverWritten=TRUE;
	try
	{
		if(isOverWritten)
			log.Open(name.c_str(),CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyWrite);
		else
		{
			log.Open(name.c_str(),CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyWrite);
			log.SeekToEnd();
		}
	}
	catch (CFileException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
	catch (CException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
}

CFileLog::CFileLog(std::string logFile, std::string extName, BOOL isOverWritten, BOOL ShowTimeBeforeLevel)
: m_level(LOGLEVEL_SHOWDEBUG), m_ShowTimeBeforeLevel(ShowTimeBeforeLevel)
{
	std::string name=logFile;
	name+=extName;
	try
	{
		if(isOverWritten)
			log.Open(name.c_str(),CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyWrite);
		else
		{
			log.Open(name.c_str(),CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyWrite);
			log.SeekToEnd();
		}
	}
	catch (CFileException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
	catch (CException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
}

CFileLog::~CFileLog()
{
	try
	{
		log.Close();
	}
	catch (CFileException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
	catch (CException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
}

std::string CFileLog::getLogName()
{
	return "CFileLog";
}

void CFileLog::setLogLevel(LogLevel level)
{
	m_level=level;
}

LogLevel CFileLog::getDefaultLogLevel()
{
	return LOGLEVEL_SHOWINFO;
}

void CFileLog::write(std::string logMsg)
{
// 	char str[MAX_MSG_LEN]={0};
	try
	{
		if(logMsg.length()==0)
			log.WriteString("");
		else
		{
			CString tmp=logMsg.c_str();
			log.WriteString(tmp);
		}
		log.Flush();
	}
	catch (CFileException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
	catch (CException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
	}
}

void CFileLog::writeLn(std::string logMsg)
{
	std::string msg=logMsg;
	msg+="\n";
	write(msg);
}

void CFileLog::write(LogLevel expectedLevel, std::string logMsg)
{
	if(expectedLevel>=m_level)
	{
		CString stime="";
		std::string msg="";
		if(m_ShowTimeBeforeLevel)
		{
			CTime time=CTime::GetCurrentTime();
			stime=time.Format("%Y-%m-%d %X");
			msg=stime.GetBuffer(stime.GetLength());
			msg+= " - ";
		}
		msg+=CLogLevel::LogLevel2String(expectedLevel);
		msg+=logMsg;
		write(msg);
	}
}

void CFileLog::writeLn(LogLevel expectedLevel, std::string logMsg)
{
	if(expectedLevel>=m_level)
	{
		std::string msg=logMsg+"\n";
		write(expectedLevel,msg);
	}
}


// void CFileLog::debugWrite(string logMsg)
// {
// #ifdef _DEBUG
// 	write(logMsg);
// #endif
// }
// 
// void CFileLog::debugWriteLn(string logMsg)
// {
// 	string msg=logMsg+"\n";
// 	debugWrite(msg);
// }
