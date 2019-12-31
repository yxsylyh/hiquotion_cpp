// CEventListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "EventListenSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CEventListenSocket::CEventListenSocket()
: m_isAccept(FALSE)
{
	AfxSocketInit();
	m_serverSocket.DataArrived+=this;
}

CEventListenSocket::~CEventListenSocket()
{
	m_serverSocket.DataArrived-=this;
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

void CEventListenSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!m_isAccept)
	{
		SOCKADDR_IN        clientAddr;
		int socketLen = sizeof(SOCKADDR_IN);
		
		if(!CSocket::Accept(m_serverSocket, (SOCKADDR*)&clientAddr, &socketLen))
			return;

		m_isAccept=TRUE;

		CString clientIp=inet_ntoa(clientAddr.sin_addr);
		UINT clientPort=clientAddr.sin_port;

		CSSConnectEvent e(this, "SSConnected", clientIp, clientPort);
		Connected.raiseEvent(this, &e);
	}

	CSocket::OnAccept(nErrorCode);
}

Begin_Event_Map(CEventListenSocket)
Event_Map(&m_serverSocket, "SSDataArrived", OnDataGot)
End_Event_Map()

// 服务端收到数据
void CEventListenSocket::OnDataGot(IEvent *e)
{
	DataArrived.raiseEvent(this, e);
}

CEventSocket &CEventListenSocket::getSocket()
{
	return m_serverSocket;
}

void CEventListenSocket::OnClose(int nErrorCode)
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
