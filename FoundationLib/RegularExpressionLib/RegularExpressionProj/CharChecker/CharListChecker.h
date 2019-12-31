// CharListChecker.h: interface for the CCharListChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARLISTCHECKER_H__0F03CC3B_2BD9_487A_9620_951318FAC321__INCLUDED_)
#define AFX_CHARLISTCHECKER_H__0F03CC3B_2BD9_487A_9620_951318FAC321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICharChecker.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

class CCharListChecker : public ICharChecker, public CPointerList<ICharChecker *>
{
public:
	CCharListChecker();
	CCharListChecker(BOOL isOrCheck);
	virtual ~CCharListChecker();

	virtual BOOL accept(char c);

	BOOL isOrChecker() const { return m_isOrChecker; }
	void setOrChecker(BOOL val) { m_isOrChecker = val; }

private:
	BOOL orCheck(char c);
	BOOL andCheck(char c);

private:
	BOOL m_isOrChecker;  // 是不是或
};

#endif // !defined(AFX_CHARLISTCHECKER_H__0F03CC3B_2BD9_487A_9620_951318FAC321__INCLUDED_)
