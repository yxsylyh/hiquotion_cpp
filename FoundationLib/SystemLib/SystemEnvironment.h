// SystemEnvironment.h: interface for the CSystemEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMENVIRONMENT_H__C1538397_1B15_41F7_AEE1_67D758047F62__INCLUDED_)
#define AFX_SYSTEMENVIRONMENT_H__C1538397_1B15_41F7_AEE1_67D758047F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Windows 系统环境变量操作类
class CSystemEnvironment  
{
public:
	CSystemEnvironment();
	virtual ~CSystemEnvironment();

	// 添加
	// 环境变量原来没有则创建，原来有则修改
	BOOL add(CString name, CString value);

	// 追加
	// 环境变量原来没有则创建，原来有则追加
	BOOL append(CString name, CString value);

	// 删除
	// 环境变量原来没有则忽略，原来有则若value为空则删除环境变量，value不空删除环境变量中的value值
	BOOL del(CString name, CString value="");

	CString getErrMsg() const { return m_errMsg; }

private:
	CString m_regKey;
	CString m_errMsg;
};

#endif // !defined(AFX_SYSTEMENVIRONMENT_H__C1538397_1B15_41F7_AEE1_67D758047F62__INCLUDED_)
