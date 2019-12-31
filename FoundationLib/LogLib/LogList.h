// LogHelper.h: interface for the CLogList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGHELPER_H__C6481C79_1672_4B87_8B9E_7A01DA5ADE9A__INCLUDED_)
#define AFX_LOGHELPER_H__C6481C79_1672_4B87_8B9E_7A01DA5ADE9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ILog.h"
#include <list>

class CLogList //: public ILog  
{
public:
	CLogList();
	virtual ~CLogList();

	void write(string logMsg);
	void writeLn(string logMsg);

	void write(LogLevel expectedLevel,string logMsg);
	void writeLn(LogLevel expectedLevel,string logMsg);

// 	// 下面的方法用于DEBUG环境
// 	void debugWrite(string logMsg);
// 	void debugWriteLn(string logMsg);
	
	void add(ILog *log);
// 	int remove(string name);
	
private:
	list<ILog *> logs;
};

#endif // !defined(AFX_LOGHELPER_H__C6481C79_1672_4B87_8B9E_7A01DA5ADE9A__INCLUDED_)
