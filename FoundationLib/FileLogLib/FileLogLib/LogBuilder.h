// LogBuilder.h: interface for the CLogBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGBUILDER_H__F294BB61_6EFB_4FFE_A174_0E758A5B3352__INCLUDED_)
#define AFX_LOGBUILDER_H__F294BB61_6EFB_4FFE_A174_0E758A5B3352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogConfig.h"
#include "FileLog.h"

class CLogBuilder
{
public:
	CLogBuilder();
	virtual ~CLogBuilder();

	CFileLog *getFileLog(){ return m_log; }


private:
	bool m_ignoreLogLevelinConfig;

	CLogConfig config;
	
	std::string m_logPath;
	
	CFileLog *m_log;
};

#endif // !defined(AFX_LOGBUILDER_H__F294BB61_6EFB_4FFE_A174_0E758A5B3352__INCLUDED_)
