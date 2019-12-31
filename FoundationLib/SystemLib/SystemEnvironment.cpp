// SystemEnvironment.cpp: implementation of the CSystemEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemEnvironment.h"
#include <atlbase.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemEnvironment::CSystemEnvironment()
: m_errMsg("")
{
	m_regKey="System\\CurrentControlSet\\Control\\Session Manager\\Environment";
}

CSystemEnvironment::~CSystemEnvironment()
{

}

// 添加
// 环境变量原来没有则创建，原来有则修改
BOOL CSystemEnvironment::add(CString name, CString value)
{
	m_errMsg="";

	if(name=="" || value=="")
	{
		m_errMsg="参数为空！";
		return FALSE;
	}

	CRegKey key;
	LONG ret=key.Open(HKEY_LOCAL_MACHINE, m_regKey);
	if(ret!=ERROR_SUCCESS)
	{
		m_errMsg="打开注册表 " + m_regKey + " 失败！";
		return FALSE;
	}

	ret=key.SetValue(value, name);
	if(ret!=ERROR_SUCCESS)
	{
		m_errMsg="设置键值 " + name + " 的数据 " + value + " 时失败！";
		return FALSE;
	}

	return TRUE;
}

// 追加
// 环境变量原来没有则创建，原来有则追加
BOOL CSystemEnvironment::append(CString name, CString value)
{
	m_errMsg="";
	
	if(name=="" || value=="")
	{
		m_errMsg="参数为空！";
		return FALSE;
	}
	
	m_errMsg="暂未实现。";
	return FALSE;
}

// 删除
// 环境变量原来没有则忽略，原来有则若value为空则删除环境变量，value不空删除环境变量中的value值
BOOL CSystemEnvironment::del(CString name, CString value)
{
	m_errMsg="";
	
	if(name=="")
	{
		m_errMsg="参数为空！";
		return FALSE;
	}
	
	m_errMsg="暂未实现。";
	return FALSE;
}
