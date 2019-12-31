// AdoConnection.h: interface for the CAdoConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONNECTION_H__3BD17E24_6C56_4F56_9433_BA3D28DC8A93__INCLUDED_)
#define AFX_ADOCONNECTION_H__3BD17E24_6C56_4F56_9433_BA3D28DC8A93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++/FoudationLib/IClassBase.h>
// #include "msado15.tlh"

class CAdoConnection : public IClassBase
{
public:
	CAdoConnection();
	virtual ~CAdoConnection();

	BOOL connect(CString connStr);
	BOOL isCreated();
	BOOL isConnected();
	_ConnectionPtr getAdoConnectionPtr(){ return pMyConnect; }
	BOOL beginTrans();
	BOOL commitTrans();
	BOOL rollbackTrans();
	_RecordsetPtr execute(CString sql, long *affected);

private:
	_ConnectionPtr pMyConnect;
	BOOL m_isCreated;
	BOOL m_isConnected;
};

#endif // !defined(AFX_ADOCONNECTION_H__3BD17E24_6C56_4F56_9433_BA3D28DC8A93__INCLUDED_)
