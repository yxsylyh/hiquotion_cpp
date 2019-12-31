// Z.cpp: implementation of the CZ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EVENTEMU.h"
#include "Z.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZ::CZ()
{
	a.OnE1+=this;
	a.OnE2+=this;
	a.On3+=this;

	b.OnF1+=this;
	b.OnF2+=this;
	b.On3+=this;

	a2.OnE1+=this;
}

CZ::~CZ()
{

}

Begin_Event_Map(CZ)
	Event_Map(&a, "E1", OnE1)
	Event_Map(&a, "E2", OnE2)
	Event_Map(&a, "3", CA_On3)
	Event_Map(&b, "F1", OnF1)
	Event_Map(&b, "F2", OnF2)
	Event_Map(&b, "3", CB_On3)

	Event_Map(&a2, "E1", a2_E1)


// 下面的方式是不行的，因为 e->getSender() 与 sender 肯定是相同的，无法区分CA的3事件和CB的3事件
// 	Event_Map(e->getSender(),e->getEventId(), "E1", OnE1)
// 	Event_Map(e->getSender(),e->getEventId(), "E2", OnE2)
// 	Event_Map(e->getSender(),e->getEventId(), "3", CA_On3)
// 	Event_Map(e->getSender(),e->getEventId(), "F1", OnF1)
// 	Event_Map(e->getSender(),e->getEventId(), "F2", OnF2)
// 	Event_Map(e->getSender(),e->getEventId(), "3", CB_On3)
End_Event_Map()

void CZ::OnE1(IEvent *e)
{
	printf("OnE1.\n");
}

void CZ::OnE2(IEvent *e)
{
	printf("OnE2.\n");
}

void CZ::OnF1(IEvent *e)
{
	printf("OnF1.\n");
}

void CZ::OnF2(IEvent *e)
{
	printf("OnF2.\n");
}

void CZ::CA_On3(IEvent *e)
{
	printf("CAOn3.\n");
}

void CZ::CB_On3(IEvent *e)
{
	printf("CBOn3.\n");
}

void CZ::emuEventRaise()
{
	a.raiseE1();
	a.raiseE2();
	
	b.raiseF1();
	b.raiseF2();
	
	a.raise3();
	b.raise3();

	a2.raiseE1();
}

void CZ::a2_E1(IEvent *e)
{
	printf("On a2 E1 event.\n");
}
