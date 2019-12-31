#include "stdafx.h"
#include "G729ADecoder.h"

CG729ADecoder::CG729ADecoder(void)
{
	srcLen=SERIAL_SIZE;  //*sizeof(Word16);
	dstLen=L_FRAME*sizeof(Word16);
	init();
}

CG729ADecoder::~CG729ADecoder(void)
{
}

void CG729ADecoder::init()
{
	/*-----------------------------------------------------------------*
	*           Initialization of decoder                             *
	*-----------------------------------------------------------------*/

	for (i=0; i<M; i++) synth_buf[i] = 0;
	synth = synth_buf + M;

	Init_Decod_ld8k();
	Init_Post_Filter();
	Init_Post_Process();
	voicing = 60;

}

// src长度和dst长度都是固定的
// 库以 Word16（32位下应该是 2 字节，64位下为 4 字节） 为长度单位处理数据
// src长度 = SERIAL_SIZE（库中定义为是80） × sizeof(Word16) = 160（32位下）或 320（64位下）
// dst长度 = L_FRAME（库中定义为是80+2） × sizeof(Word16) = 164（32位下）或 328（64位下）
int CG729ADecoder::decode(char *src, char *dst)
{
	if(!src || !dst)
		return -1;

// 	memcpy(serial, src, srcLen);

// 	bits2prm_ld8k( &serial[2], &parm[1]);
// 	bits2prm_ld8k( serial, &parm[1]);
	bits2prm_ld8k( (unsigned char *)src, &parm[1]);

// 	/* the hardware detects frame erasures by checking if all bits
// 	are set to zero
// 	*/
// 	parm[0] = 0;           /* No frame erasure */
// 	for (i=2; i < SERIAL_SIZE; i++)
// 		if (serial[i] == 0 ) parm[0] = 1; /* frame erased     */
// 
// 	/* check parity and put 1 in parm[4] if parity error */
// 
// 	parm[4] = Check_Parity_Pitch(parm[3], parm[4]);

	parm[0] = 0;  /* 假设没有丢帧 */
	parm[4] = 0 ; /* 假设数据效验正常 */

	Decod_ld8k(parm, voicing, synth, Az_dec, &T0_first);

	/* Postfilter */

	voicing = 0;
	ptr_Az = Az_dec;
	for(i=0; i<L_FRAME; i+=L_SUBFR) {
		Post(T0_first, &synth[i], ptr_Az, &pst_out[i], &sf_voic);
		if (sf_voic != 0) { voicing = sf_voic;}
		ptr_Az += MP1;
	}
	Copy(&synth_buf[L_FRAME], &synth_buf[0], M);

	Post_Process(pst_out, L_FRAME);

#ifdef HARDW
	{
		Word16 *my_pt;
		Word16 my_temp;
		int my_i;
		my_pt = pst_out;
		for(my_i=0; my_i < L_FRAME; my_i++) {
			my_temp = *my_pt;
			my_temp = add( my_temp, (Word16) 4); /* rounding on 13 bit */
			my_temp = my_temp & 0xFFF8; /* mask on 13 bit */
			*my_pt++ = my_temp;
		}
	}
#endif

	memcpy(dst, pst_out, dstLen);

	return 0;
}

// 解码
// 原长度必须是 10 的整数倍
int CG729ADecoder::decodeEx(char *src, unsigned int srcLen, char *dst)
{
	int count=srcLen / 10;
// 	char srcSlip[10];
// 	char dstSlip[160];
	for(int i=0;i<count;i++)
	{
// 		memcpy(srcSlip, src + i * 10, 10);
		decode((char *)(src + i * 10), (char *)(dst + i * 160));
// 		memcpy(dst + i * 160, dstSlip, 160);

// 		Sleep(1);
	}

	return 0;
}
