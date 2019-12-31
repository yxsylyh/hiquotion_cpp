#include "stdafx.h"
#include "H264EncoderByX264.h"

CH264EncoderByX264::CH264EncoderByX264(void)
: m_encoder_t(NULL)
{
	pic.img.plane[0]=NULL;
	pic.img.plane[1]=NULL;
	pic.img.plane[2]=NULL;
	pic.img.plane[3]=NULL;
}

CH264EncoderByX264::~CH264EncoderByX264(void)
{
}

BOOL CH264EncoderByX264::initEncoder(int width, int height)
{
	m_width=width;
	m_height=height;

// 	closeEncoder();
	x264_param_default(&m_param);//设置默认参数具体见common/common.c
	m_param.i_width=m_width;
	m_param.i_height=m_height;
	m_param.i_log_level = X264_LOG_NONE;
	m_param.analyse.b_psnr = 0;
	m_param.b_visualize = 0;  // 估计是转换的时候的一种可视化，这里取0了

	m_encoder_t=x264_encoder_open(&m_param);
	if(!m_encoder_t)
	{
// 		fprintf( stderr, "x264 [error]: x264_encoder_open failed\n" );
		return FALSE;
	}

	/* Create a new pic */
	x264_picture_alloc( &pic, X264_CSP_I420, m_param.i_width, m_param.i_height );

	if(m_encoder_t)
		m_isOpen=TRUE;
	else
		m_isOpen=FALSE;

	return m_isOpen;
}

void CH264EncoderByX264::closeEncoder()
{
	x264_picture_clean( &pic );

	if(m_encoder_t)
	{
		x264_encoder_close( m_encoder_t );
		m_encoder_t=NULL;
	}
}

// void CH264EncoderByX264::setParameter(int width, int height, int bitrate, float framerate, int aspect_ratio, int video_format)
// {
// 	if(width<=0 || height<=0)
// 		return;
// 
// 	m_width=width;
// 	m_height=height;
// 
// 	// 	m_size = m_param.height * m_param.width + (m_param.height * m_param.width >> 1);
// 	m_size = m_height * m_width + (m_height * m_width >> 1);
// 	if(m_dst)
// 		T264_free(m_dst);
// 	m_dst = (unsigned char*)T264_malloc(m_size, CACHE_SIZE);
// 
// 	m_bitrate=bitrate;
// 	m_framerate=framerate;
// 	m_aspect_ratio=aspect_ratio;
// 	m_video_format=video_format;
// }

BOOL CH264EncoderByX264::encode(BYTE *yuvSrc, BYTE *dst, int *dstLen)
{
	if(!m_isOpen)
	{
		*dstLen=0;
		return FALSE;
	}

	pic.i_type = X264_TYPE_AUTO;
	pic.i_qpplus1 = 0;
	pic.img.plane[0]=yuvSrc;
	pic.img.plane[1]=yuvSrc+m_param.i_width*m_param.i_height;
	pic.img.plane[2]=yuvSrc+m_param.i_width*m_param.i_height+m_param.i_width*m_param.i_height/4;
	x264_nal_t *nal;
	int i_nal=0;
	int ret=x264_encoder_encode(m_encoder_t, &nal, &i_nal, &pic, &m_picout);

	if(ret<0)
	{
		*dstLen=0;
		return FALSE;
	}

	int sizeSum=0;
	for( int i = 0; i < i_nal; i++ )
	{
		int i_size;
		int i_data;

		i_data = DATA_MAX;
		if( ( i_size = x264_nal_encode( data, &i_data, 1, &nal[i] ) ) > 0 )
		{
//			i_file += p_write_nalu( hout, data, i_size );
			memcpy(dst+sizeSum, data, i_data);
			sizeSum+=i_data;
		}
// 		else if( i_size < 0 )
// 		{
// 			fprintf( stderr, "x264 [error]: need to increase buffer size (size=%d)\n", -i_size );
// 		}
	}

	*dstLen=sizeSum;
	return TRUE;
}

