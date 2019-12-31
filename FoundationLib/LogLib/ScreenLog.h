// ScreenLog.h: interface for the CScreenLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENLOG_H__F93856AC_8F05_47BD_98F3_A47CA5148869__INCLUDED_)
#define AFX_SCREENLOG_H__F93856AC_8F05_47BD_98F3_A47CA5148869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ILog.h"

#define MAX_MSG_LEN 2000

class CScreenLog : public ILog  
{
public:
	CScreenLog(BOOL ShowTimeBeforeLevel=FALSE);
	virtual ~CScreenLog();

	virtual string getLogName();
	
	void setLogLevel(LogLevel level);
	static LogLevel getDefaultLogLevel();     // æ≤Ã¨ µœ÷

	void write(string logMsg);
	void writeLn(string logMsg);
	
	void write(LogLevel expectedLevel,string logMsg);
	void writeLn(LogLevel expectedLevel,string logMsg);

// 	void debugWrite(string logMsg);
// 	void debugWriteLn(string logMsg);
private:
	LogLevel m_level;
	BOOL m_ShowTimeBeforeLevel;
};

#endif // !defined(AFX_SCREENLOG_H__F93856AC_8F05_47BD_98F3_A47CA5148869__INCLUDED_)
