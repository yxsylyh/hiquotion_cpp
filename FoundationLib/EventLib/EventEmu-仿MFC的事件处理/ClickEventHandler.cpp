// ClickEventHandler.cpp: implementation of the CClickEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EVENTEMU.h"
#include "ClickEventHandler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClickEventHandler::CClickEventHandler()
{

}

CClickEventHandler::~CClickEventHandler()
{

}

Begin_Event_Map(CClickEventHandler)
	Event_Map(e->getSender(), "Clicked", OnClicked)
End_Event_Map()

void CClickEventHandler::OnClicked(IEvent *e)
{
	printf("clicked.");
}
