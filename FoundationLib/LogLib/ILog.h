// ILog.h: interface for the ILog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILOG_H__7AB09502_335E_4CB4_B0C0_A6E6ABC1D5A6__INCLUDED_)
#define AFX_ILOG_H__7AB09502_335E_4CB4_B0C0_A6E6ABC1D5A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// enum enumLogLevel
// {
// 	//	LOGLEVEL_SHOWALL,           // 显示所有日志内容
// 	LOGLEVEL_SHOWDEBUG,         // 在自己调试程序时需要输出的，比如变量内容等
// 	//	LOGLEVEL_SHOWRELEASEDEBUG,  // 在程序交付使用的时候，显示的便于程序差错的调试信息，这个信息在 Release 版本中仍可以显示
// 	LOGLEVEL_SHOWINFO,          // 显示信息
// 	LOGLEVEL_SHOWWARNING,       // 显示警告信息
// 	LOGLEVEL_SHOWERROR,         // 显示错误信息
// 	//	LOGLEVEL_SHOWLOGONLY,       // 仅显示日志内容
// 
// 	// 在程序稳定后，一般设置为 LOGLEVEL_SHOWWARNING 即可。
// };
// 
// typedef enumLogLevel LogLevel;

// #include <LogLib\LogLevel.h>

#include <C++\FoudationLib\Interface.h>

#include "LogLevel.h"
#include <string>

using namespace std;

MyInterface ILog  
{
public:
	ILog();
	virtual ~ILog();

	virtual void setLogLevel(LogLevel level);

	virtual void write(std::string logMsg);
	virtual void writeLn(std::string logMsg);

	virtual void write(LogLevel expectedLevel, std::string logMsg);
	virtual void writeLn(LogLevel expectedLevel, std::string logMsg);

// 	virtual void debugWrite(string logMsg)=0;
// 	virtual void debugWriteLn(string logMsg)=0;


};

#endif // !defined(AFX_ILOG_H__7AB09502_335E_4CB4_B0C0_A6E6ABC1D5A6__INCLUDED_)
