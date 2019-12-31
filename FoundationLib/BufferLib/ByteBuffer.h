// CharBuffer.h: interface for the CCharBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARBUFFER_H__2752D2AB_91A4_4974_BFE5_521C9389518E__INCLUDED_)
#define AFX_CHARBUFFER_H__2752D2AB_91A4_4974_BFE5_521C9389518E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DATA_BUFFER 10000

class CByteBuffer
{
public:
	CByteBuffer();
	virtual ~CByteBuffer();

	// 重新定义缓冲区大小
	virtual void redimBufferSize(BYTE *buffer, int length, BOOL dataReserve=FALSE);
	// 重新定义缓冲区大小
	virtual void redimBufferSize(int length, BOOL dataReserve=FALSE);
	// 写入数据
	virtual BOOL write(int position, BYTE *data, int dataLength, BOOL isIncreaseDataLength=TRUE, BOOL isIncreaseBufferLength=FALSE);
	// 追加数据
	virtual BOOL append(BYTE *data, int dataLength, BOOL isIncreaseBufferLength=FALSE);
	// 更新数据
	virtual BOOL update(int position, BYTE *data, int dataLength, BOOL isIncreaseBufferLength=FALSE);
	// 读数据
	virtual BOOL read(int position, BYTE *data, int dataLength);
	// 清空数据
	virtual void clearData();
	// 获取数据区起始地址
	virtual BYTE *getDataStart();
	// 获取数据长度
	virtual int getDataLength();
	// 获取全部数据
	virtual void getTotalData(BYTE *data, int *dataLength);

	virtual BYTE * getDataBuffer() { return m_dataBuffer; }
	virtual int getBufferLength() { return m_bufferLength; }
	
protected:
	BYTE *m_dataBuffer;
	int m_bufferLength;
	int m_dataLength;
	
#ifdef SUPPORT_MULTI_THREAD
	CMutex m_lock;
#endif

};

#endif // !defined(AFX_CHARBUFFER_H__2752D2AB_91A4_4974_BFE5_521C9389518E__INCLUDED_)
