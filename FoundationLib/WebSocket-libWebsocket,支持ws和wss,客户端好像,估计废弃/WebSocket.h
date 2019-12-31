#pragma once

#include <C++\3rdParty\libwebsockets\libwebsockets.h>
#include <C++\FoundationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoundationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include "websocketservicethread.h"

class CWebSocket : public IEventRaisable
{
public:
	CWebSocket(void);
	~CWebSocket(void);

	int open(CString uri);
	BOOL isOpen() const { return m_isOpen; }
	void setOpen(BOOL isOpen) { m_isOpen=isOpen; }

	int startService();
	void pauseService();
	void resumeService();
	void stopService();

	int sendMessage(CString msg);
	int sendData(char *data, int length);

	void close();

	void setUserBuffer(unsigned char *buffer, int length);

	CDelegate WSOpen;
	CDelegate WSReceiveData;
	CDelegate WSCanSendData;
	CDelegate WSError;
	CDelegate WSClose;

private:
	struct lws_context_creation_info m_createInfo;
	struct lws_client_connect_info m_connectInfo;
	struct lws_context *m_context;
	const char *m_protocolWS, *m_uriPath;
	struct lws *plws;

	CString m_uri;

	CWebsocketServiceThread m_thead;

	BOOL m_isOpen;

	unsigned char m_userData[102400];
};
