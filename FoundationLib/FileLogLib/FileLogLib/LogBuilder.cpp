// LogBuilder.cpp: implementation of the CLogBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogBuilder.h"
#include <C++\FoundationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogBuilder::CLogBuilder()
:m_log(NULL)
{
	m_logPath=CFolderOperation::addGang(CFolderOperation::GetModulePath());

	// 如果希望忽略配置文件中定义的日志级别，请将其改为 true。
	m_ignoreLogLevelinConfig=false;

	// 创建文件日志
// 		; 日志文件名（不带扩展名，扩展名为.log）
// 		LogFileName=m_log
// 		; 日志文件名是否加日期后缀
// 		LogFileNameAddDate=
// 		; 可以把日志文件创建的日志放到一个子文件夹中，指定子文件夹名（SubFolderName=），若为空则在同目录内创建文件日志。
// 		SubFolderName=Logs
// 		; 是否覆写（否则为追加内容）
// 		FileLogOverwritten=

	// 是否把文件日志放到子文件夹内
	std::string subFolder=config.getSubFolderName();
	if(subFolder!="")
	{
		m_logPath += subFolder.c_str();
		m_logPath += "\\";

		// 如果没创建子文件夹，则创建
		if(!CFolderOperation::isFolderExist(m_logPath.c_str()))
			CFolderOperation::createDir(m_logPath.c_str());
	}

	// 获取设置的日志文件名（不包括扩展名）
	std::string logFileName=config.getLogFileName();
	if(logFileName=="")
		m_logPath += "mylog";
	else
		m_logPath += logFileName.c_str();

	// 文件名后是否添加日期
	if(config.getLogFileNameAddDate())
	{
		CTime time=CTime::GetCurrentTime();
		CString strTime;
		strTime.Format("_%.4d%.2d%.2d",time.GetYear(),time.GetMonth(),time.GetDay());
		m_logPath += strTime;
	}

	// 添加扩展名
	m_logPath += ".log";

	BOOL isOverWritten=config.getFileLogOverwritten();
	m_log=new CFileLog();
	if(!m_log)
		return;

	if(!m_log->open(m_logPath, isOverWritten, config.getShowTimeBeforeLevel()))
		return;

	// 设置文件日志级别
	if(m_ignoreLogLevelinConfig)
		m_log->setLogLevel(CFileLog::getDefaultLogLevel());
	else
		m_log->setLogLevel(config.getLogLevel());
}

CLogBuilder::~CLogBuilder()
{
	if(m_log)
	{
		delete(m_log);
		m_log=NULL;
	}
}
