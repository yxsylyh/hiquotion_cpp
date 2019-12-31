// FtpProgressEvent.cpp: implementation of the CFtpProgressEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpProgressEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpProgressEvent::CFtpProgressEvent()
{

}

CFtpProgressEvent::CFtpProgressEvent( IEventRaisable *sender, string eventId, UINT fileId, UINT progress )
: IEvent(sender, eventId), m_fileId(fileId), m_progress(progress)
{
	
}

CFtpProgressEvent::~CFtpProgressEvent()
{

}
