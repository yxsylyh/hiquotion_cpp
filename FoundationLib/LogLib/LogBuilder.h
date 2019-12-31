// LogBuilder.h: interface for the CLogBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGBUILDER_H__F294BB61_6EFB_4FFE_A174_0E758A5B3352__INCLUDED_)
#define AFX_LOGBUILDER_H__F294BB61_6EFB_4FFE_A174_0E758A5B3352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogList.h"
#include "LogBuilderBase.h"
#include "LogConfig.h"
#include "FileLog.h"
#include "ScreenLog.h"
#include "logliblog.h"

class CLogBuilder : CLogBuilderBase
{
public:
	CLogBuilder(CLogList *logList, string path);
	virtual ~CLogBuilder();

	CLogConfig logConfig;

	CString m_Path;
	
	CFileLog *fileLog;
	CScreenLog *screenLog;

};

#endif // !defined(AFX_LOGBUILDER_H__F294BB61_6EFB_4FFE_A174_0E758A5B3352__INCLUDED_)
