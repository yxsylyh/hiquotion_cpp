// OrChecker.h: interface for the COrChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORCHECKER_H__68B663C0_4E0F_4700_826E_CBF8D9D3CCC0__INCLUDED_)
#define AFX_ORCHECKER_H__68B663C0_4E0F_4700_826E_CBF8D9D3CCC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICharChecker.h"

class COrChecker : public ICharChecker  
{
public:
	COrChecker();
	COrChecker(ICharChecker *checker1, ICharChecker *checker2);
	virtual ~COrChecker();

	virtual BOOL accept(char c);

	ICharChecker * getChecker1() const { return m_checker1; }
	void setChecker1(ICharChecker * val) { m_checker1 = val; }

	ICharChecker * getChecker2() const { return m_checker2; }
	void setChecker2(ICharChecker * val) { m_checker2 = val; }

private:
	ICharChecker *m_checker1;
	ICharChecker *m_checker2;
};

#endif // !defined(AFX_ORCHECKER_H__68B663C0_4E0F_4700_826E_CBF8D9D3CCC0__INCLUDED_)
