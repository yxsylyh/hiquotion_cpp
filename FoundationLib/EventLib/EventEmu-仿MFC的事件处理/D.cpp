// D.cpp: implementation of the CD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EVENTEMU.h"
#include "D.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CD::CD()
{
// 	a1.OnE1+=this;
// 	a2.OnE1+=this;
	CA *a1=new CA;
	CA *a2=new CA;
	a1->OnE1+=this;
	a2->OnE1+=this;
	m_list.push_back(a1);
	m_list.push_back(a2);
}

CD::~CD()
{

}

Begin_Event_Map(CD)
// Event_Map(&a1, "E1", OnA1)
// Event_Map(&a2, "E1", OnA2)
Event_List_Map(m_list, CA, "E1", OnA)
End_Event_Map()

void CD::OnA1(IEvent *e)
{
	printf("On CA a1\n");
}

void CD::OnA2(IEvent *e)
{
	printf("On CA a2\n");
}

void CD::raiseEvent()
{
// 	a1.raiseE1();
// 	a2.raiseE1();
	for(int i=0;i<m_list.size();i++)
	{
		CA *a=m_list.at(i);
		a->raiseE1();
	}

}

void CD::OnA( IEvent *e )
{
	printf("On CA List Event\n");
}
