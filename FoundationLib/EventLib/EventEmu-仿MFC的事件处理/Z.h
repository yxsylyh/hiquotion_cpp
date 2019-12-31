// Z.h: interface for the CZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Z_H__3657BA5D_4A7B_49CB_8F89_0454BF8766E5__INCLUDED_)
#define AFX_Z_H__3657BA5D_4A7B_49CB_8F89_0454BF8766E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IEventHandler.h"
#include "A.h"
#include "B.h"

class CZ : public IEventHandler  
{
public:
	CZ();
	virtual ~CZ();

	void emuEventRaise();

	Declare_Event_Map()
		
	void OnE1(IEvent *e);
	void OnE2(IEvent *e);
	void OnF1(IEvent *e);
	void OnF2(IEvent *e);
	void CA_On3(IEvent *e);
	void CB_On3(IEvent *e);

	void a2_E1(IEvent *e);

	// CZ means Window Class(for example, a Dialog)
	// CA and CB means Control in Window(for example, a Button and a TextBox)
	CA a;
	CB b;

	CA a2;
};

#endif // !defined(AFX_Z_H__3657BA5D_4A7B_49CB_8F89_0454BF8766E5__INCLUDED_)
