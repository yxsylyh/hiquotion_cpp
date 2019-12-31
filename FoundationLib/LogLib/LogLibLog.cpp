// LogLibLog.cpp: implementation of the CLogLibLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogLibLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogLibLog::CLogLibLog() : log(NULL)
{

}

CLogLibLog::~CLogLibLog()
{
	if(log)
	{
		delete(log);
		log=NULL;
	}
}

void CLogLibLog::doLog(LogLevel level,string msg)
{
	if(!log)
	{
		log=new CFileLog("LogLib",".log",TRUE,TRUE);
		log->setLogLevel(LOGLEVEL_SHOWWARNING);
	}

	log->writeLn(level,msg);
}
