// TypeValue.h: interface for the CTypeValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPEVALUE_H__8D8B4FD9_C6EC_4774_80C1_A6FBC855B1D6__INCLUDED_)
#define AFX_TYPEVALUE_H__8D8B4FD9_C6EC_4774_80C1_A6FBC855B1D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTypeValue  
{
public:
	CTypeValue();
	virtual ~CTypeValue();

	static CString getDefaultValue(CString type);
};

#endif // !defined(AFX_TYPEVALUE_H__8D8B4FD9_C6EC_4774_80C1_A6FBC855B1D6__INCLUDED_)
