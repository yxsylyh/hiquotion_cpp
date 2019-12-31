// LogLevel.h: interface for the CLogLevel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGLEVEL_H__AF5D0C92_6802_4712_9F7D_471B37E3B627__INCLUDED_)
#define AFX_LOGLEVEL_H__AF5D0C92_6802_4712_9F7D_471B37E3B627__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

enum eLogLevel
{
//	LOGLEVEL_SHOWALL,           // 显示所有日志内容
	LOGLEVEL_SHOWDEBUG,         // 在自己调试程序时需要输出的，比如变量内容等
//	LOGLEVEL_SHOWRELEASEDEBUG,  // 在程序交付使用的时候，显示的便于程序差错的调试信息，这个信息在 Release 版本中仍可以显示
	LOGLEVEL_SHOWINFO,          // 显示信息
	LOGLEVEL_SHOWWARNING,       // 显示警告信息
	LOGLEVEL_SHOWERROR,         // 显示错误信息
//	LOGLEVEL_SHOWLOGONLY,       // 仅显示日志内容

// 在程序稳定后，一般设置为 LOGLEVEL_SHOWWARNING 即可。
};

typedef eLogLevel LogLevel;

class CLogLevel  
{
public:
	CLogLevel();
	virtual ~CLogLevel();

	static std::string LogLevel2String(LogLevel level);
	static LogLevel String2LogLevel(std::string level);

};

#endif // !defined(AFX_LOGLEVEL_H__AF5D0C92_6802_4712_9F7D_471B37E3B627__INCLUDED_)
