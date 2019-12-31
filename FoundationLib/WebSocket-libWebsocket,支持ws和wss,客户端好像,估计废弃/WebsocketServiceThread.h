#pragma once
#include <c++\foudationlib\multithreadlib\threadbase.h>
#include <C++\3rdParty\libwebsockets\libwebsockets.h>

class CWebsocketServiceThread :
	public CThreadBase
{
public:
	CWebsocketServiceThread(void);
	CWebsocketServiceThread(struct lws_context *context);
	~CWebsocketServiceThread(void);

	struct lws_context * getContext() const { return m_context; }
	void setContext(struct lws_context * val) { m_context = val; }

protected:
	UINT threadRun();

private:
	struct lws_context *m_context;
};
