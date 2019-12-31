// RfOperation.h: interface for the CRfOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RFOPERATION_H__A9EEBF19_29C9_4AE0_A571_76C4A1615200__INCLUDED_)
#define AFX_RFOPERATION_H__A9EEBF19_29C9_4AE0_A571_76C4A1615200__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mwrf32.h"
#pragma comment(lib,"mwrf32.lib")

#include <string>

class CRfOperation  
{
public:
	CRfOperation();
	virtual ~CRfOperation();

	int connect();
	void disconnect();
	BOOL isDeviceExist();
	BOOL findCard(std::string &cardSn);
	int readCard(std::string &content);
	int writeCard(std::string content);

private:
	HANDLE m_icdev;
	BOOL m_isConnected;

};

#endif // !defined(AFX_RFOPERATION_H__A9EEBF19_29C9_4AE0_A571_76C4A1615200__INCLUDED_)
