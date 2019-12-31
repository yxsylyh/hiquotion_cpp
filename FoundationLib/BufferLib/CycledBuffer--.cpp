// CycledBuffer.cpp: implementation of the CCycledBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CycledBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCycledBuffer::CCycledBuffer()
: m_isBufferOutside(FALSE), m_waitedReadLength(0), m_waitedWriteLength(0), m_isExit(FALSE),m_isEmpty(TRUE)
{
	m_cycledBuffer=new char[DEFAULT_BUFFER_LENGTH];
	m_bufferLength=DEFAULT_BUFFER_LENGTH;
	
	m_startIndex=0;
	m_endIndex=-1;

// 	m_notFull=new CSemaphore(DEFAULT_BUFFER_LENGTH, DEFAULT_BUFFER_LENGTH);
// 	m_notEmpty=new CSemaphore(0, DEFAULT_BUFFER_LENGTH);
}

CCycledBuffer::CCycledBuffer(unsigned int bufferLength)
: m_isBufferOutside(FALSE), m_waitedReadLength(0), m_waitedWriteLength(0), m_isExit(FALSE), m_isEmpty(TRUE)
{
	unsigned int len=0;
	if(bufferLength>0)
		len=bufferLength;
	else
		len=DEFAULT_BUFFER_LENGTH;

	m_cycledBuffer=new char[len];
	m_bufferLength=len;
	
	m_startIndex=0;
	m_endIndex=-1;

// 	m_notFull=new CSemaphore(DEFAULT_BUFFER_LENGTH, DEFAULT_BUFFER_LENGTH);
// 	m_notEmpty=new CSemaphore(0, DEFAULT_BUFFER_LENGTH);
}

// CCycledBuffer::CCycledBuffer(char *buffer, unsigned int bufferLength)
// : m_isBufferOutside(TRUE)
// {
// 	if(buffer && bufferLength>0)
// 	{
// 		m_cycledBuffer=buffer;
// 		m_bufferLength=bufferLength;
// 	}
// 	else
// 	{
// 	m_cycledBuffer=new char[DEFAULT_BUFFER_LENGTH];
// 	m_bufferLength=DEFAULT_BUFFER_LENGTH;
// 	}
// 	
// 	m_startPosition=0;
// 	m_endPosition=-1;
// }

CCycledBuffer::~CCycledBuffer()
{
	delete m_cycledBuffer;

	exitWaiting();

// 	delete m_notFull;
// 	delete m_notEmpty;
}

// 初始化
void CCycledBuffer::init()
{
	m_readLock.Lock();
	m_writeLock.Lock();

	m_startIndex=0;
	m_endIndex=-1;
	m_isEmpty=TRUE;

	m_readLock.Unlock();
	m_writeLock.Unlock();

	m_notEmpty.SetEvent();
	m_notFull.SetEvent();

}

// 获取缓冲区长度
unsigned int CCycledBuffer::getBufferLength()
{
	return m_bufferLength;
}

// 获取缓冲区剩余长度
unsigned int CCycledBuffer::getRestLength()
{
	return m_bufferLength-getDataLength();
}

// 获取数据长度
unsigned int CCycledBuffer::getDataLength()
{
	if(m_isEmpty)
		return 0;

	int length=m_endIndex-m_startIndex+1;
	if(length>0)
		return length;
	else
		return length+m_bufferLength;
}

