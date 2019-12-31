// DataBuffer.h: interface for the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUFFER_H__BEED6793_FA14_4B6C_B9DD_F7C7E622F10C__INCLUDED_)
#define AFX_DATABUFFER_H__BEED6793_FA14_4B6C_B9DD_F7C7E622F10C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SUPPORT_MULTI_THREAD

#ifdef SUPPORT_MULTI_THREAD
#include <afxmt.h>
#endif
#include <string>

#define MAX_BUFFER_LENGTH 200000

// 缓冲区操作类
// 把整个缓冲区当作可以操作的数据区
// 提供最基本的读写功能
class CBufferOperation  
{
public:
	CBufferOperation(unsigned int bufferLength=MAX_BUFFER_LENGTH);
	virtual ~CBufferOperation();

	// 获取缓冲区长度
	unsigned int getBufferLength() const { return m_bufferLength; }
// 	void setBufferLength(unsigned int val) { m_bufferLength = val; }

// 	// x下面这个函数不加了，容易导致正在读取缓冲区时缓冲区中的数据被破坏的情况（猜测），而且不容易加以保护
	// 重定义缓冲区大小（默认不保留原缓冲区中的数据）
	// 重定义后比原来小的情况暂时不考虑
	int redimBufferLength(int bufferLength, BOOL reserveData=FALSE);

// 	// 获取数据长度
// 	unsigned int getDataLength() const { return m_dataLength; }

	// 读、写全部缓冲区字节数组
	int readTotalBuffer(char *data);
	int writeTotalBuffer(char *data);

	// 读、写指定位置开始及指定长度的字节数组
	int readBytes(unsigned int pos, char *data, int dataLength);
	int writeBytes(unsigned int pos, char *data, int dataLength);

	// 读、写指定位置开始的1个字节
	int readByte(unsigned int pos, unsigned char *data);
	int writeByte(unsigned int pos, unsigned char data);

	// 读、写指定位置开始的4字节整型
	int readLong(unsigned int pos, int *lng);
	int writeLong(unsigned int pos, int lng);

	// 读、写指定位置开始的2字节整型
	int readInteger(unsigned int pos, short *integer);
	int writeInteger(unsigned int pos, short integer);

// 	// 读、写指定位置开始的1个字符
// 	int readChar(unsigned int pos, char *data);
// 	int writeChar(unsigned int pos, char data);

	// 读、写指定位置开始及指定长度的字符串
	int readString(unsigned int pos, std::string &str, unsigned int length);
	int writeString(unsigned int pos, std::string str, unsigned int length);
	int readString(unsigned int pos, CString &str, unsigned int length);
	int writeString(unsigned int pos, CString str, unsigned int length);

	unsigned int getHeadLength() const { return m_headLength; }
	void setHeadLength(unsigned int val) { m_headLength = val; }

protected:
	unsigned int m_bufferLength;

	unsigned int m_headLength;
	char *m_buffer;

#ifdef SUPPORT_MULTI_THREAD
	CMutex m_lock;
#endif

};

#endif // !defined(AFX_DATABUFFER_H__BEED6793_FA14_4B6C_B9DD_F7C7E622F10C__INCLUDED_)
