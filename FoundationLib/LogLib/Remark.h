// Remark.h: interface for the CRemark class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REMARK_H__802AB3A6_91F1_45FF_B13D_1C14304CC771__INCLUDED_)
#define AFX_REMARK_H__802AB3A6_91F1_45FF_B13D_1C14304CC771__INCLUDED_

#include "LogBuilder.h"
#include "LogList.h"
#include "MTFileLog.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRemark  
{
public:
	CRemark();
	virtual ~CRemark();

	CLogList *logs;
	CLogBuilder *logBuilder;
	
	void doLog(string comment); //,BOOL isDebug=FALSE);

	// 	void doLog(string comment,...);
	void doLog(LogLevel loglevel,string comment);

	CMTFileLog *mtLog;
};

#endif // !defined(AFX_REMARK_H__802AB3A6_91F1_45FF_B13D_1C14304CC771__INCLUDED_)
