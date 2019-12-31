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

CDataBuffer::CDataBuffer()
{
	m_headLength=0;
	init();
}

CDataBuffer::CDataBuffer(unsigned int headLength)
{
	m_headLength=headLength;
	init();
}

CDataBuffer::~CDataBuffer()
{

}

// 初始化
void CDataBuffer::init()
{
	m_dataIndex=0;
	m_dataLength=0;
}

// 读、写全部数据字节数组
// 返回值：
// 0，成功
// -1，data为空，或*data为空
// -2，数据长度非正，或超出了缓冲区大小
int CDataBuffer::readTotalData(char *data, int dataLength)
{
	if(!data)
		return -1;
	
	if(dataLength<=0 || dataLength>m_bufferLength)
		return -2;
	
	memcpy(data, m_buffer+m_headLength, dataLength);
	return 0;
}

// 返回值：
// 0，成功
// -1，data为空
// -2，数据长度非正，或超出了缓冲区大小
int CDataBuffer::writeTotalData(char *data, int dataLength)
{
	if(!data)
		return -1;
	
	if(dataLength<=0 || dataLength>m_bufferLength)
		return -2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength, data, dataLength);
	
	m_dataLength+=dataLength;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return 0;
}

// 读、写当前位置开始及指定长度的字节数组
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，读取的长度非正，或超出了从pos位置之后的缓冲区长度
int CDataBuffer::readBytes(char *data, int dataLength)
{
	if(m_dataIndex>=m_dataLength)
		return -1;

	if(dataLength<=0 || dataLength>m_dataLength-m_dataIndex)
		return -2;

	CBufferOperation::readBytes(m_dataIndex, data, dataLength);

// 	memcpy(*data, m_buffer+m_headLength+m_dataIndex, dataLength);

	m_dataIndex+=dataLength;
	return 0;
}

// 返回值：
// 0，成功
// -1，写入的位置超出了缓冲区长度-1
// -2，写入的长度非正，或超出了从pos位置之后的缓冲区长度
int CDataBuffer::appendBytes(char *data, int dataLength)
{
	if(m_dataIndex>=m_bufferLength)
		return -1;
	
	if(dataLength<=0 || dataLength>m_bufferLength-m_dataIndex)
		return -2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif

	CBufferOperation::writeBytes(m_dataIndex, data, dataLength);
	
//	memcpy(m_buffer+m_headLength+pos, data, dataLength);

	m_dataLength+=dataLength;
	m_dataIndex+=dataLength;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return 0;
}

