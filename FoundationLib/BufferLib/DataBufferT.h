// DataBuffer.h: interface for the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUFFER_H__2DA3DE94_5BAB_442C_B581_A41E355FEE05__INCLUDED_)
#define AFX_DATABUFFER_H__2DA3DE94_5BAB_442C_B581_A41E355FEE05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SUPPORT_MULTI_THREAD
#include <afxmt.h>
#endif

#define DEFAULT_BUFFER_LENGTH 40960

template <class T>
class CDataBufferT  
{
public:
	CDataBufferT()
	{
		m_dataBuffer=new T[DEFAULT_BUFFER_LENGTH * sizeof(T)];
		m_bufferLength=DEFAULT_BUFFER_LENGTH;
		m_dataLength=0;
		m_currentPosition=0;
		m_currentPosition=0;
	};

	CDataBufferT(int length)
	{
		m_dataBuffer=new T[length * sizeof(T)];
		m_bufferLength=length;
		m_dataLength=0;
		m_currentPosition=0;
		m_currentPosition=0;
	};

	virtual ~CDataBufferT()
	{
		delete m_dataBuffer;
	};

	// 重新定义缓冲区大小
	void redimBufferSize(T *buffer, int length, BOOL dataReserve=FALSE)
	{
		if(!buffer)
			return;

		if(length<=0)
			return;

#ifdef SUPPORT_MULTI_THREAD
		m_lock.Lock();
#endif

		T *newBuffer=buffer; //new T[length * sizeof(T)];
		if(dataReserve)
		{
			memcpy(newBuffer, m_dataBuffer, min(m_dataLength, length)*sizeof(T));
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
	void redimBufferSize(int length, BOOL dataReserve=FALSE)
	{
		if(length<=0)
			return;

		T *newBuffer=new T[length * sizeof(T)];
		memset(newBuffer, 0x00, length * sizeof(T));
		redimBufferSize(newBuffer, length, dataReserve);
	};

	// 写入数据
	BOOL write(int position, T *data, int dataLength, BOOL isIncreaseDataLength=TRUE, BOOL isIncreaseBufferLength=FALSE)
	{
		if(position<0)
			return FALSE;

		if(!data)
			return FALSE;

		if(dataLength<=0)
			return FALSE;

		if(m_dataLength + dataLength > m_bufferLength)
		{
			if(isIncreaseBufferLength)
				redimBufferSize(m_dataLength + dataLength, TRUE);
			else
				return FALSE;
		}

#ifdef SUPPORT_MULTI_THREAD
		m_lock.Lock();
#endif
		memcpy(m_dataBuffer + position, data, dataLength * sizeof(T));

		if(isIncreaseDataLength)
			m_dataLength = max(m_dataLength, position+dataLength);

#ifdef SUPPORT_MULTI_THREAD
		m_lock.Unlock();
#endif

		return TRUE;
	};

	// 追加数据
	BOOL append(T *data, int dataLength, BOOL isIncreaseBufferLength=FALSE)
	{
		if(!data)
			return FALSE;
		
		if(dataLength<=0)
			return FALSE;

		if(m_dataLength+dataLength>m_bufferLength)
		{
			if(isIncreaseBufferLength)
				redimBufferSize(m_dataLength + dataLength, TRUE);
			else
				return FALSE;
		}
		
		return write(m_dataLength, data, dataLength, TRUE, isIncreaseBufferLength);
	};

	BOOL update(int position, T *data, int dataLength, BOOL isIncreaseBufferLength=FALSE)
	{
		if(position<0 || position>=m_bufferLength)
			return FALSE;

		if(!data)
			return FALSE;

		if(dataLength<=0)
			return FALSE;

		if(position + dataLength >= m_bufferLength)
		{
			if(isIncreaseBufferLength)
				redimBufferSize(position+dataLength, TRUE);
			else
				return FALSE;
		}

		return write(position, data, dataLength, TRUE, isIncreaseBufferLength);
	}

	// 读数据
	BOOL read(int position, T *data, int dataLength, BOOL isForwardCurrentPosition=TRUE)
	{
		if(!data)
			return FALSE;
		
		if(dataLength<=0)
			return FALSE;
		
		if(position+dataLength>m_bufferLength)
			return FALSE;

#ifdef SUPPORT_MULTI_THREAD
		m_lock.Lock();
#endif
		memcpy(data, m_dataBuffer+position, dataLength*sizeof(T));

		if(isForwardCurrentPosition)
			m_currentPosition+=dataLength;

#ifdef SUPPORT_MULTI_THREAD
		m_lock.Unlock();
#endif

		return TRUE;
	};

	// 读数据
	BOOL read(T *data, int dataLength, BOOL isForwardCurrentPosition=TRUE)
	{
		if(!data)
			return FALSE;
		
		if(dataLength<=0)
			return FALSE;
		
		if(m_currentPosition+dataLength>m_bufferLength)
			return FALSE;

		return read(m_currentPosition, data, dataLength, isForwardCurrentPosition);
	}

	// 清空数据
	void clearData()
	{
#ifdef SUPPORT_MULTI_THREAD
		m_lock.Lock();
#endif
		m_dataLength=0;
		m_currentPosition=0;
#ifdef SUPPORT_MULTI_THREAD
		m_lock.Unlock();
#endif
	}

	// 获取数据区起始地址
	T *getDataHead()
	{
		return m_dataBuffer;
	}
	
	// 获取数据长度
	int getDataLength() const { return m_dataLength; }

	// 获取全部数据
	int getTotalData(T *data, int *dataLength)
	{
		*dataLength=m_dataLength;
		memcpy(data, m_dataBuffer, m_dataLength * sizeof(T));
	}

private:
	T *m_dataBuffer;
	int m_bufferLength;
	int m_dataLength;
	int m_currentPosition;

#ifdef SUPPORT_MULTI_THREAD
	CMutex m_lock;
#endif
};

#endif // !defined(AFX_DATABUFFER_H__2DA3DE94_5BAB_442C_B581_A41E355FEE05__INCLUDED_)