// 写入数据
// 返回值：
// 0，成功
// -1，参数有误
// -2，取消写入以等待退出
// -3，待写入的数据长度超过了缓冲区长度
int CCycledBuffer::write(char *data, unsigned int dataLength)
{
	if(!data)
		return -1;

	if(dataLength==0)
		return -1;

	if(m_isExit)
		return -2;

	if(m_bufferLength<dataLength)
		return -3;

	unsigned int restLength=getRestLength();
	while(restLength<dataLength)
	{
		Sleep(1);

		m_waitedWriteLength=dataLength;
		// 如果缓冲区剩余长度不够，则等待
		WaitForSingleObject(m_notFull, INFINITE);

		if(m_isExit)
			return FALSE;

		Sleep(1);

		m_writeLock.Lock();

		// 在Lock之前，如果缓冲区剩余长度已经发生，那么在Lock之后，需要做一下判断
		// 此时只有当前线程操作数据，所以只要条件满足，就可以继续
		restLength=getRestLength();
		if(restLength<dataLength)
		{
			m_writeLock.Unlock();
			return FALSE;
		}

	}

	if(m_endIndex+dataLength<=m_bufferLength-1)   // pay attention : m_endPosition can be -1, but nothing serious because of above safe check.
	{
// 		unsigned int pos=(m_endIndex==-1 ? 0 : m_endIndex);
		memcpy(m_cycledBuffer+m_endIndex+1, data, dataLength);
		if(m_endIndex==-1)
			m_endIndex=dataLength-1;
		else
			m_endIndex+=dataLength;
// 		if(m_endIndex==m_bufferLength-1)
// 			m_endIndex=0;
	}
	else
	{
		int len1=m_bufferLength-1-m_endIndex;  // 是从 m_endIndex 后一位置开始数，所以如果 m_endIndex 是 m_bufferLength-1，那么后面就没有了，len1 就为 0
		int len2=dataLength-len1;
		if(len1>0)
			memcpy(m_cycledBuffer+m_endIndex+1, data, len1);
		memcpy(m_cycledBuffer, data + len1, len2);
		m_endIndex=len2-1;
	}

	BOOL ret=FALSE;
// 	if(m_waitedReadLength>0)
// 	{
// 		if(getDataLength()>=m_waitedReadLength)
// 		{
			ret=m_notEmpty.SetEvent();
			m_waitedReadLength=0;
// 		}
// 	}

	m_writeLock.Unlock();

	m_isEmpty=FALSE;

	return 0;
}

// 读取数据
// 返回值：
// 0，成功
// -1，参数有误
// -2，取消写入以等待退出
// -3，待写入的数据长度超过了缓冲区长度
int CCycledBuffer::read(char *data, unsigned int dataLength)
{
	if(!data)
		return -1;

	if(dataLength==0)
		return -1;

	if(m_isExit)
		return -2;

	if(m_bufferLength<dataLength)
		return -3;

	while(getDataLength()<dataLength)
	{
		Sleep(1);

		m_waitedReadLength=dataLength;
		// 如果数据长度不够，则等待
		WaitForSingleObject(m_notEmpty, INFINITE);

		if(m_isExit)
			return FALSE;

		Sleep(1);

		m_readLock.Lock();

		// 在Lock之前，如果数据长度已经发生，那么在Lock之后，需要做一下判断
		// 此时只有当前线程操作数据，所以只要条件满足，就可以继续
		if(getDataLength()<dataLength)
		{
			m_readLock.Unlock();
			return FALSE;
		}
	}

	if(m_startIndex+dataLength<=m_bufferLength-1)
	{
		memcpy(data, m_cycledBuffer+m_startIndex, dataLength);
		m_startIndex+=dataLength;
		if(m_startIndex==m_bufferLength)
			m_startIndex=0;
	}
	else
	{
// 		char *tmp=new char[dataLength];
		int len1=m_bufferLength-m_startIndex;   // 从 m_startIndex 开始数，所以 m_startIndex 是 m_bufferLength 的时候，后面才没有，即 len1 为 0
		int len2=dataLength-len1;
		if(len1>0)
			memcpy(data, m_cycledBuffer+m_startIndex, len1);
		memcpy(data+len1, m_cycledBuffer, len2);
// 		memcpy(tmp, m_buffer+m_startPosition, len1);
// 		memcpy(tmp+len1, m_buffer, len2);
		m_startIndex=len2;
		
// 		memcpy(data, tmp, dataLength);
// 		delete tmp;
	}

	if((m_endIndex+1) % m_bufferLength == m_startIndex)
		m_isEmpty=TRUE;
	else
		m_isEmpty=FALSE;
	
	BOOL ret=FALSE;
// 	if(m_waitedWriteLength>0)
// 	{
// 		if(getRestLength()>=m_waitedWriteLength)
// 		{
			ret=m_notFull.SetEvent();
			m_waitedWriteLength=0;
// 		}
// 	}

	m_readLock.Unlock();

	return TRUE;
}

// 重定义缓冲区大小
void CCycledBuffer::redimLength(unsigned int length, BOOL reserveData)
{
	if(length<=0)
		return;

	char *tmp=new char[length];
	memset(tmp, 0x00, length);

	m_writeLock.Lock();
	m_readLock.Lock();

	if(reserveData)
		memcpy(tmp, m_cycledBuffer, min(m_bufferLength, length));

	delete m_cycledBuffer;
	m_cycledBuffer=tmp;

	m_bufferLength=length;

	m_readLock.Unlock();
	m_writeLock.Unlock();
}

// 退出等待状态
void CCycledBuffer::exitWaiting()
{
	m_isExit=TRUE;
	m_notEmpty.SetEvent();
	m_notFull.SetEvent();
}

