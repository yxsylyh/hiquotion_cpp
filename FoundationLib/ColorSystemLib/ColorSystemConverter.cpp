// YUVRGBConverter.cpp: implementation of the CYUVRGBConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColorSystemConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorSystemConverter::CColorSystemConverter()
{

}

CColorSystemConverter::~CColorSystemConverter()
{

}

BYTE CColorSystemConverter::Clip255( LONG v ) 
{ 
    if ( v < 0 ) v = 0; 
    else if( v > 255 ) v = 255; 
    return (BYTE)v; 
}

//YUV2转RGB24整型版算法,注意RGB缓冲区应是YUV2的1.5倍,可以通过(((m_lpbmi->bmiHeader.biWidth * m_lpbmi->bmiHeader.biBitCount + 31) >> 5 ) << 2) * m_lpbmi->bmiHeader.biHeight; 
//算出RGB图像大小 
void CColorSystemConverter::YUY2ToRGB( BYTE *YUY2buff, BYTE *RGBbuff, DWORD dwYUVSize) 
{ 
    // 
    //C = Y - 16 
    //D = U - 128 
    //E = V - 128 
    //R = clip(( 298 * C           + 409 * E + 128) >> 8) 
    //G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8) 
    //B = clip(( 298 * C + 516 * D           + 128) >> 8) 
    BYTE    *orgRGBbuff = RGBbuff; 
	
    for( DWORD count = 0; count < dwYUVSize; count += 4 ) 
    { 
        //Y0 U0 Y1 V0 
        BYTE Y0 = *YUY2buff; 
        BYTE U  = *(++YUY2buff); 
        BYTE Y1 = *(++YUY2buff); 
        BYTE V  = *(++YUY2buff); 
        ++YUY2buff; 
		
        LONG Y,C,D,E; 
        BYTE R,G,B; 
		
        Y = Y0; 
        C = Y-16; 
        D = U-128; 
        E = V-128; 
        R = Clip255(( 298 * C           + 409 * E + 128) >> 8); 
        G = Clip255(( 298 * C - 100 * D - 208 * E + 128) >> 8); 
        B = Clip255(( 298 * C + 516 * D           + 128) >> 8); 
		
        *(RGBbuff)     = B;            
        *(++RGBbuff) = G;    
        *(++RGBbuff) = R;          
		
        Y = Y1; 
        C = Y-16; 
        D = U-128; 
        E = V-128; 
        R = Clip255(( 298 * C           + 409 * E + 128) >> 8); 
        G = Clip255(( 298 * C - 100 * D - 208 * E + 128) >> 8); 
        B = Clip255(( 298 * C + 516 * D           + 128) >> 8); 
        *(++RGBbuff) =   B;            
        *(++RGBbuff) = G;    
        *(++RGBbuff) = R;          
        ++RGBbuff; 
		
// 		Sleep(1);
    } 
}

// BMP 图像垂直翻转
void CColorSystemConverter::Vertical(BYTE *src, int width, int height, BYTE *dst)
{
	for(int i=0;i<height;i++)
	{
		memcpy(dst+(height-1-i)*width*3, src+i*width*3, width*3);
// 		Sleep(1);
	}
}

// void ColorSystemConverter::RGBToYUV420InitTable()
// {
// 	int i;
// 	
// 	for (i = 0; i < 256; i++) RGB2YUV_YR[i] = (float)65.481 * (i<<8);
// 	for (i = 0; i < 256; i++) RGB2YUV_YG[i] = (float)128.553 * (i<<8);
// 	for (i = 0; i < 256; i++) RGB2YUV_YB[i] = (float)24.966 * (i<<8);
// 	for (i = 0; i < 256; i++) RGB2YUV_UR[i] = (float)37.797 * (i<<8);
// 	for (i = 0; i < 256; i++) RGB2YUV_UG[i] = (float)74.203 * (i<<8);
// 	for (i = 0; i < 256; i++) RGB2YUV_VG[i] = (float)93.786 * (i<<8);
// 	for (i = 0; i < 256; i++) RGB2YUV_VB[i] = (float)18.214 * (i<<8);
// 	for (i = 0; i < 256; i++) RGB2YUV_UBVR[i] = (float)112 * (i<<8);
// 
// }

// YUV2 to YUV420Planar Planar是平面格式，H.264编码库需要使用 YUV420 平面格式
void CColorSystemConverter::YUV2ToYUV420Planar(BYTE *yuv2, int width, int height, BYTE *yuv420planar)
{
	// 存储空间

	// RGB = W x H x 3
	// YUV2(YUV422) = W x H x 2
	// YUV420 = W x H x 3 / 2

	// YUV420 len = YUV2 len x 3 / 4


	// Y00 U00 Y01 V00 Y02 U01 Y03 V01 ...
	// Y10 U10 Y11 V10 Y12 U11 Y13 V11 ...

	// converted to

	// Y00 Y01 Y02 Y03 ... Y10 Y11 Y12 Y13 ... (U00+U10)/2 (U01+U11)/2 ... (V00+V10)/2 (V01+V11)/2 ...

	BYTE *y=yuv420planar;
	BYTE *u=yuv420planar + width * height;
	BYTE *v=u + width * height / 4;

	int i=0,j=0;
	for(i=0;i<width * height;i++)
	{
		y[i]=yuv2[2*i];
// 		Sleep(1);
	}

	for(j=0;j<height/2;j++)
		for(i=0;i<width;i++)
		{
			if (i % 2 == 0)
			{
				//存u分量
				u[j*width/2+i/2] =(yuv2[2*j*width*2+2*i+1]+yuv2[(2*j+1)*width*2+2*i+1])/2;
// 				u[j*width/2+i/2] =yuv2[2*j*width*2+2*i+1];
// 				u[j*width/2+i/2] =yuv2[(2*j+1)*width*2+2*i+1];
				//存v分量
				v[j*width/2+i/2] =(yuv2[2*j*width*2+2*i+3]+yuv2[(2*j+1)*width*2+2*i+3])/2;
// 				v[j*width/2+i/2] =yuv2[2*j*width*2+2*i+3];
// 				v[j*width/2+i/2] =yuv2[(2*j+1)*width*2+2*i+3];
			}
// 			Sleep(1);
		}
}

