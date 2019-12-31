// CharChecker.h: interface for the CCharChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARCHECKER_H__469FBED9_2DBB_4B1E_A967_C372726FE8E4__INCLUDED_)
#define AFX_CHARCHECKER_H__469FBED9_2DBB_4B1E_A967_C372726FE8E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICharChecker.h"

class CCharChecker : public ICharChecker  
{
public:
	CCharChecker();
	CCharChecker(char c);
	virtual ~CCharChecker();

	virtual BOOL accept(char c);

private:
	char m_char;
};

#endif // !defined(AFX_CHARCHECKER_H__469FBED9_2DBB_4B1E_A967_C372726FE8E4__INCLUDED_)
