// SimpleSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket

CSimpleSocket::CSimpleSocket()
: m_isHeadWanted(TRUE), m_dataWanted(SDTP_HEAD_LENGTH), m_status(SSS_NO_ACTION)
{
	AfxSocketInit();
	m_buffer.redimBufferLength(SS_RECEIVE_BUFFER_TOTAL_LENGTH);
}

CSimpleSocket::~CSimpleSocket()
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

void CSimpleSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	// 如果不需要接收，则忽略到达的数据
	DWORD dwReceived;
	
	if (!IOCtl(FIONREAD, &dwReceived))
	{
		// Error handling here
		MessageBox(0, "获取接收到的数据长度时失败！", "", MB_OK);
		m_buffer.init();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	if(dwReceived<=0)
	{
		m_buffer.init();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	if(m_status==SSS_NO_ACTION)
	{
		m_buffer.init();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	// 如果缓冲区长度不够，则缓冲区扩大一倍，并且保留原来的数据
	if(m_buffer.getDataLength()+dwReceived>m_buffer.getBufferLength())
		m_buffer.redimBufferLength(max(m_buffer.getDataLength()+dwReceived, m_buffer.getBufferLength()) * 2, TRUE);

// 	char buf[SS_RECEIVE_BUFFER_LENGTH];
	char *buf=new char[dwReceived];
	DWORD sum=0;
// 	do 
// 	{
		// 接收数据
// 		int ret=Receive(buf, SS_RECEIVE_BUFFER_LENGTH);
		int ret=Receive(buf, dwReceived);
		if(ret>0)
		{
			// 写入数据
			m_buffer.appendBytes(buf, ret);
// 			sum+=ret;
		}
// 	}
// 	while(sum<dwReceived);

	delete buf;

	// 如果接收到的数据比希望接收到的数据少，则返回，继续等待
	if(m_buffer.getDataLength()<m_dataWanted)
	{
		CSocket::OnReceive(nErrorCode);
		return;
	}

	char *data=new char[m_buffer.getDataLength()];
	int len=m_buffer.getDataLength();
	m_buffer.readTotalData(data, len);
	// 如果是希望接收协议头，则从协议头开始写入整个数据
	if(m_isHeadWanted)
		m_sdtp.setTotalData(data, m_buffer.getDataLength());
	// 否则，在数据区追加数据
	else
		m_sdtp.appendData(data, m_buffer.getDataLength());
	delete data;

	// 如果是希望接收协议头
	if(m_isHeadWanted)
	{
		int datalen=0;
		// 获取协议头中的数据长度
		m_sdtp.getDataLengthInHead(&datalen);
		// 如果协议头中的数据长度非正，则忽略该包及以后的包
		if(datalen<=0)
		{
			m_status=SSS_NO_ACTION;
			m_buffer.init();
			m_sdtp.init();
			CSocket::OnReceive(nErrorCode);
			return;
		}

		// 协议头接收完毕
// 		m_isHeadWanted=FALSE;
// 		m_dataWanted=datalen;
		wantData(datalen);
	}
// 	else
// 	{

	// 对数据区数据做判断

		// 如果接收到的数据长度与协议头中的数据长度一致，则抛出事件
		if(m_dataWanted<=m_sdtp.getDataLength())
		{
			wantHeader();

			int len=m_sdtp.getDataLength();
			char *data=new char[len];
			ZeroMemory(data, len);
			m_sdtp.getData(data);
			m_buffer.init();
			CSSDataArriveEvent e(this, "SSDataArrived", (BYTE *)data, len);
			DataArrived.raiseEvent(this, &e);
			delete data;
			m_buffer.init();
			m_sdtp.init();
		}
// 	}

	CSocket::OnReceive(nErrorCode);
}

int CSimpleSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!lpBuf)
		return -1;

	if(nBufLen<=0)
		return -2;

	m_sdtp.init();
	m_sdtp.genHead('s','d','t','p',1,0,0,0);
	m_sdtp.appendData((char *)lpBuf, nBufLen);
	m_sdtp.setCheckCodeInHead(m_sdtp.genCheckCode());
	m_sdtp.setDataLengthInHead(nBufLen);

	char *buf=new char[m_sdtp.getTotalDataLength()];
	m_sdtp.getTotalData(buf);

	int ret=CSocket::Send(buf, m_sdtp.getTotalDataLength(), nFlags);
	delete buf;
	return ret;
}

void CSimpleSocket::setBufferLength(int bufferLength)
{
	m_sdtp.setBufferLength(bufferLength);
}

void CSimpleSocket::setStatus(SS_STATUS val)
{
	m_status = val;
	if(m_status!=SSS_NO_ACTION)
		wantHeader();
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

// 希望接收协议头
void CSimpleSocket::wantHeader()
{
	m_isHeadWanted=TRUE;
	m_dataWanted=SDTP_HEAD_LENGTH;
}

// 希望接收数据
void CSimpleSocket::wantData(int dataLength)
{
	if(dataLength<=0)
		return;

	m_isHeadWanted=FALSE;
	m_dataWanted=dataLength;
}



CSSDataArriveEvent::CSSDataArriveEvent(IEventRaisable *sender, string eventId, BYTE *data, int dataLength)
: IEvent(sender, eventId), m_data(data), m_dataLength(dataLength)
{
}

CSSDataArriveEvent::~CSSDataArriveEvent()
{
	
}
