// SDTP.h: interface for the CSDTP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDTP_H__C4AC6824_B31B_48A1_9318_B8BF78A0C93F__INCLUDED_)
#define AFX_SDTP_H__C4AC6824_B31B_48A1_9318_B8BF78A0C93F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\BufferLib\HeaderBuffer.h>

// SDTP——简单数据传输协议
// 协议格式：协议头 + 数据
// 协议头（16字节）
// 协议标志：sdtp（简单数据传输协议） —— 4 字节
// 版本号：1.0.0.0                    —— 4 字节
// 数据长度：                         —— 4 字节
// 数据校验：                         —— 4 字节
// 数据：实际传输的数据

// 校验方法：
// 数据求和，再模256

// 该类对每个需要传输的数据都封装成这样的带简单协议的数据，然后再发送
// 接收数据后，先根据协议头判断数据长度，并判断数据是否接收足够，接收足够后，抛出事件（事件中包括实际传输的数据和长度属性）

#define SDTP_FLAG_LENGTH      4
#define SDTP_VERTION_LENGTH   4
#define SDTP_DATA_LENGTH      4
#define SDTP_DATA_CODE_LENGTH 4
#define SDTP_HEAD_LENGTH      SDTP_FLAG_LENGTH + SDTP_VERTION_LENGTH + SDTP_DATA_LENGTH + SDTP_DATA_CODE_LENGTH

class CSDTP  
{
public:
	CSDTP();
	virtual ~CSDTP();

	// 初始化
	void init();

	// 生成协议标志和协议版本
	void genHead(char flag[SDTP_FLAG_LENGTH], char ver[SDTP_VERTION_LENGTH]);
	void genHead(char flag1, char flag2, char flag3, char flag4, char ver1, char ver2, char ver3, char ver4);

	// 设置协议头中的协议标志
	void setProtocolFlagInHead(char c[SDTP_FLAG_LENGTH]);
	void setProtocolFlagInHead(char c1, char c2, char c3, char c4);

	// 获取协议头中的协议标志
	void getProtocolFlagInHead(char c[SDTP_FLAG_LENGTH]);
	void getProtocolFlagInHead(char *c1, char *c2, char *c3, char *c4);
	

	// 设置协议头中的版本号
	void setVersionInHead(char v[SDTP_VERTION_LENGTH]);
	void setVersionInHead(char v1, char v2, char v3, char v4);

	// 获取协议头中的版本号
	void getVersionInHead(char v[SDTP_VERTION_LENGTH]);
	void getVersionInHead(char *v1, char *v2, char *v3, char *v4);
	

	// 设置协议头中的数据长度
	void setDataLengthInHead(int len);

	// 获取协议头中的数据长度
	void getDataLengthInHead(int *len);
	

	// 设置协议头中的数据校验
	void setCheckCodeInHead(int checkCode);

	// 获取协议头中的数据校验
	void getCheckCodeInHead(int *checkCode);
	

	// 设置数据内容
	BOOL appendData(char *data, int dataLength);

	// 获取数据内容
	BOOL getData(char *data);


	// 获取数据长度
	int getDataLength();


	// 设置整个数据（从协议头起始处开始写入）
	BOOL setTotalData(char *data, int dataLength);

	// 获取整个数据（从协议头起始处开始读取）
	BOOL getTotalData(char *data);


	// 获取整个数据长度（包括协议头）
	int getTotalDataLength();
	

	// 生成校验码
	virtual int genCheckCode();
	// 验证校验码
	virtual BOOL verifyCheckCode(int checkCode);
	

	// 设置缓冲区大小
	BOOL setBufferLength(int bufferLength);

protected:
	CHeaderBuffer m_buffer;
};

#endif // !defined(AFX_SDTP_H__C4AC6824_B31B_48A1_9318_B8BF78A0C93F__INCLUDED_)
