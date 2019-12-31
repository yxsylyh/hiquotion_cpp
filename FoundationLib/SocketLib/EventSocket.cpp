// SimpleSocket.cpp : implementation file
//

#include "stdafx.h"
#include "EventSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket

CEventSocket::CEventSocket()
{
	AfxSocketInit();
	m_buffer.redimBufferSize(SS_RECEIVE_BUFFER_TOTAL_LENGTH);
}

CEventSocket::~CEventSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSimpleSocket, CSocket)
	//{{AFX_MSG_MAP(CSimpleSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket member functions

void CEventSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	// 如果不需要接收，则忽略到达的数据
	DWORD dwReceived;
	
	if (!IOCtl(FIONREAD, &dwReceived))
	{
		// Error handling here
		MessageBox(0, "获取接收到的数据长度时失败！", "", MB_OK);
		m_buffer.clearData();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	if(dwReceived<=0)
	{
		m_buffer.clearData();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	// 如果缓冲区长度不够，则缓冲区扩大一倍，并且保留原来的数据
	if(m_buffer.getDataLength()+dwReceived>m_buffer.getBufferLength())
		m_buffer.redimBufferSize(max(m_buffer.getDataLength()+dwReceived, m_buffer.getBufferLength()) * 2, TRUE);

	char buf[SS_RECEIVE_BUFFER_LENGTH];
	DWORD sum=0;
	do 
	{
		// 接收数据
		int ret=Receive(buf, SS_RECEIVE_BUFFER_LENGTH);
		if(ret>0)
		{
			// 写入数据
			m_buffer.append((BYTE *)buf, ret);
			sum+=ret;
		}
	}
	while(sum<dwReceived);

	char *data=new char[m_buffer.getDataLength()];
	int len=0;
	m_buffer.getTotalData((BYTE *)data, &len);

		int datalen=0;
		// 获取协议头中的数据长度
		m_sdtp.getDataLengthInHead(&datalen);
		// 如果协议头中的数据长度非正，则忽略该包及以后的包
		if(datalen<=0)
		{
			m_status=SSS_NO_ACTION;
			m_buffer.clearData();
			m_sdtp.init();
			CSocket::OnReceive(nErrorCode);
			return;
		}

		// 协议头接收完毕
// 		m_isHeadWanted=FALSE;
// 		m_dataWanted=datalen;
	}
// 	else
// 	{

	// 对数据区数据做判断

		// 如果接收到的数据长度与协议头中的数据长度一致，则抛出事件
			char *data=new char[len];
			ZeroMemory(data, len);
			m_buffer.clearData();
			CSSDataArriveEvent e(this, "SSDataArrived", (BYTE *)data, len);
			DataArrived.raiseEvent(this, &e);
			delete data;
			m_buffer.clearData();
			m_sdtp.init();
// 	}

	CSocket::OnReceive(nErrorCode);
}

void CSimpleSocket::setBufferLength(int bufferLength)
{
	m_sdtp.setBufferLength(bufferLength);
}

void CSimpleSocket::setStatus(SS_STATUS val)
{
	m_status = val;
}

void CSimpleSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_status=SSS_NO_ACTION;

	CSocket::OnClose(nErrorCode);
}

void CSimpleSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	setStatus(SSS_RECEIVE_DATA);

	CSocket::OnConnect(nErrorCode);
}
int CSimpleSocket::sendString(CString &msg)
{
	if(msg=="")
		return -1;

	return Send((LPTSTR)(LPCSTR)msg, msg.GetLength());
}



CSSDataArriveEvent::CSSDataArriveEvent(IEventRaisable *sender, string eventId, BYTE *data, int dataLength)
: IEvent(sender, eventId), m_data(data), m_dataLength(dataLength)
{
}

CSSDataArriveEvent::~CSSDataArriveEvent()
{
	
}
