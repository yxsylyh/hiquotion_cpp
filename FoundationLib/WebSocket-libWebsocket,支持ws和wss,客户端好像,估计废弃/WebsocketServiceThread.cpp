#include "StdAfx.h"
#include "WebsocketServiceThread.h"

CWebsocketServiceThread::CWebsocketServiceThread(void)
: m_context(NULL)
{
}

CWebsocketServiceThread::CWebsocketServiceThread( struct lws_context *context )
: m_context(context)
{

}
CWebsocketServiceThread::~CWebsocketServiceThread(void)
{
}

UINT CWebsocketServiceThread::threadRun()
{
	if(!m_context)
		return -1;

	while(m_status==Running)
	{
		lws_service(m_context, 500);
	}

	lws_cancel_service(m_context);
	return 0;
}
