// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleListenSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CSimpleListenSocket::CSimpleListenSocket()
: m_isAccept(FALSE)
{
	AfxSocketInit();
	m_comunicatedSocket.DataArrived+=this;
}

CSimpleListenSocket::~CSimpleListenSocket()
{
	m_comunicatedSocket.DataArrived-=this;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSimpleListenSocket, CSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CSimpleListenSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!m_isAccept)
	{
		SOCKADDR_IN        clientAddr;
		int socketLen = sizeof(SOCKADDR_IN);
		
		if(!CSocket::Accept(m_comunicatedSocket, (SOCKADDR*)&clientAddr, &socketLen))
			return;

		m_comunicatedSocket.setStatus(SSS_RECEIVE_DATA);
		m_isAccept=TRUE;

		CString clientIp=inet_ntoa(clientAddr.sin_addr);
		UINT clientPort=clientAddr.sin_port;

		CSSConnectEvent e(this, "SSConnected", clientIp, clientPort);
		Connected.raiseEvent(this, &e);
	}

	CSocket::OnAccept(nErrorCode);
}

Begin_Event_Map(CSimpleListenSocket)
Event_Map(&m_comunicatedSocket, "SSDataArrived", OnDataGot)
End_Event_Map()

// 服务端收到数据
void CSimpleListenSocket::OnDataGot(IEvent *e)
{
	DataArrived.raiseEvent(this, e);
}

CSimpleSocket *CSimpleListenSocket::getSocket()
{
	CSimpleSocket *pSocket=&m_comunicatedSocket;
	return pSocket;
}

void CSimpleListenSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_isAccept=FALSE;

	CSocket::OnClose(nErrorCode);
}


CSSConnectEvent::CSSConnectEvent(IEventRaisable *sender, string eventId, CString ip, UINT port)
: IEvent(sender, eventId), m_ip(ip), m_port(port)
{
}

CSSConnectEvent::~CSSConnectEvent()
{
	
}
