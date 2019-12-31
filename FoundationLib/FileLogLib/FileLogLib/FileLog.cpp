// Log.cpp: implementation of the CFileLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileLog.h"
#include "LogLevel.h"
#include <sstream> 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileLog::CFileLog()
: m_level(LOGLEVEL_SHOWDEBUG), m_isOpen(FALSE)
{
	
}

CFileLog::~CFileLog()
{
	if(!m_isOpen)
		return;

	try
	{
		log.Close();
		m_isOpen=FALSE;
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

BOOL CFileLog::open(std::string logFile, BOOL isOverWritten,BOOL ShowTimeBeforeLevel)
{
	m_ShowTimeBeforeLevel=ShowTimeBeforeLevel;
	try
	{
		if(isOverWritten)
		{
			if(!log.Open(logFile.c_str(),CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
				return FALSE;
		}
		else
		{
			if(!log.Open(logFile.c_str(),CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite))
				return FALSE;

			log.SeekToEnd();
		}
		m_isOpen=TRUE;
	}
	catch (CFileException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
		m_isOpen=FALSE;
	}
	catch (CException* e)
	{
		char emsg[100];
		e->GetErrorMessage(emsg,100);
		printf("%s\n",emsg);
		m_isOpen=FALSE;
	}

	return m_isOpen;
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
	char str[MAX_MSG_LEN]={0};
// 	sprintf(str,"%s\n",logMsg);
	try
	{
		CString tmp=logMsg.c_str();
		log.WriteString(tmp);
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
	std::string msg=logMsg+"\n";
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
		msg+=CLogLevel::LogLevel2String(expectedLevel)+logMsg;
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

void CFileLog::writeException(int code, std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	std::ostringstream ss;
	ss << "(错误码：" << code <<")";
	std::string strCode=ss.str();
	
	std::string msg=strCode + arrangeMsg(message, fromMethod, fromClass, fromProject);
	
	writeLn(LOGLEVEL_SHOWERROR,msg);
}

void CFileLog::writeException(std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	std::string msg=arrangeMsg(message, fromMethod, fromClass, fromProject);
	
	writeLn(LOGLEVEL_SHOWERROR,msg);
}

void CFileLog::writeInfo(std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	std::string msg=arrangeMsg(message, fromMethod, fromClass, fromProject);
	
	writeLn(LOGLEVEL_SHOWINFO,msg);
}

void CFileLog::writeWarning(std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	std::string msg=arrangeMsg(message, fromMethod, fromClass, fromProject);
	
	writeLn(LOGLEVEL_SHOWWARNING,msg);
}

void CFileLog::writeDebug(std::string message, std::string fromMethod, std::string fromClass, std::string fromProject)
{
	std::string msg=arrangeMsg(message, fromMethod, fromClass, fromProject);
	
	writeLn(LOGLEVEL_SHOWDEBUG,msg);
}

std::string CFileLog::arrangeMsg(std::string message, std::string fromMethod/*=""*/, std::string fromClass/*=""*/, std::string fromProject/*=""*/)
{
	std::string msg=message;
	if(fromMethod.size()>0)
		msg+= "\n\t所在方法：" + fromMethod;
	if(fromClass.size()>0)
		msg+= "\n\t所在类：" + fromClass;
	if(fromProject.size()>0)
		msg+= "\n\t所在工程：" + fromProject;

	return msg;
}
