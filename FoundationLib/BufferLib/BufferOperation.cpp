// DataBuffer.cpp: implementation of the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBufferOperation::CBufferOperation(unsigned int bufferLength)
: m_headLength(0)//, m_dataLength(0)
{
	unsigned int length=bufferLength;
	if(length==0)
		length=MAX_BUFFER_LENGTH;

	m_buffer=new char[length];
	m_bufferLength=length;
}

CBufferOperation::~CBufferOperation()
{
	delete m_buffer;
	m_buffer=NULL;
}

// 重定义缓冲区大小（默认不保留原缓冲区中的数据）
// 重定义后比原来小的情况暂时不考虑
int CBufferOperation::redimBufferLength(int bufferLength, BOOL reserveData)
{
	if(bufferLength<m_bufferLength)
		return 0;

	char *buffer=new char[bufferLength];
	memset(buffer, 0x00, bufferLength);
	memcpy(buffer, m_buffer, m_bufferLength);

	delete m_buffer;
	m_buffer=buffer;
	m_bufferLength=bufferLength;

	return 0;
}

// 读、写全部缓冲区字节数组
// 返回值：
// 0，成功
// -1，data为空，或*data为空
int CBufferOperation::readTotalBuffer(char *data)
{
	if(!data)
		return -1;

	memcpy(data, m_buffer+m_headLength, m_bufferLength-m_headLength);
	return 0;
}

// 返回值：
// 0，成功
// -1，data为空
int CBufferOperation::writeTotalBuffer(char *data)
{
	if(!data)
		return -1;

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif

	memcpy(m_buffer+m_headLength, data, m_bufferLength-m_headLength);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
return 0;
}

// 读、写指定位置开始及指定长度的字节数组
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，读取的长度非正，或超出了从pos位置之后的缓冲区长度
int CBufferOperation::readBytes(unsigned int pos, char *data, int dataLength)
{
	if(pos>=m_bufferLength)
		return -1;

	if(dataLength<=0 || dataLength>m_bufferLength-1-pos)
		return -2;

	memcpy(data, m_buffer+m_headLength+pos, dataLength);
	return 0;
}

// 返回值：
// 0，成功
// -1，写入的位置超出了缓冲区长度-1
// -2，写入的长度非正，或超出了从pos位置之后的缓冲区长度
int CBufferOperation::writeBytes(unsigned int pos, char *data, int dataLength)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(dataLength<=0 || dataLength>m_bufferLength-1-pos)
		return -2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, data, dataLength);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// 读、写指定位置开始的1个字节
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，data为空
int CBufferOperation::readByte(unsigned int pos, unsigned char *data)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(!data)
		return -2;

	*data=m_buffer[m_headLength+pos];
	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
int CBufferOperation::writeByte(unsigned int pos, unsigned char data)
{
	if(pos>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	m_buffer[m_headLength+pos]=data;

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// 读、写指定位置开始的4字节整型
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，整型变量指针为空
int CBufferOperation::readLong(unsigned int pos, int *lng)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(!lng)
		return -2;

	memcpy(lng, m_buffer+m_headLength+pos, 4);
	return 0;
}

// 0，成功
// -1，读取的位置超出了缓冲区长度-1
int CBufferOperation::writeLong(unsigned int pos, int lng)
{
	if(pos>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, &lng, 4);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// 读、写指定位置开始的2字节整型
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，整型变量指针为空
int CBufferOperation::readInteger(unsigned int pos, short *integer)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(!integer)
		return -2;
	
	memcpy(integer, m_buffer+m_headLength+pos, 2);
	return 0;

}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
int CBufferOperation::writeInteger(unsigned int pos, short integer)
{
	if(pos>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, &integer, 2);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// // 读、写指定位置开始的1个字符
// int CDataBuffer::readChar(unsigned int pos, char *data)
// {
// 
// }
// 
// int CDataBuffer::writeChar(unsigned int pos, char data)
// {
// 
// }

// 读、写指定位置开始及指定长度的字符串
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CBufferOperation::readString(unsigned int pos, std::string &str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;

	char *ch=new char[length+1];
	readBytes(pos, ch, length);
	ch[length]='\0';
	str=ch;
	delete ch;
	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CBufferOperation::writeString(unsigned int pos, std::string str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, str.c_str(), length);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CBufferOperation::readString(unsigned int pos, CString &str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;
	
	std::string s;
	readString(pos, s, length);
	str=s.c_str();
	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CBufferOperation::writeString(unsigned int pos, CString str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;
	
	std::string s=(LPTSTR)(LPCSTR)str;
	writeString(pos, s, length);
	return 0;
}
