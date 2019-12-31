#pragma once

#include "h264-ffmpeg\avcodec.h"

class CH264DecoderByFFMpeg
{
public:
	CH264DecoderByFFMpeg(void);
	~CH264DecoderByFFMpeg(void);

	BOOL initDecoder();
	void closeDecoder();

	// 解码
	// 返回值：0：失败，>0：成功
	int decode(BYTE *data, int dataLen);

	void getDecodedFrame(BYTE *y, BYTE *u, BYTE *v);

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

private:
	AVCodecContext *c;
	AVCodec *codec;
	AVFrame *picture;

	int m_width;
	int m_height;
};
