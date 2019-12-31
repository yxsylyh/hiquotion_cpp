// B.h: interface for the CB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_B_H__68630310_4216_4CDA_9A34_B7713E435349__INCLUDED_)
#define AFX_B_H__68630310_4216_4CDA_9A34_B7713E435349__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IEventRaisable.h"
#include "Delegate.h"

class CB : public IEventRaisable  
{
public:
	CB();
	virtual ~CB();

	void raiseF1();
	void raiseF2();
	void raise3();

	CDelegate OnF1;
	CDelegate OnF2;
	CDelegate On3;
};

#endif // !defined(AFX_B_H__68630310_4216_4CDA_9A34_B7713E435349__INCLUDED_)