// 读、写当前位置开始的1个字节
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，data为空
int CDataBuffer::readByte(unsigned char *data)
{
	if(m_dataIndex>=m_bufferLength)
		return -1;
	
	if(!data)
		return -2;

	CBufferOperation::readByte(m_dataIndex, data);

//	*data=m_buffer[m_headLength+m_dataIndex];
	m_dataIndex+=1;
	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
int CDataBuffer::appendByte(unsigned char data)
{
	if(m_dataIndex>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	CBufferOperation::writeByte(m_dataIndex, data);
//	m_buffer[m_headLength+m_dataIndex]=data;

	m_dataLength+=1;
	m_dataIndex+=1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return 0;
}

// 读、写当前位置开始的4字节整型
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，整型变量指针为空
int CDataBuffer::readLong(int *lng)
{
	if(m_dataIndex>=m_dataLength)
		return -1;
	
	if(!lng)
		return -2;

	CBufferOperation::readLong(m_dataIndex, lng);

// 	memcpy(lng, m_buffer+m_headLength+m_dataIndex, 4);

	m_dataIndex+=4;
	return 0;
}

// 0，成功
// -1，读取的位置超出了缓冲区长度-1
int CDataBuffer::writeLong(int lng)
{
	if(m_dataIndex>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	CBufferOperation::writeLong(m_dataIndex, lng);
// 	memcpy(m_buffer+m_headLength+pos, &lng, 4);

	m_dataLength+=4;
	m_dataIndex+=4;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return 0;
}

// 读、写当前位置开始的2字节整型
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，整型变量指针为空
int CDataBuffer::readInteger(short *integer)
{
	if(m_dataIndex>=m_dataLength)
		return -1;
	
	if(!integer)
		return -2;
	
	CBufferOperation::readInteger(m_dataIndex, integer);
//	memcpy(integer, m_buffer+m_headLength+pos, 2);

	m_dataIndex+=2;

	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
int CDataBuffer::writeInteger(short integer)
{
	if(m_dataIndex>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	CBufferOperation::writeInteger(m_dataIndex, integer);
// 	memcpy(m_buffer+m_headLength+m_dataIndex, &integer, 2);

	m_dataLength+=2;
	m_dataIndex+=2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return 0;
}

// 读、写当前位置开始及指定长度的字符串
// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CDataBuffer::readString(std::string &str, unsigned int length)
{
	if(m_dataIndex>=m_dataLength)
		return -1;
	
	if(length<=0 || length>m_dataLength-m_dataIndex)
		return -2;

// 	char *ch=new char[length+1];
// 	readBytes(m_dataIndex, &ch, length);
// 	ch[length]='\0';
// 	str=ch;
// 	delete ch;

	CBufferOperation::readString(m_dataIndex, str, length);

	m_dataIndex+=length;
	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CDataBuffer::writeString(std::string str, unsigned int length)
{
	if(m_dataIndex>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-m_dataIndex)
		return -2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	CBufferOperation::writeString(m_dataIndex, str, length);
//	memcpy(m_buffer+m_headLength+pos, str.c_str(), length);

	m_dataLength+=length;
	m_dataIndex+=length;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif

	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CDataBuffer::readString(CString &str, unsigned int length)
{
	if(m_dataIndex>=m_dataLength)
		return -1;
	
	if(length<=0 || length>m_dataLength-m_dataIndex)
		return -2;
	
	std::string s;
	readString(s, length);
	str=s.c_str();
	return 0;
}

// 返回值：
// 0，成功
// -1，读取的位置超出了缓冲区长度-1
// -2，指定的长度非正，或超出了从pos位置之后的缓冲区长度
int CDataBuffer::writeString(CString str, unsigned int length)
{
	if(m_dataIndex>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-m_dataIndex)
		return -2;
	
	std::string s=(LPTSTR)(LPCSTR)str;
	writeString(s, length);
	return 0;
}

// 继承父类的方法
// 读、写指定位置开始及指定长度的字节数组
int CDataBuffer::readBytes(unsigned int pos, char *data, int dataLength)
{
	return CBufferOperation::readBytes(pos, data, dataLength);
}

int CDataBuffer::writeBytes(unsigned int pos, char *data, int dataLength)
{
	return CBufferOperation::writeBytes(pos, data, dataLength);
}

// 读、写指定位置开始的1个字节
int CDataBuffer::readByte(unsigned int pos, unsigned char *data)
{
	return CBufferOperation::readByte(pos, data);
}

int CDataBuffer::writeByte(unsigned int pos, unsigned char data)
{
	return CBufferOperation::writeByte(pos, data);
}

// 读、写指定位置开始的4字节整型
int CDataBuffer::readLong(unsigned int pos, int *lng)
{
	return CBufferOperation::readLong(pos, lng);
}

int CDataBuffer::writeLong(unsigned int pos, int lng)
{
	return CBufferOperation::writeLong(pos, lng);
}

// 读、写指定位置开始的2字节整型
int CDataBuffer::readInteger(unsigned int pos, short *integer)
{
	return CBufferOperation::readInteger(pos, integer);
}

int CDataBuffer::writeInteger(unsigned int pos, short integer)
{
	return CBufferOperation::writeInteger(pos, integer);
}

// 	// 读、写指定位置开始的1个字符
// 	int CDataBuffer::readChar(unsigned int pos, char *data);
// 	int CDataBuffer::writeChar(unsigned int pos, char data);

// 读、写指定位置开始及指定长度的字符串
int CDataBuffer::readString(unsigned int pos, std::string &str, unsigned int length)
{
	return CBufferOperation::readString(pos, str, length);
}

int CDataBuffer::writeString(unsigned int pos, std::string str, unsigned int length)
{
	return CBufferOperation::writeString(pos, str, length);
}

int CDataBuffer::readString(unsigned int pos, CString &str, unsigned int length)
{
	return CBufferOperation::readString(pos, str, length);
}

int CDataBuffer::writeString(unsigned int pos, CString str, unsigned int length)
{
	return CBufferOperation::writeString(pos, str, length);
}
