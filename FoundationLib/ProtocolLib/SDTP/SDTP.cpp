// SDTP.cpp: implementation of the CSDTP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SDTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSDTP::CSDTP()
{
	m_buffer.setHeadLength(SDTP_HEAD_LENGTH);
}

CSDTP::~CSDTP()
{

}

// 初始化
void CSDTP::init()
{
	m_buffer.init();
}

// 生成协议标志和协议版本
void CSDTP::genHead(char flag[SDTP_FLAG_LENGTH], char ver[SDTP_VERTION_LENGTH])
{
	setProtocolFlagInHead(flag);
	setVersionInHead(ver);
}

void CSDTP::genHead(char flag1, char flag2, char flag3, char flag4, char ver1, char ver2, char ver3, char ver4)
{
	setProtocolFlagInHead(flag1, flag2, flag3, flag4);
	setVersionInHead(ver1, ver2, ver3, ver4);
}

// 设置协议头中的协议标志
void CSDTP::setProtocolFlagInHead(char c[SDTP_FLAG_LENGTH])
{
	BYTE *buffer=m_buffer.getTotalBuffer();
	memcpy(buffer, c, SDTP_FLAG_LENGTH);
}

void CSDTP::setProtocolFlagInHead(char c1, char c2, char c3, char c4)
{
	char c[SDTP_FLAG_LENGTH];
	if(SDTP_FLAG_LENGTH>=1)
		c[0]=c1;
	if(SDTP_FLAG_LENGTH>=2)
		c[1]=c2;
	if(SDTP_FLAG_LENGTH>=3)
		c[2]=c3;
	if(SDTP_FLAG_LENGTH>=4)
		c[3]=c4;

	BYTE *buffer=m_buffer.getTotalBuffer();
	memcpy(buffer, c, SDTP_FLAG_LENGTH);
}

// 获取协议头中的协议标志
void CSDTP::getProtocolFlagInHead(char c[SDTP_FLAG_LENGTH])
{
	BYTE *buffer=m_buffer.getTotalBuffer();
	memcpy(c, buffer, SDTP_FLAG_LENGTH);
}

void CSDTP::getProtocolFlagInHead(char *c1, char *c2, char *c3, char *c4)
{
	char c[SDTP_FLAG_LENGTH];

	BYTE *buffer=m_buffer.getTotalBuffer();
	memcpy(c, buffer, SDTP_FLAG_LENGTH);

	if(SDTP_FLAG_LENGTH>=1)
		*c1=c[0];
	if(SDTP_FLAG_LENGTH>=2)
		*c2=c[1];
	if(SDTP_FLAG_LENGTH>=3)
		*c3=c[2];
	if(SDTP_FLAG_LENGTH>=4)
		*c3=c[4];
}

// 设置协议头中的版本号
void CSDTP::setVersionInHead(char v[SDTP_VERTION_LENGTH])
{
	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH;
	memcpy(buffer, v, SDTP_VERTION_LENGTH);
}

void CSDTP::setVersionInHead(char v1, char v2, char v3, char v4)
{
	char v[SDTP_VERTION_LENGTH];
	if(SDTP_VERTION_LENGTH>=1)
		v[0]=v1;
	if(SDTP_VERTION_LENGTH>=2)
		v[1]=v2;
	if(SDTP_VERTION_LENGTH>=3)
		v[2]=v3;
	if(SDTP_VERTION_LENGTH>=4)
		v[3]=v4;
	
	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH;
	memcpy(buffer, v, SDTP_VERTION_LENGTH);

}

// 获取协议头中的版本号
void CSDTP::getVersionInHead(char v[SDTP_VERTION_LENGTH])
{
	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH;
	memcpy(v, buffer, SDTP_VERTION_LENGTH);
}

