#include "stdafx.h"
#include "VA_G729ADecoder.h"

CVA_G729ADecoder::CVA_G729ADecoder(void)
{
	init();
}

CVA_G729ADecoder::~CVA_G729ADecoder(void)
{
}

void CVA_G729ADecoder::init()
{
	/*-----------------------------------------------------------------*
	*           Initialization of decoder                             *
	*-----------------------------------------------------------------*/

	va_g729a_init_decoder();
}

// src长度和dst长度都是固定的
// 库以 Word16（32位下应该是 2 字节，64位下为 4 字节） 为长度单位处理数据
// src长度 = SERIAL_SIZE（库中定义为是80） × sizeof(Word16) = 160（32位下）或 320（64位下）
// dst长度 = L_FRAME（库中定义为是80+2） × sizeof(Word16) = 164（32位下）或 328（64位下）
int CVA_G729ADecoder::decode(char *src, char *dst)
{
	if(!src || !dst)
		return -1;

	va_g729a_decoder((unsigned char *)src, (short *)dst, 0);

	return 0;
}

// 解码
// 原长度必须是 10 的整数倍
int CVA_G729ADecoder::decodeEx(char *src, unsigned int srcLen, char *dst)
{
	int count=srcLen / 10;
	for(int i=0;i<count;i++)
	{
		decode((char *)(src + i * 10), (char *)(dst + i * 160));
	}

	return 0;
}