// YUV420Planar to RGB
void CColorSystemConverter::YUV420PlanarToRGB(BYTE *yuv420planar, int width, int height, BYTE *rgb)
{
	// 存储空间

	// RGB = W x H x 3
	// YUV2(YUV422) = W x H x 2
	// YUV420 = W x H x 3 / 2


	int uIndex = width * height;
	int vIndex = uIndex + ((width * height) >> 2);
// 	int gIndex = width * height;
// 	int bIndex = gIndex * 2;

	YUV420ToRGB(yuv420planar, yuv420planar+uIndex, yuv420planar+vIndex, width, height, rgb);

// 	int temp = 0;
// 
// 	for (int y = 0; y < height; y++)
// 	{
// 		for (int x = 0; x < width; x++)
// 		{
// 			// R分量
// 			temp = (int)(yuv420planar[y * width + x] + (yuv420planar[vIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[0][2]);
// 			rgb[y * width * 3 + x * 3 + 2] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
// 
// 			// G分量
// 			temp = (int)(yuv420planar[y * width + x] + (yuv420planar[uIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[1][1] + (yuv420planar[vIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[1][2]);
// // 			rgb[gIndex + y * width + x] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
// 			rgb[y * width * 3 + x * 3 + 1] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
// 
// 			// B分量
// 			temp = (int)(yuv420planar[y * width + x] + (yuv420planar[uIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[2][1]);
// // 			rgb[bIndex + y * width + x] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
// 			rgb[y * width * 3 + x * 3] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
// 		}
// 	}

}

// YUV420分量 to RGB
void CColorSystemConverter::YUV420ToRGB(BYTE *y,BYTE *u, BYTE *v, int width, int height, BYTE *rgb)
{
	int temp = 0;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			// R分量
			temp = (int)(y[j * width + i] + (v[(j / 2) * (width / 2) + i / 2] - 128) * YUV2RGB_CONVERT_MATRIX[0][2]);
			rgb[j * width * 3 + i * 3 + 2] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));

			// G分量
			temp = (int)(y[j * width + i] + (u[(j / 2) * (width / 2) + i / 2] - 128) * YUV2RGB_CONVERT_MATRIX[1][1] + (v[(j / 2) * (width / 2) + i / 2] - 128) * YUV2RGB_CONVERT_MATRIX[1][2]);
// 			rgb[gIndex + y * width + x] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
			rgb[j * width * 3 + i * 3 + 1] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));

			// B分量
			temp = (int)(y[j * width + i] + (u[(j / 2) * (width / 2) + i / 2] - 128) * YUV2RGB_CONVERT_MATRIX[2][1] + (v[(j / 2) * (width / 2) + i / 2] - 128) * YUV2RGB_CONVERT_MATRIX[2][2]);
// 			rgb[bIndex + y * width + x] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
			rgb[j * width * 3 + i * 3] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));

// 			Sleep(1);
		}
	}

}

// RGB to YUV420Planar
void CColorSystemConverter::RGBToYUV420Planar(BYTE *rgb, int width, int height, BYTE *yuv420planar)
{
	// 存储空间

	// RGB = W x H x 3
	// YUV2(YUV422) = W x H x 2
	// YUV420 = W x H x 3 / 2

	int i, j;  
	unsigned char*bufY, *bufU, *bufV, *bufRGB;//,*bufYuv;  
	bufY = yuv420planar;  
	bufV = yuv420planar + width * height;  
	bufU = bufV + (width * height* 1/4);  
	unsigned char y, u, v, r, g, b;//,testu,testv;  
	unsigned int ylen = width * height;  
	unsigned int ulen = (width * height)/4;  
	unsigned int vlen = (width * height)/4;   
	for (j = 0; j<height;j++)  
	{  
		bufRGB = rgb + width * j * 3; // width * (height - 1 - j) * 3 ;  
		for (i = 0;i<width;i++)  
		{  
			r = *(bufRGB++);  
			g = *(bufRGB++);  
			b = *(bufRGB++);  
			y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;            
			u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;            
			v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;  
			*(bufY++) = max( 0, min(y, 255 ));  
			if (j%2==0&&i%2 ==0)  
			{  
				if (u>255)  
				{  
					u=255;  
				}  
				if (u<0)  
				{  
					u = 0;  
				}  
				*(bufU++) =u;  
				//存u分量   
// 				*(bufV++) =v;  
			}  
			else  
			{  
				//存v分量   
				if (i%2==0)  
				{  
					if (v>255)  
					{  
						v = 255;  
					}  
					if (v<0)  
					{  
						v = 0;  
					}  
					*(bufV++) =v;  
				}  
			}  

// 			Sleep(1);
		}  
	}  
}
