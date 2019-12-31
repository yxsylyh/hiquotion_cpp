// LogConfig.cpp: implementation of the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "LogLibLog.h"
#include "LogConfig.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>
#include <C++\FoudationLib\FileSysLib\FileOperation.h>
#include <algorithm>
#include "LogLevel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// extern CLogLibLog loglibLog;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogConfig::CLogConfig(string configName)
{
	section="LOG";
	ShowTimeBeforeLevel="ShowTimeBeforeLevel";
	CreateScreenLog="CreateScreenLog";
	ScreenLogLevel="ScreenLogLevel";
	
	CreateFileLog="CreateFileLog";
	FileLogLevel="FileLogLevel";
	LogFileName="LogFileName";
	LogFileNameAddDate="LogFileNameAddDate";
	SubFolderName="SubFolderName";
	FileLogOverwritten="FileLogOverwritten";
	
	appPath=CFolderOperation::GetModulePath();
	config.setFileName((LPTSTR)(LPCTSTR)(appPath + "\\" + configName.c_str()));
	if(!CFileOperation::isFileExist(appPath + "\\" + configName.c_str()))
	{
//		loglibLog.doLog(LOGLEVEL_SHOWERROR,"配置文件 " + configName+ " 不存在！");
		AfxMessageBox(("配置文件 " + configName+ " 不存在！").c_str());
	}
}

CLogConfig::~CLogConfig()
{

}

//	是否在每条日志前显示时间
BOOL CLogConfig::getShowTimeBeforeLevel()
{
	string result=config.getSectionValueString(section,ShowTimeBeforeLevel);
	// 转为小写
	transform(result.begin(),result.end(),result.begin(),tolower);

	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	屏幕日志是否创建
BOOL CLogConfig::getCreateScreenLog()
{
	string result=config.getSectionValueString(section,CreateScreenLog);
	// 转为小写
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	设置屏幕日志输出级别
LogLevel CLogConfig::getScreenLogLevel()
{
	string result=config.getSectionValueString(section,ScreenLogLevel);
	return CLogLevel::String2LogLevel(result);
}

//	文件日志是否创建
BOOL CLogConfig::getCreateFileLog()
{
	string result=config.getSectionValueString(section,CreateFileLog);
	// 转为小写
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	设置文件日志输出级别
LogLevel CLogConfig::getFileLogLevel()
{
	string result=config.getSectionValueString(section,FileLogLevel);
	return CLogLevel::String2LogLevel(result);
}

//	日志文件名（不带扩展名，扩展名为.log）
string CLogConfig::getLogFileName()
{
	return config.getSectionValueString(section,LogFileName);
}

//	日志文件名是否加日期后缀
BOOL CLogConfig::getLogFileNameAddDate()
{
	string result=config.getSectionValueString(section,LogFileNameAddDate);
	// 转为小写
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	可以把日志文件创建的日志放到一个子文件夹中，指定子文件夹名（SubFolderName=），若为空则在同目录内创建文件日志。
string CLogConfig::getSubFolderName()
{
	return config.getSectionValueString(section,SubFolderName);
}

//	是否覆写（否则为追加内容）
BOOL CLogConfig::getFileLogOverwritten()
{
	string result=config.getSectionValueString(section,FileLogOverwritten);
	// 转为小写
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}
