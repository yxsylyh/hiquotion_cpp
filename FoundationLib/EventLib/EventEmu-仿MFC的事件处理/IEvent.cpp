// IEvent.cpp: implementation of the IEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IEvent::IEvent()
: m_sender(NULL),m_eventId(""), m_indexOfEventList(-1), m_returnCode(-1), m_returnMessage(""), m_prevEvent(NULL)
{

}

IEvent::IEvent(IEventRaisable *sender, string eventId)
: m_sender(sender),m_eventId(eventId), m_indexOfEventList(-1), m_returnCode(-1), m_returnMessage(""), m_prevEvent(NULL)
{

}

IEvent::IEvent(IEventRaisable *sender, string eventId, int returnCode)
: m_sender(sender),m_eventId(eventId), m_indexOfEventList(-1), m_returnCode(returnCode), m_returnMessage(""), m_prevEvent(NULL)
{

}

IEvent::IEvent(IEventRaisable *sender, string eventId, string returnMessage)
: m_sender(sender),m_eventId(eventId), m_indexOfEventList(-1), m_returnCode(-1), m_returnMessage(returnMessage), m_prevEvent(NULL)
{

}

IEvent::IEvent(IEventRaisable *sender, string eventId, int returnCode, string returnMessage)
: m_sender(sender),m_eventId(eventId), m_indexOfEventList(-1), m_returnCode(returnCode), m_returnMessage(returnMessage), m_prevEvent(NULL)
{

}

IEvent::IEvent(IEventRaisable *sender, string eventId, IEvent *e)
: m_sender(sender),m_eventId(eventId), m_returnCode(-1), m_returnMessage(""), m_prevEvent(e)
{

}

IEvent::IEvent( IEventRaisable *sender, string eventId, int returnCode, IEvent *e )
: m_sender(sender),m_eventId(eventId), m_returnCode(returnCode), m_returnMessage(""), m_prevEvent(e)
{

}

IEvent::IEvent( IEventRaisable *sender, string eventId, string returnMessage, IEvent *e )
: m_sender(sender),m_eventId(eventId), m_returnCode(-1), m_returnMessage(returnMessage), m_prevEvent(e)
{

}

IEvent::IEvent( IEventRaisable *sender, string eventId, int returnCode, string returnMessage, IEvent *e )
: m_sender(sender),m_eventId(eventId), m_indexOfEventList(-1), m_returnCode(returnCode), m_returnMessage(returnMessage), m_prevEvent(e)
{

}

IEvent::~IEvent()
{

}

IEventRaisable *IEvent::getSender()
{
	return m_sender;
}

string IEvent::getEventId()
{
	return m_eventId;
}
