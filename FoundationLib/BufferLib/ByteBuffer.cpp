// CharBuffer.cpp: implementation of the CCharBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ByteBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CByteBuffer::CByteBuffer()
{
	m_dataBuffer=new BYTE[DATA_BUFFER];
	m_bufferLength=DATA_BUFFER;
	m_dataLength=0;
}

CByteBuffer::~CByteBuffer()
{
	delete m_dataBuffer;
}

// 重新定义缓冲区大小
void CByteBuffer::redimBufferSize(BYTE *buffer, int length, BOOL dataReserve)
{
	if(!buffer)
		return;

	if(length<=0)
		return;

#ifdef SUPPORT_MULTI_THREAD
		m_lock.Lock();
#endif

	BYTE *newBuffer=buffer; //new BYTE[length * sizeof(BYTE)];
	if(dataReserve)
	{
		memcpy(newBuffer, getDataBuffer(), min(m_dataLength, length));
		m_dataLength=min(m_dataLength, length);
	}
	delete m_dataBuffer;
	m_dataBuffer=newBuffer;
	m_bufferLength=length;

#ifdef SUPPORT_MULTI_THREAD
		m_lock.Unlock();
#endif
};
 
// 重新定义缓冲区大小
void CByteBuffer::redimBufferSize(int length, BOOL dataReserve)
{
	if(length<=0)
		return;

	BYTE *newBuffer=new BYTE[length * sizeof(BYTE)];
	memset(newBuffer, 0x00, length * sizeof(BYTE));
	redimBufferSize(newBuffer, length, dataReserve);
};

// 写入数据
BOOL CByteBuffer::write(int position, BYTE *data, int dataLength, BOOL isIncreaseDataLength, BOOL isIncreaseBufferLength)
{
	if(position<0)
		return FALSE;

	if(!data)
		return FALSE;

	if(dataLength<=0)
		return FALSE;

	if(m_dataLength + dataLength > getBufferLength())
	{
		if(isIncreaseBufferLength)
			redimBufferSize(m_dataLength + dataLength, TRUE);
		else
			return FALSE;
	}

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	memcpy(getDataBuffer() + position, data, dataLength);

	if(isIncreaseDataLength)
		m_dataLength = max(m_dataLength, position+dataLength);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return TRUE;
};

// 追加数据
BOOL CByteBuffer::append(BYTE *data, int dataLength, BOOL isIncreaseBufferLength)
{
	if(!data)
		return FALSE;
	
	if(dataLength<=0)
		return FALSE;

	if(m_dataLength+dataLength>getBufferLength())
	{
		if(isIncreaseBufferLength)
			redimBufferSize(m_dataLength + dataLength, TRUE);
		else
			return FALSE;
	}
	
	return write(m_dataLength, data, dataLength, TRUE, isIncreaseBufferLength);
};

// 更新数据
BOOL CByteBuffer::update(int position, BYTE *data, int dataLength, BOOL isIncreaseBufferLength)
{
	if(position<0 || position>=getBufferLength())
		return FALSE;

	if(!data)
		return FALSE;

	if(dataLength<=0)
		return FALSE;

	if(position + dataLength >= getBufferLength())
	{
		if(isIncreaseBufferLength)
			redimBufferSize(position+dataLength, TRUE);
		else
			return FALSE;
	}

	return write(position, data, dataLength, TRUE, isIncreaseBufferLength);
}

// 读数据
BOOL CByteBuffer::read(int position, BYTE *data, int dataLength)
{
	if(!data)
		return FALSE;
	
	if(dataLength<=0)
		return FALSE;
	
	if(position+dataLength>getBufferLength())
		return FALSE;

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	memcpy(data, getDataBuffer()+position, dataLength);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return TRUE;
};

// 清空数据
void CByteBuffer::clearData()
{
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	m_dataLength=0;
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
}

// 获取数据区起始地址
BYTE *CByteBuffer::getDataStart()
{
	return getDataBuffer();
}
	
// 获取数据长度
int CByteBuffer::getDataLength()
{
	return m_dataLength;
}

// 获取全部数据
void CByteBuffer::getTotalData(BYTE *data, int *dataLength)
{
	*dataLength=m_dataLength;
	if(m_dataLength>0)
		memcpy(data, getDataBuffer(), m_dataLength);
}
