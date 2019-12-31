#pragma once

#include <C++\3rdParty\Speex\speex.h>

#define FRAME_SIZE 160

// Speex 编码器
// 注：根据官方文档，Speex 不是线程安全的，所以该类也不是线程安全的
// 线程中执行编码时，请加锁
// 以后有机会看直接加上锁，省得外部费事

class CSpeexEncoder
{
public:
	CSpeexEncoder(void);
	~CSpeexEncoder(void);

	BOOL init(int quality=8);
	BOOL encode(float *src, int srcLen, char *dst, int *dstLen);
	void destroy();

private:
	SpeexBits bits;
	void *state;
};
