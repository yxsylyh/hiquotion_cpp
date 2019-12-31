// SymbolCharChecker.h: interface for the CSymbolCharChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMBOLCHARCHECKER_H__720840D0_B7BA_42F5_8D8F_963670B23448__INCLUDED_)
#define AFX_SYMBOLCHARCHECKER_H__720840D0_B7BA_42F5_8D8F_963670B23448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CharChecker.h"

class CSymbolCharChecker : public CCharChecker  
{
public:
	CSymbolCharChecker();
	CSymbolCharChecker(char c);
	virtual ~CSymbolCharChecker();

};

#endif // !defined(AFX_SYMBOLCHARCHECKER_H__720840D0_B7BA_42F5_8D8F_963670B23448__INCLUDED_)
