// AndChecker.h: interface for the CAndChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANDCHECKER_H__35E46F7D_D1DA_4668_B629_998F1F1C7F3D__INCLUDED_)
#define AFX_ANDCHECKER_H__35E46F7D_D1DA_4668_B629_998F1F1C7F3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICharChecker.h"

class CAndChecker : public ICharChecker  
{
public:
	CAndChecker();
	CAndChecker(ICharChecker *checker1, ICharChecker *checker2);
	virtual ~CAndChecker();

	virtual BOOL accept(char c);
	
	ICharChecker * getChecker1() const { return m_checker1; }
	void setChecker1(ICharChecker * val) { m_checker1 = val; }
	
	ICharChecker * getChecker2() const { return m_checker2; }
	void setChecker2(ICharChecker * val) { m_checker2 = val; }
	
private:
	ICharChecker *m_checker1;
	ICharChecker *m_checker2;
};

#endif // !defined(AFX_ANDCHECKER_H__35E46F7D_D1DA_4668_B629_998F1F1C7F3D__INCLUDED_)
