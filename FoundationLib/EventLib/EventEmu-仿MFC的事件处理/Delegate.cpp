// Delegate.cpp: implementation of the CDelegate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Delegate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDelegate::CDelegate()
{

}

CDelegate::~CDelegate()
{
	handlers.clear();
}

void CDelegate::operator += (IEventHandler *handler)
{
	if(handler)
		handlers.push_back(handler);
}

void CDelegate::operator -= (IEventHandler *handler)
{
	if(!handler)
		return;

	vector<IEventHandler *>::iterator it;
	vector<IEventHandler *>::iterator tmp;
	for(it=handlers.begin();it!=handlers.end();)
	{
		if (*it==handler)
		{
			tmp=it;
			handlers.erase(tmp);
			break;
		}
		else
			it++;
	}
}

void CDelegate::raiseEvent(IEventRaisable *sender, IEvent *e)
{
	for(int i=0;i<(int)handlers.size();i++)
	{
		IEventHandler *handler=handlers[i];
		if(!handler)
			continue;
		
		handler->handleEvent(sender, e);
	}
}