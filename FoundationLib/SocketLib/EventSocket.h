#if !defined(AFX_SIMPLESOCKET_H__814A6119_BBDF_4C8C_8899_AEA0B07E0284__INCLUDED_)
#define AFX_SIMPLESOCKET_H__814A6119_BBDF_4C8C_8899_AEA0B07E0284__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimpleSocket.h : header file
//

#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include <C++\FoudationLib\BufferLib\ByteBuffer.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>

#define SS_RECEIVE_BUFFER_TOTAL_LENGTH 10240000
#define SS_RECEIVE_BUFFER_LENGTH 1024

#include <afxsock.h>

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket command target

class CEventSocket : public CSocket, public IEventRaisable
{
// Attributes
public:

// Operations
public:
	CEventSocket();
	virtual ~CEventSocket();
	
	int sendString(CString &msg);

	CDelegate Connected;
	CDelegate DataArrived;
	CDelegate Closed;

	void setBufferLength(int bufferLength);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSimpleSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CByteBuffer m_buffer;
};

class CSSDataArriveEvent : public IEvent
{
public:
	CSSDataArriveEvent(IEventRaisable *sender, string eventId, BYTE *data, int dataLength);
	virtual ~CSSDataArriveEvent();

	BYTE * getData() const { return m_data; }
	int getDataLength() const { return m_dataLength; }

private:
	BYTE *m_data;
	int m_dataLength;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLESOCKET_H__814A6119_BBDF_4C8C_8899_AEA0B07E0284__INCLUDED_)