void CSDTP::getVersionInHead(char *v1, char *v2, char *v3, char *v4)
{
	char v[SDTP_VERTION_LENGTH];
	
	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH;
	memcpy(v, buffer, SDTP_VERTION_LENGTH);
	
	if(SDTP_VERTION_LENGTH>=1)
		*v1=v[0];
	if(SDTP_VERTION_LENGTH>=2)
		*v2=v[1];
	if(SDTP_VERTION_LENGTH>=3)
		*v3=v[2];
	if(SDTP_VERTION_LENGTH>=4)
		*v3=v[4];
}

// 设置协议头中的数据长度
void CSDTP::setDataLengthInHead(int len)
{
	if(len<0)
		return;

	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH + SDTP_VERTION_LENGTH;
	memcpy(buffer, &len, min(SDTP_DATA_LENGTH,4));
}

// 获取协议头中的数据长度
void CSDTP::getDataLengthInHead(int *len)
{
	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH + SDTP_VERTION_LENGTH;
	int l=0;
	memcpy(&l, buffer, min(SDTP_DATA_LENGTH, 4));
	*len=l;
}

// 设置协议头中的数据校验
void CSDTP::setCheckCodeInHead(int checkCode)
{
	if(checkCode<0)
		return;

	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH + SDTP_VERTION_LENGTH + SDTP_DATA_LENGTH;
	memcpy(buffer, &checkCode, min(SDTP_DATA_CODE_LENGTH,4));
}

// 获取协议头中的数据校验
void CSDTP::getCheckCodeInHead(int *checkCode)
{
	BYTE *buffer=m_buffer.getTotalBuffer() + SDTP_FLAG_LENGTH + SDTP_VERTION_LENGTH + SDTP_DATA_LENGTH;
	int code=0;
	memcpy(&code, buffer, min(SDTP_DATA_CODE_LENGTH, 4));
	*checkCode=code;
}

// 设置数据内容
BOOL CSDTP::appendData(char *data, int dataLength)
{
	if(!data)
		return FALSE;

	if(dataLength<=0)
		return FALSE;

	return m_buffer.appendBytes(data, dataLength);
}

// 获取数据内容
BOOL CSDTP::getData(char *data)
{
	if(!data)
		return FALSE;

	if(m_buffer.getDataLength()>0)
	{
		memcpy(data, m_buffer.getDataBuffer(), m_buffer.getDataLength());
		return TRUE;
	}
	else
		return FALSE;
}

// 获取数据长度
int CSDTP::getDataLength()
{
	return m_buffer.getDataLength();
}

// 设置整个数据（从协议头起始处开始写入）
BOOL CSDTP::setTotalData(char *data, int dataLength)
{
	if(!data)
		return FALSE;

	if(dataLength<=0)
		return FALSE;

	if(dataLength<SDTP_HEAD_LENGTH)
		return FALSE;

	m_buffer.setTotalData(data, dataLength);
	return TRUE;
}

// 获取整个数据（从协议头起始处开始读取）
BOOL CSDTP::getTotalData(char *data)
{
	if(!data)
		return FALSE;

	BYTE *buffer=m_buffer.getTotalBuffer();
	memcpy(data, buffer, getTotalDataLength());
	return TRUE;
}

// 获取整个数据长度（包括协议头）
int CSDTP::getTotalDataLength()
{
	return m_buffer.getDataLength() + SDTP_HEAD_LENGTH;
}

// 生成校验码
int CSDTP::genCheckCode()
{
	int len=m_buffer.getDataLength();
	if(len<=0)
		return -1;

	char *data=new char[len];
	getData(data);

	int sum=0;
	for(int i=0;i<len;i++)
		sum+=data[i];

	delete data;

	return sum % 256;
}

// 验证校验码
BOOL CSDTP::verifyCheckCode(int checkCode)
{
	if(checkCode==genCheckCode())
		return TRUE;
	else
		return FALSE;
}

// 设置缓冲区大小
BOOL CSDTP::setBufferLength(int bufferLength)
{
	if(bufferLength<=0)
		return FALSE;

	m_buffer.redimBufferLength(bufferLength);
	return TRUE;
}
