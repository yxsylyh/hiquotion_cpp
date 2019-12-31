// A.h: interface for the CA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_A_H__68B60A44_9A4A_4FFB_A47C_D24F475DDF73__INCLUDED_)
#define AFX_A_H__68B60A44_9A4A_4FFB_A47C_D24F475DDF73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IEventRaisable.h"
#include "Delegate.h"

class CA : public IEventRaisable  
{
public:
	CA();
	virtual ~CA();

	void raiseE1();
	void raiseE2();
	void raise3();

	CDelegate OnE1;
	CDelegate OnE2;
	CDelegate On3;
};

#endif // !defined(AFX_A_H__68B60A44_9A4A_4FFB_A47C_D24F475DDF73__INCLUDED_)
