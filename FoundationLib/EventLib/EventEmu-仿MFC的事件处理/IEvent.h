// IEvent.h: interface for the IEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IEVENT_H__4DFF5880_95A2_4B34_8FA5_C5089E10984D__INCLUDED_)
#define AFX_IEVENT_H__4DFF5880_95A2_4B34_8FA5_C5089E10984D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

#include "IEventRaisable.h"

class IEvent  
{
public:
	IEvent();
	IEvent(IEventRaisable *sender, string eventId);
	IEvent(IEventRaisable *sender, string eventId, int returnCode);
	IEvent(IEventRaisable *sender, string eventId, string returnMessage);
	IEvent(IEventRaisable *sender, string eventId, int returnCode, string returnMessage);
	IEvent(IEventRaisable *sender, string eventId, IEvent *e);
	IEvent(IEventRaisable *sender, string eventId, int returnCode, IEvent *e);
	IEvent(IEventRaisable *sender, string eventId, string returnMessage, IEvent *e);
	IEvent(IEventRaisable *sender, string eventId, int returnCode, string returnMessage, IEvent *e);
	virtual ~IEvent();

	string getEventId();
	IEventRaisable *getSender();

	int getIndexOfEventList() const { return m_indexOfEventList; }
	void setIndexOfEventList(int val) { m_indexOfEventList = val; }

	int getReturnCode() const { return m_returnCode; }
	string getReturnMessage() const { return m_returnMessage; }

protected:
	IEventRaisable *m_sender;
	string m_eventId;
	int m_indexOfEventList;

	int m_returnCode;
	string m_returnMessage;

	IEvent *m_prevEvent;
};

#endif // !defined(AFX_IEVENT_H__4DFF5880_95A2_4B34_8FA5_C5089E10984D__INCLUDED_)
