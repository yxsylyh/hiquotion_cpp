#pragma once

extern "C"
{
#include <C++\3rdParty\G729A\va_g729a.h>
};

// 解码前的长度以在库中修正，修正为 10 字节

class CVA_G729ADecoder
{
public:
	CVA_G729ADecoder(void);
	~CVA_G729ADecoder(void);

	void init();

	// src长度和dst长度都是固定的
	// 库以 Word16（32位下应该是 2 字节，64位下为 4 字节） 为长度单位处理数据
	// xxx src长度 = SERIAL_SIZE（库中定义为是80+2） × sizeof(Word16) = 164（32位下）或 328（64位下）
	// src长度已修正为 10 字节
	// dst长度 = L_FRAME（库中定义为是80） × sizeof(Word16) = 160（32位下）或 320（64位下）
	int decode(char *src, char *dst);

	// 解码
	// 原长度必须是 10 的整数倍
	int decodeEx(char *src, unsigned int srcLen, char *dst);

private:
// 	Word16  synth_buf[L_FRAME+M], *synth; /* Synthesis                   */
// 	Word16  parm[PRM_SIZE+1];             /* Synthesis parameters        */
// // 	Word16  serial[SERIAL_SIZE];          /* Serial stream               */
// 	unsigned char serial[SERIAL_SIZE];          /* Serial stream               */
// 	Word16  Az_dec[MP1*2], *ptr_Az;       /* Decoded Az for post-filter  */
// 	Word16  T0_first;                     /* Pitch lag in 1st subframe   */
// 	Word16  pst_out[L_FRAME];             /* Postfilter output           */
// 
// 	Word16  voicing;                      /* voicing from previous frame */
// 	Word16  sf_voic;                      /* voicing for subframe        */
// 
// 	Word16  i, frame;
// 
// 	Word16 srcLen;
// 	Word16 dstLen;
};
