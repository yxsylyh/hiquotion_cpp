// Remark.cpp: implementation of the CRemark class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Remark.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRemark::CRemark()
:logs(0),logBuilder(0)
{
	char *folder="Logs";

	logs=new CLogList();
	CString path=CFolderOperation::GetModulePath();

	logBuilder=new CLogBuilder(logs,path.GetBuffer(path.GetLength()));

	string logpath=(LPTSTR)(LPCSTR)logBuilder->m_Path;
	logpath+="_db";
//	mtLog=new CMTFileLog(logpath,".log",logBuilder->logConfig.getFileLogOverwritten(),logBuilder->logConfig.getShowTimeBeforeLevel());
	mtLog=NULL;    // 等更新到1.5版本的时候，把这行注释掉，上面行放开注释
}

CRemark::~CRemark()
{
	if(logs)
	{
		delete(logs);
		logs=NULL;
	}
	if(logBuilder)
	{
		delete(logBuilder);
		logBuilder=NULL;
	}

	if(mtLog)
	{
		delete mtLog;
		mtLog=NULL;
	}
}

void CRemark::doLog(string comment)//,BOOL isDebug)
{
	// 	if(isDebug)
	// 		logs->debugWriteLn(comment);
	// 	else
	logs->writeLn(comment);
}

void CRemark::doLog(LogLevel loglevel,string comment)
{
	// 	if(loglevel>=currLogLevel)
	logs->writeLn(loglevel,comment);
}

