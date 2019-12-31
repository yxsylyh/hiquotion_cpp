// RangeCharChecker.h: interface for the CRangeCharChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANGECHARCHECKER_H__37BBB3B0_D6A7_463E_B5E7_4FDCACDBC3AF__INCLUDED_)
#define AFX_RANGECHARCHECKER_H__37BBB3B0_D6A7_463E_B5E7_4FDCACDBC3AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICharChecker.h"

class CRangeCharChecker : public ICharChecker  
{
public:
	CRangeCharChecker();
	CRangeCharChecker(char from, char to);
	virtual ~CRangeCharChecker();

	virtual BOOL accept(char c);

	char getCharFrom() const { return m_charFrom; }
	void setCharFrom(char val) { m_charFrom = val; }

	char getCharTo() const { return m_charTo; }
	void setCharTo(char val) { m_charTo = val; }

private:
	char m_charFrom;
	char m_charTo;
};

#endif // !defined(AFX_RANGECHARCHECKER_H__37BBB3B0_D6A7_463E_B5E7_4FDCACDBC3AF__INCLUDED_)
