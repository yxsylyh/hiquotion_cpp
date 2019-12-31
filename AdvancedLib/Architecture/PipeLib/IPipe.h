// IPipe.h: interface for the IPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPIPE_H__BC294875_1C43_45AC_8C61_79CC44EB172B__INCLUDED_)
#define AFX_IPIPE_H__BC294875_1C43_45AC_8C61_79CC44EB172B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IParameter.h"

class IPipe  
{
public:
	IPipe();
	IPipe(CString name);
	virtual ~IPipe();

	virtual IParameter *execute(IParameter *para){return NULL;};

	CString getName() const { return m_name; }
	void setName(CString val) { m_name = val; }

	CString getMessage() { return m_message; };

protected:
	CString m_name;
	CString m_message;
};

#endif // !defined(AFX_IPIPE_H__BC294875_1C43_45AC_8C61_79CC44EB172B__INCLUDED_)
