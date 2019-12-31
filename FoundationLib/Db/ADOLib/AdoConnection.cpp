// AdoConnection.cpp: implementation of the CAdoConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoConnection.h"
#include <sstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoConnection::CAdoConnection()
: m_isConnected(FALSE)
{
	HRESULT hr = pMyConnect.CreateInstance(__uuidof(Connection));
	if( FAILED(hr) )
	{
		std::stringstream ss;
		ss << "创建数据库连接对象失败！Windows 错误码是 " << GetLastError();
		m_errMessage=ss.str();
		m_isCreated=FALSE;
		return;
	}
	m_isCreated=TRUE;
}

CAdoConnection::~CAdoConnection()
{
	if(m_isConnected)
		pMyConnect->Close();
}

BOOL CAdoConnection::isCreated()
{
	return m_isCreated;
}

BOOL CAdoConnection::connect(CString connStr)
{
	if(!m_isCreated)
	{
		m_errMessage="请先创建连接对象。";
		m_isConnected=FALSE;
		return FALSE;
	}

	try
	{
		pMyConnect->Open(connStr.AllocSysString(),"","",NULL);
	}
	catch (_com_error &e)
	{
		m_errMessage="连接数据库失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		m_isConnected=FALSE;
		return FALSE;
	}

	m_isConnected=TRUE;
	return TRUE;
}

BOOL CAdoConnection::isConnected()
{
	if(!m_isCreated)
	{
		m_errMessage="请先创建连接对象。";
		return FALSE;
	}

	return m_isConnected;
}

BOOL CAdoConnection::beginTrans()
{
	if(!m_isConnected)
	{
		m_errMessage="数据库未连接。";
		return FALSE;
	}

	try
	{
		pMyConnect->BeginTrans();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="开始事务失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoConnection::commitTrans()
{
	if(!m_isConnected)
	{
		m_errMessage="数据库未连接。";
		return FALSE;
	}
	
	try
	{
		pMyConnect->CommitTrans();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="提交事务失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoConnection::rollbackTrans()
{
	if(!m_isConnected)
	{
		m_errMessage="数据库未连接。";
		return FALSE;
	}
	
	try
	{
		pMyConnect->RollbackTrans();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="回滚事务失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

_RecordsetPtr CAdoConnection::execute(CString sql, long *affected)
{
	if(!m_isConnected)
	{
		m_errMessage="数据库未连接。";
		return NULL;
	}
	
	try
	{
		VARIANT recordAffected;
		_RecordsetPtr rec=pMyConnect->Execute(sql.AllocSysString(), &recordAffected, adCmdText);
		*affected=recordAffected.lVal;
		return rec;
	}
	catch (_com_error &e)
	{
		m_errMessage="执行 " + sql + " 失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return NULL;
	}
}
