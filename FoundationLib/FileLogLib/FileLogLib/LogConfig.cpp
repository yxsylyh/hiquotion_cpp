// LogConfig.cpp: implementation of the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "LogLibLog.h"
#include "LogConfig.h"
#include <algorithm>
#include "LogLevel.h"
#include <C++\FoundationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// extern CLogLibLog loglibLog;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogConfig::CLogConfig(std::string configName)
{
	CString logPath=CFolderOperation::addGang(CFolderOperation::GetModulePath())+"log.xml";
	m_xmlOperation=new CXmlOperation((LPTSTR)(LPCSTR)logPath);
	if(!m_xmlOperation->isOpenSuccess())
	{
		AfxMessageBox("打开 log.xml 文件失败！");
	}

	m_showTimeBeforeLevel=getShowTime();
	m_fileLogLevel=getLevel();
	m_logFileName=getLogName();
	m_logFileNameAddDate=getFileNameWithDate();
	m_subFolderName=getSubFolder();
	m_fileLogOverwritten=getOverwritten();

}

CLogConfig::~CLogConfig()
{
	delete m_xmlOperation;
}

//	是否在每条日志前显示时间
bool CLogConfig::getShowTime()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("showTime");  // 获取节点
	if(!element)
		return true;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		return true;
	
	// 转为小写
	std::transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return true;
	else if(result=="false")
		return false;
	else
		return true;
}

//	设置文件日志输出级别
LogLevel CLogConfig::getLevel()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("level");  // 获取节点
	if(!element)
		m_fileLogLevel=LOGLEVEL_SHOWINFO;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		m_fileLogLevel=LOGLEVEL_SHOWINFO;
	
	// 转为大写
	std::transform(result.begin(),result.end(),result.begin(),toupper);
	
	return CLogLevel::String2LogLevel(result);
}

//	日志文件名（不带扩展名，扩展名为.log）
std::string CLogConfig::getLogName()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("fileName");  // 获取节点
	if(!element)
		return "";
	
	std::string result=m_xmlOperation->getElementText(element);
	return result;
}

//	日志文件名是否加日期后缀
bool CLogConfig::getFileNameWithDate()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("fileNameWithDate");  // 获取节点
	if(!element)
		return true;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		return true;
	// 转为小写
	std::transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return true;
	else if(result=="false")
		return false;
	else
		return false;
}

//	可以把日志文件创建的日志放到一个子文件夹中，指定子文件夹名（SubFolderName=），若为空则在同目录内创建文件日志。
std::string CLogConfig::getSubFolder()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("subFolderName");  // 获取节点
	if(!element)
		return "";
	
	std::string result=m_xmlOperation->getElementText(element);
	return result;
}

//	是否覆写（否则为追加内容）
bool CLogConfig::getOverwritten()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("overwrite");  // 获取节点
	if(!element)
		return false;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		return false;

	// 转为小写
	std::transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return true;
	else if(result=="false")
		return false;
	else
		return false;
}
