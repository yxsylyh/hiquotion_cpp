#ifndef H264_H
#define H264_H

#include "avcodec.h"

extern "C" {
void Close_Decode_frame( unsigned char *Buf, AVCodecContext *c, AVFrame *picture );
}
#endif