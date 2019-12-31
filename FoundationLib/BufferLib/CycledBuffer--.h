// CycledBuffer.h: interface for the CCycledBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYCLEDBUFFER_H__015A0855_671E_4402_A97D_07E5E1C89090__INCLUDED_)
#define AFX_CYCLEDBUFFER_H__015A0855_671E_4402_A97D_07E5E1C89090__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>

#define DEFAULT_BUFFER_LENGTH 10240000

class CCycledBuffer  
{
public:
	CCycledBuffer();
	CCycledBuffer(unsigned int bufferLength);
// 	CCycledBuffer(char *buffer, unsigned int bufferLength);
	virtual ~CCycledBuffer();

	// 初始化
	void init();

	// 获取缓冲区长度
	unsigned int getBufferLength();

	// 获取缓冲区剩余长度
	unsigned int getRestLength();
	// 获取数据长度
	unsigned int getDataLength();
	// 写入数据
	int write(char *data, unsigned int dataLength);
	// 读取数据
	int read(char *data, unsigned int dataLength);

	// 重定义缓冲区大小
	void redimLength(unsigned int length, BOOL reserveData=TRUE);

	char *getCycledBuffer() const { return m_cycledBuffer; }

	unsigned int getStartIndex() const { return m_startIndex; }
	unsigned int getEndIndex() const { return m_endIndex; }

	// 退出等待状态
	void exitWaiting();

#ifdef _DEBUG

	// for test only
	void setStartIndex(unsigned int val) { m_startIndex = val; }

	// for test only
	void setEndIndex(int val) { m_endIndex = val; }

	// for test only
	BOOL isEmpty() const { return m_isEmpty; }
	// for test only
	void setEmpty(BOOL val) { m_isEmpty = val; }

	// for test only
	void setBufferData(int index, char data)
	{
		if(index<0 || index>m_bufferLength)
			return;

		m_cycledBuffer[index]=data;
	};

	char getBufferData(int index)
	{
		if(index<0 || index>m_bufferLength)
			return 0;

		return m_cycledBuffer[index];
	}

#endif

private:
	char *m_cycledBuffer;
	unsigned int m_bufferLength;
	BOOL m_isBufferOutside;

	unsigned int m_startIndex;  // 起始位置索引
	int m_endIndex;    // 结束位置索引
	BOOL m_isEmpty;             // 如果结束索引在开始索引的后一位置，则判断不出来是没有数据还是数据已满，所以用这个变量来判断
	CMutex m_writeLock;
	CMutex m_readLock;
// 	CSemaphore *m_notFull;
// 	CSemaphore *m_notEmpty;

	CEvent m_notFull;
	CEvent m_notEmpty;

	int m_waitedReadLength;
	int m_waitedWriteLength;

	BOOL m_isExit;
};

#endif // !defined(AFX_CYCLEDBUFFER_H__015A0855_671E_4402_A97D_07E5E1C89090__INCLUDED_)
