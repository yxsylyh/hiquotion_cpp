// DataBuffer.h: interface for the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUFFER_H__8097583E_1F6A_4B96_A25F_0793B00B8BA4__INCLUDED_)
#define AFX_DATABUFFER_H__8097583E_1F6A_4B96_A25F_0793B00B8BA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferOperation.h"

// 数据缓冲区类
// 1、在缓冲区操作类的基础上，使用一个数据区
// 2、可以顺序追加数据，可以顺序读取数据，而不需要指定读取的起始位置
// 3、在数据区的前面，指定一定字节大小的数据头
// 4、本类的扩展类可以在指定大小的数据头部定义读取各种数据类型数据的操作
class CDataBuffer : public CBufferOperation  
{
public:
	CDataBuffer();
	CDataBuffer(unsigned int headLength);
	virtual ~CDataBuffer();

	// 初始化
	void init();

	// 读、写全部数据字节数组
	int readTotalData(char *data, int dataLength);
	int writeTotalData(char *data, int dataLength);
	
	// 读、写当前位置开始及指定长度的字节数组
	int readBytes(char *data, int dataLength);
	int appendBytes(char *data, int dataLength);
	
	// 读、写当前位置开始的1个字节
	int readByte(unsigned char *data);
	int appendByte(unsigned char data);
	
	// 读、写当前位置开始的4字节整型
	int readLong(int *lng);
	int writeLong(int lng);
	
	// 读、写当前位置开始的2字节整型
	int readInteger(short *integer);
	int writeInteger(short integer);
	
	// 读、写当前位置开始及指定长度的字符串
	int readString(std::string &str, unsigned int length);
	int writeString(std::string str, unsigned int length);
	int readString(CString &str, unsigned int length);
	int writeString(CString str, unsigned int length);

	// 获取和设置当前数据索引
	unsigned int getDataIndex() const { return m_dataIndex; }
	void setDataIndex(unsigned int val) { m_dataIndex = val; }

	// 获取数据长度
	unsigned int getDataLength() const { return m_dataLength; }

	// 继承父类的方法
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


protected:
	unsigned int m_dataIndex;
	unsigned int m_dataLength;
};

#endif // !defined(AFX_DATABUFFER_H__8097583E_1F6A_4B96_A25F_0793B00B8BA4__INCLUDED_)
