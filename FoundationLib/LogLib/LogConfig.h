// LogConfig.h: interface for the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
#define AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\INILib\IniOperation.h>
#include "LogLevel.h"

class CLogConfig  
{
public:
	CLogConfig(string configName="logconfig.ini");
	virtual ~CLogConfig();

//	是否在每条日志前显示时间
	BOOL getShowTimeBeforeLevel();

//	屏幕日志是否创建
	BOOL getCreateScreenLog();

//	设置屏幕日志输出级别
	LogLevel getScreenLogLevel();

//	文件日志是否创建
	BOOL getCreateFileLog();

//	设置文件日志输出级别
	LogLevel getFileLogLevel();

//	日志文件名（不带扩展名，扩展名为.log）
	string getLogFileName();

//	日志文件名是否加日期后缀
	BOOL getLogFileNameAddDate();

//	可以把日志文件创建的日志放到一个子文件夹中，指定子文件夹名（SubFolderName=），若为空则在同目录内创建文件日志。
	string getSubFolderName();

//	是否覆写（否则为追加内容）
	BOOL getFileLogOverwritten();

private:
	CIniOperation config;
	CString appPath;
	
	char *section;
	char *ShowTimeBeforeLevel;
	char *CreateScreenLog;
	char *ScreenLogLevel;

	char *CreateFileLog;
	char *FileLogLevel;
	char *LogFileName;
	char *LogFileNameAddDate;
	char *SubFolderName;
	char *FileLogOverwritten;
};

#endif // !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
