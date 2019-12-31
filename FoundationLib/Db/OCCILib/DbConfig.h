// DbConfig.h: interface for the CDbConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCONFIG_H__8FAA5E68_40CA_4401_94EF_A5EB4B6A57A0__INCLUDED_)
#define AFX_DBCONFIG_H__8FAA5E68_40CA_4401_94EF_A5EB4B6A57A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <C++\FoudationLib\INILib\IniOperation.h>

class CDbConfig  
{
public:
	CDbConfig(string configFileOrWithFullPath="appconfig.ini");
	virtual ~CDbConfig();

// 	string className;
// 	string classCode;
	
	// 读取用户名
	char *getUserName();
	
	// 读取密码
	char *getPwd();
	
	// 读取数据库名
	char *getOraName();
	
private:
	CIniOperation config;
	CString appPath;
	string m_configFile;

	char *section;
	char *user;
	char *pwd;
	char *oraName;

};

#endif // !defined(AFX_DBCONFIG_H__8FAA5E68_40CA_4401_94EF_A5EB4B6A57A0__INCLUDED_)
