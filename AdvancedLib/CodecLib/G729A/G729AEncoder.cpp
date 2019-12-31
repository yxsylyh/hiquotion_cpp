#include "stdafx.h"
#include "G729AEncoder.h"

CG729AEncoder::CG729AEncoder(void)
{
	srcLen=L_FRAME*sizeof(Word16);
	dstLen=SERIAL_SIZE; //*sizeof(Word16);
	init();
}

CG729AEncoder::~CG729AEncoder(void)
{
}

void CG729AEncoder::init()
{
	/*--------------------------------------------------------------------------*
	* Initialization of the coder.                                             *
	*--------------------------------------------------------------------------*/

	Init_Pre_Process();
	Init_Coder_ld8k();
	for(i=0; i<PRM_SIZE; i++) prm[i] = (Word16)0;

	/* To force the input and output to be time-aligned the variable SYNC
	has to be defined. Note: the test vectors were generated with this option
	disabled
	*/

#ifdef SYNC
	/* Read L_NEXT first speech data */

	fread(&new_speech[-L_NEXT], sizeof(Word16), L_NEXT, f_speech);
#ifdef HARDW
	/* set 3 LSB's to zero */
	for(i=0; i < L_NEXT; i++)
		new_speech[-L_NEXT+i] = new_speech[-L_NEXT+i] & 0xFFF8;
#endif
	Pre_Process(&new_speech[-L_NEXT], L_NEXT);
#endif

}

int CG729AEncoder::encode(char *src, char *dst)
{
	if(!src || !dst)
		return -1;

	// new_speech 在 Init_Pre_Process() 中被初始化，所以 get_new_speech() 必须在 Init_Pre_Process() 之后调用
	Word16 *new_speech=get_new_speech();

	memcpy(new_speech, src, srcLen);
#ifdef HARDW
	/* set 3 LSB's to zero */
	for(i=0; i < L_FRAME; i++) new_speech[i] = new_speech[i] & 0xFFF8;
#endif

	Pre_Process(new_speech, L_FRAME);

	Coder_ld8k(prm, syn);

// 	prm2bits_ld8k( prm, serial);
	prm2bits_ld8k( prm, (unsigned char *)dst);

// 	memcpy(dst, serial, dstLen);

	return 0;
}

// src的长度得是80，Word16是2字节，所以总长度是160
// int CG729AEncoder::encode(Word16 *src, char *dst)
// {
// 	if(!src || !dst)
// 		return -1;
// 
// 	// new_speech 在 Init_Pre_Process() 中被初始化，所以 get_new_speech() 必须在 Init_Pre_Process() 之后调用
// 	Word16 *new_speech=get_new_speech();
// 
// 	memcpy(new_speech, src, srcLen);
// #ifdef HARDW
// 	/* set 3 LSB's to zero */
// 	for(i=0; i < L_FRAME; i++) new_speech[i] = new_speech[i] & 0xFFF8;
// #endif
// 
// 	Pre_Process(new_speech, L_FRAME);
// 
// 	Coder_ld8k(prm, syn);
// 
// 	prm2bits_ld8k( prm, serial);
// 
// 	memcpy(dst, serial, dstLen);
// 
// 	return 0;
// }

// 编码
// 原长度必须是 160 的整数倍
int CG729AEncoder::encodeEx(char *src, unsigned int srcLen, char *dst)
{
	int count=srcLen / 160;
// 	char srcSlip[160];
// 	char dstSlip[10];
	for(int i=0;i<count;i++)
	{
// 		memcpy(srcSlip, src + i * 160, 160);
//		encode((char *)srcSlip, (char *)dstSlip);
		encode((char *)(src + i * 160), (char *)(dst + i * 10));
// 		memcpy(dst + i * 10, dstSlip, 10);

// 		Sleep(1);
	}

	return 0;
}

// 编码
// 原长度必须是 80 的整数倍
// int CG729AEncoder::encodeEx(char *src, unsigned int srcLen, char *dst)
// {
// 	int count=srcLen / 80;
// 	Word16 srcSlip[80];
// 	char dstSlip[10];
// 	for(int i=0;i<count;i++)
// 	{
// 		for(int j=0;j<80;j++)
// 			srcSlip[j]=src[i*80+j];
// 
// 		// 		memcpy(srcSlip, src + i * 160, 160);
// 		//		encode((char *)srcSlip, (char *)dstSlip);
// 		encode(srcSlip, (char *)dstSlip);
// 		memcpy(dst + i * 10, dstSlip, 10);
// 
// // 		Sleep(1);
// 	}
// 
// 	return 0;
// }
