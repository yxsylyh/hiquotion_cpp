#if !defined(AFX_LISTENSOCKET_H__00EA8A8E_0DB7_4B60_97A9_3ECBBECF992B__INCLUDED_)
#define AFX_LISTENSOCKET_H__00EA8A8E_0DB7_4B60_97A9_3ECBBECF992B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//

#include "SimpleSocket.h"
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventHandler.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>


/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CSimpleListenSocket : public CSocket, public IEventRaisable, public IEventHandler
{
// Attributes
public:

	CDelegate Connected;
	CDelegate DataArrived;

// Operations
public:
	CSimpleListenSocket();
	virtual ~CSimpleListenSocket();

	BOOL getAccept() const { return m_isAccept; }
	CSimpleSocket *getSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	BOOL m_isAccept;
	CSimpleSocket m_comunicatedSocket;

	Declare_Event_Map()
	
	// 服务端收到数据
	void OnDataGot(IEvent *e);
};

class CSSConnectEvent : public IEvent
{
public:
	CSSConnectEvent(IEventRaisable *sender, string eventId, CString ip, UINT port);
	virtual ~CSSConnectEvent();
	
	CString getIp() const { return m_ip; }
	UINT getPort() const { return m_port; }
	
private:
	CString m_ip;
	UINT m_port;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__00EA8A8E_0DB7_4B60_97A9_3ECBBECF992B__INCLUDED_)
