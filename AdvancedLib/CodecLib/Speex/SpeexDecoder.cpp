#include "StdAfx.h"
#include "SpeexDecoder.h"

CSpeexDecoder::CSpeexDecoder(void)
{
}

CSpeexDecoder::~CSpeexDecoder(void)
{
}

BOOL CSpeexDecoder::init(int quality/*=8*/)
{
	/*Create a new decoder state in narrowband mode*/
	state = speex_decoder_init(&speex_nb_mode);

	/*Set the perceptual enhancement on*/
	int tmp=quality;
	if(tmp<0)
		tmp=1;

	int ret=speex_decoder_ctl(state, SPEEX_SET_ENH, &tmp);

	/*Initialization of the structure that holds the bits*/
	speex_bits_init(&bits);

	return TRUE;
}

BOOL CSpeexDecoder::decode( char *src, int srcLen, float *dst, int *dstLen )
{
	/*Copy the data into the bit-stream struct*/
	speex_bits_read_from(&bits, src, srcLen);

	/*Decode the data*/
	float output[200];
	m_errMsg="";
	// 0 for no error, -1 for end of stream, -2 corrupt stream
//	int ret=speex_decode(state, &bits, output);
	int ret=speex_decode(state, &bits, dst);
	if(ret!=0)
	{
		if(ret==-1)
			m_errMsg="已到音频数据流的结尾";
		else if(ret==-2)
			m_errMsg="损坏的音频数据流";

		return FALSE;
	}

	/*Copy from float to short (16 bits) for output*/
// 	for (int i=0;i<FRAME_SIZE;i++)
// 		dst[i]=output[i];

	*dstLen=FRAME_SIZE/sizeof(float);

	return TRUE;
}

void CSpeexDecoder::destroy()
{
	/*Destroy the decoder state*/
	speex_decoder_destroy(state);

	/*Destroy the bit-stream truct*/
	speex_bits_destroy(&bits);
}
