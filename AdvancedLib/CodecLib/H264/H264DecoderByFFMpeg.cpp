#include "StdAfx.h"
#include "H264DecoderByFFMpeg.h"

CH264DecoderByFFMpeg::CH264DecoderByFFMpeg(void)
: c(NULL), codec(NULL), picture(NULL), m_width(0), m_height(0)
{
}

CH264DecoderByFFMpeg::~CH264DecoderByFFMpeg(void)
{
}

BOOL CH264DecoderByFFMpeg::initDecoder()
{
	avcodec_init(); 
	avcodec_register_all(); 
	codec = avcodec_find_decoder(CODEC_ID_H264);

	if (!codec)  {
// 		AppendLog( "codec failed" );
		return FALSE; 
	} 
	//allocate codec context
	c = avcodec_alloc_context(); 

	if(!c){
// 		AppendLog( "avcodec_alloc_context failed" );
		return FALSE;
	}
	//open codec
	if (avcodec_open(c, codec) < 0) {
// 		AppendLog( "avcodec_open failed" );
		return FALSE; 
	} 

// 	c->width=width;
// 	c->height=height;

	//allocate frame buffer
	picture   = avcodec_alloc_frame();
	if(!picture){
// 		AppendLog( "avcodec_alloc_frame failed" );
		return FALSE;
	}

	return TRUE;

}

void CH264DecoderByFFMpeg::closeDecoder()
{
	if(c) {
		avcodec_close(c); 
		av_free(c);
		c = NULL;
	} 
	if(picture) {
		
		av_free(picture);
		picture = NULL;
	}

	m_width=0;
	m_height=0;
}

// 解码
// 返回值：0：失败，>0：成功
int CH264DecoderByFFMpeg::decode(BYTE *data, int dataLen)
{
	int got_picture;
	int ret=avcodec_decode_video(c, picture, &got_picture, data, dataLen);
	if(ret<=0)
		return ret;

	m_width=c->width;
	m_height=c->height;

	return ret;
}

void CH264DecoderByFFMpeg::getDecodedFrame(BYTE *y, BYTE *u, BYTE *v)
{
	int i=0;
	for(i=0; i<c->height; i++)
	{
		//			fwrite(picture->data[0] + i * picture->linesize[0], 1, c->width, outf);
		memcpy(y + i * c->width, picture->data[0] + i * picture->linesize[0], c->width);
// 		memcpy(y + i * c->width, picture->data[0] + i * c->width, c->width);
	}
// 	memcpy(y, picture->data[0], width*height);
	for(i=0; i<c->height/2; i++)
	{
		//			fwrite(picture->data[1] + i * picture->linesize[1], 1, c->width/2, outf);
		memcpy(u + i * c->width/2, picture->data[1] + i * picture->linesize[1], c->width/2);
// 		memcpy(u + i * c->width/2, picture->data[1] + i * c->width/2, c->width/2);
	}
// 	memcpy(u, picture->data[1], width*height/2);
	for(i=0; i<c->height/2; i++)
	{
		//			fwrite(picture->data[2] + i * picture->linesize[2], 1, c->width/2, outf);
		memcpy(v + i * c->width/2, picture->data[2] + i * picture->linesize[2], c->width/2);
// 		memcpy(v + i * c->width/2, picture->data[2] + i * c->width/2, c->width/2);
	}
// 	memcpy(v, picture->data[2], width*height/2);
}
