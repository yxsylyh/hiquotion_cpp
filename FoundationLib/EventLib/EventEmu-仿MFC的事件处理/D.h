// D.h: interface for the CD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_D_H__A3F1523A_C692_4EC1_BCF2_A47E47E9A436__INCLUDED_)
#define AFX_D_H__A3F1523A_C692_4EC1_BCF2_A47E47E9A436__INCLUDED_

#include "IEventHandler.h"
#include "A.h"
#include "IEvent.h"
#include <vector>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CD : public IEventHandler  
{
public:
	CD();
	virtual ~CD();

	CA a1;
	CA a2;

	void raiseEvent();

	Declare_Event_Map();

private:
	void OnA1(IEvent *e);
	void OnA2(IEvent *e);
	void OnA(IEvent *e);

	std::vector<CA *> m_list;

};

#endif // !defined(AFX_D_H__A3F1523A_C692_4EC1_BCF2_A47E47E9A436__INCLUDED_)
