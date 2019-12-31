// LogLibLog.h: interface for the CLogLibLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGLIBLOG_H__96B20095_33CC_4DC0_AA58_42E0B286DDC4__INCLUDED_)
#define AFX_LOGLIBLOG_H__96B20095_33CC_4DC0_AA58_42E0B286DDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileLog.h"


class CLogLibLog  
{
public:
	CLogLibLog();
	virtual ~CLogLibLog();

	void doLog(LogLevel level,string msg);

private:
	CFileLog *log;
};

#endif // !defined(AFX_LOGLIBLOG_H__96B20095_33CC_4DC0_AA58_42E0B286DDC4__INCLUDED_)
