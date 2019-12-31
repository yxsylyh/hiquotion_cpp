// ClickEventHandler.h: interface for the CClickEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLICKEVENTHANDLER_H__0AEDF7A9_4744_42D3_BBE5_F563DCA7C604__INCLUDED_)
#define AFX_CLICKEVENTHANDLER_H__0AEDF7A9_4744_42D3_BBE5_F563DCA7C604__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IEventHandler.h"

class CClickEventHandler : public IEventHandler  
{
public:
	CClickEventHandler();
	virtual ~CClickEventHandler();

	Declare_Event_Map()

	void OnClicked(IEvent *e);
};

#endif // !defined(AFX_CLICKEVENTHANDLER_H__0AEDF7A9_4744_42D3_BBE5_F563DCA7C604__INCLUDED_)
