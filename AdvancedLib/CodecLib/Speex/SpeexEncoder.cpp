#include "StdAfx.h"
#include "SpeexEncoder.h"

CSpeexEncoder::CSpeexEncoder(void)
{
}

CSpeexEncoder::~CSpeexEncoder(void)
{
}

BOOL CSpeexEncoder::init(int quality/*=8*/)
{
	/*Create a new encoder state in narrowband mode*/
	state = speex_encoder_init(&speex_nb_mode);

	/*Set the quality to 8 (15 kbps)*/
	int tmp=quality;
	if(tmp<0)
		tmp=8;

	int ret=speex_encoder_ctl(state, SPEEX_SET_QUALITY, &tmp);

	/*Initialization of the structure that holds the bits*/
	speex_bits_init(&bits);

	return TRUE;
}

BOOL CSpeexEncoder::encode( float *src, int length, char *dst, int *dstLen )
{
	/*Flush all the bits in the struct so we can encode a new frame*/
	speex_bits_reset(&bits);

	/*Encode the frame*/
	int ret=speex_encode(state, src, &bits);

	/*Copy the bits to an array of char that can be written*/
	int nbBytes = speex_bits_write(&bits, dst, 200);

	*dstLen=nbBytes;

	return TRUE;
}

void CSpeexEncoder::destroy()
{
	/*Destroy the encoder state*/
	speex_encoder_destroy(state);

	/*Destroy the bit-packing struct*/
	speex_bits_destroy(&bits);
}
