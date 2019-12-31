// LogConfig.h: interface for the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
#define AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogLevel.h"
#include "XmlOperation.h"

class CLogConfig  
{
public:
	CLogConfig(std::string configName="log.xml");
	virtual ~CLogConfig();

	bool getShowTimeBeforeLevel() const { return m_showTimeBeforeLevel; }
// 	void setShowTimeBeforeLevel(bool val) { m_showTimeBeforeLevel = val; }
	LogLevel getLogLevel() const { return m_fileLogLevel; }
	std::string getLogFileName() const { return m_logFileName; }
// 	void setLogFileName(string val) { m_logFileName = val; }
	bool getLogFileNameAddDate() const { return m_logFileNameAddDate; }
// 	void setLogFileNameAddDate(bool val) { m_logFileNameAddDate = val; }
	std::string getSubFolderName() const { return m_subFolderName; }
// 	void setSubFolderName(string val) { m_subFolderName = val; }
	bool getFileLogOverwritten() const { return m_fileLogOverwritten; }
// 	void setFileLogOverwritten(bool val) { m_fileLogOverwritten = val; }

private:

//	是否在每条日志前显示时间
	bool getShowTime();

//	设置文件日志输出级别
	LogLevel getLevel();

//	日志文件名（不带扩展名，扩展名为.log）
	std::string getLogName();

//	日志文件名是否加日期后缀
	bool getFileNameWithDate();

//	可以把日志文件创建的日志放到一个子文件夹中，指定子文件夹名（SubFolderName=），若为空则在同目录内创建文件日志。
	std::string getSubFolder();

//	是否覆写（否则为追加内容）
	bool getOverwritten();

private:
	CXmlOperation *m_xmlOperation;
	
	bool m_showTimeBeforeLevel;
	LogLevel m_fileLogLevel;
	std::string m_logFileName;
	bool m_logFileNameAddDate;
	std::string m_subFolderName;
	bool m_fileLogOverwritten;
};

#endif // !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
