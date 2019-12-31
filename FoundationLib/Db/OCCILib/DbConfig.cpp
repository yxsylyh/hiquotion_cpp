// DbConfig.cpp: implementation of the CDbConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DbConfig.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbConfig::CDbConfig(string configFileOrWithFullPath)
{
	section="DB";
	user="name";
	pwd="pwd";
	oraName="oraName";

	m_configFile=configFileOrWithFullPath;

	appPath=CFolderOperation::GetModulePath();
// 	config.setFileName((LPTSTR)(LPCTSTR)(appPath + "\\appconfig.ini"));
	config.setFileName((LPTSTR)(LPCTSTR)(appPath + "\\appconfig.ini"));
}

CDbConfig::~CDbConfig()
{

}

// 读取用户名
char *CDbConfig::getUserName()
{
	return config.getSectionValueString(section,user);
}

// 读取密码
char *CDbConfig::getPwd()
{
	return config.getSectionValueString(section,pwd);
}

// 读取数据库名
char *CDbConfig::getOraName()
{
	return config.getSectionValueString(section,oraName);
}
