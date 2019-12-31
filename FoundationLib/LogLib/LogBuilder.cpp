// LogBuilder.cpp: implementation of the CLogBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogBuilder.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogBuilder::CLogBuilder(CLogList *logList, string path)
:fileLog(NULL),screenLog(NULL)
{
	m_Path=CFolderOperation::addGang(path.c_str());

	// 如果创建屏幕日志，
	if(logConfig.getCreateScreenLog())
	{
		screenLog=new CScreenLog(logConfig.getShowTimeBeforeLevel());
		// 如果忽略屏幕日志的级别设置
		if(CLogBuilderBase::m_ignoreLogLevelinConfig)
			screenLog->setLogLevel(CScreenLog::getDefaultLogLevel());
		else
			screenLog->setLogLevel(logConfig.getScreenLogLevel());

		// 添加到日志列表
		logList->add((ILog *)screenLog);
	}

	// 如果创建文件日志
	if(logConfig.getCreateFileLog())
	{
// 		; 日志文件名（不带扩展名，扩展名为.log）
// 		LogFileName=log
// 		; 日志文件名是否加日期后缀
// 		LogFileNameAddDate=
// 		; 可以把日志文件创建的日志放到一个子文件夹中，指定子文件夹名（SubFolderName=），若为空则在同目录内创建文件日志。
// 		SubFolderName=Logs
// 		; 是否覆写（否则为追加内容）
// 		FileLogOverwritten=

		// 是否把文件日志放到子文件夹内
		string subFolder=logConfig.getSubFolderName();
		if(subFolder!="")
		{
			m_Path += subFolder.c_str();
			m_Path += "\\";

			// 如果没创建子文件夹，则创建
			if(!CFolderOperation::isFolderExist(m_Path))
				CFolderOperation::createDir(m_Path);
		}

		// 获取设置的日志文件名（不包括扩展名）
		string logFileName=logConfig.getLogFileName();
		if(logFileName=="")
			m_Path += "mylog";
		else
			m_Path += logFileName.c_str();

		// 文件名后是否添加日志
		if(logConfig.getLogFileNameAddDate())
		{
			CTime time=CTime::GetCurrentTime();
			CString strTime;
			strTime.Format("_%.4d%.2d%.2d",time.GetYear(),time.GetMonth(),time.GetDay());
			m_Path += strTime;
		}

		BOOL isOverWritten=logConfig.getFileLogOverwritten();
		fileLog=new CFileLog(m_Path.GetBuffer(m_Path.GetLength()),".log",isOverWritten,logConfig.getShowTimeBeforeLevel());

		// 设置文件日志级别
		if(CLogBuilderBase::m_ignoreLogLevelinConfig)
			fileLog->setLogLevel(CFileLog::getDefaultLogLevel());
		else
			fileLog->setLogLevel(logConfig.getFileLogLevel());
		
		// 向LogHelper中添加日志类
		logList->add((ILog *)fileLog);
	}

}

CLogBuilder::~CLogBuilder()
{
	if(fileLog)
	{
		delete(fileLog);
		fileLog=NULL;
	}

	if(screenLog)
	{
		delete(screenLog);
		screenLog=NULL;
	}
}
