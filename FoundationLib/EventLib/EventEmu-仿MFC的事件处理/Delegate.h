// Delegate.h: interface for the CDelegate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELEGATE_H__6D0EA7D2_1447_49EC_8A5E_607A38A8F0A9__INCLUDED_)
#define AFX_DELEGATE_H__6D0EA7D2_1447_49EC_8A5E_607A38A8F0A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "IEventHandler.h"
#include "IEvent.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

class CDelegate  
{
public:
	CDelegate();
	virtual ~CDelegate();

	void operator += (IEventHandler *handler);
	void operator -= (IEventHandler *handler);
	void raiseEvent(IEventRaisable *sender, IEvent *e);

private:
	CPointerList<IEventHandler *> handlers;

};


#endif // !defined(AFX_DELEGATE_H__6D0EA7D2_1447_49EC_8A5E_607A38A8F0A9__INCLUDED_)
