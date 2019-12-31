// BitmapProcess.cpp: implementation of the CBitmapProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BitmapProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitmapProcess::CBitmapProcess()
{

}

CBitmapProcess::~CBitmapProcess()
{

}

// 彩色图像生成灰度图
// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高x3），灰度图像数据（长度为宽x高）
int CBitmapProcess::color2Gray(int width, int height, unsigned char *rgbData, unsigned char *greyData)
{
	if(width<=0 || height <=0 || !rgbData || !greyData)
		return -1;
	
	// 灰度值=0.3R+0.59G+0.11B
	for(int i=0;i<width*height;i++)
	{
		unsigned char b=rgbData[3*i];
		unsigned char g=rgbData[3*i+1];
		unsigned char r=rgbData[3*i+2];
		
		greyData[i]=(unsigned char)(0.3*r+0.59*g+0.11*b);
	}
	
	return 0;
}

int CBitmapProcess::color8bit2Gray(int width, int height, BITMAPINFO *info, unsigned char *rgbData, unsigned char *greyData)
{
	if(width<=0 || height <=0 || !info || !rgbData || !greyData)
		return -1;
	
	// 灰度值=0.3R+0.59G+0.11B
	for(int i=0;i<width*height;i++)
	{
		unsigned char r=info->bmiColors[rgbData[i]].rgbRed;
		unsigned char g=info->bmiColors[rgbData[i]].rgbGreen;
		unsigned char b=info->bmiColors[rgbData[i]].rgbBlue;
		
		int grey=(unsigned char)(0.3*r+0.59*g+0.11*b);

		info->bmiColors[rgbData[i]].rgbRed=grey;
		info->bmiColors[rgbData[i]].rgbGreen=grey;
		info->bmiColors[rgbData[i]].rgbBlue=grey;
// 		greyData[i]=grey;
	}

	return 0;
}

// 彩色图像二值化
// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高x3），二值图像数据（长度为宽x高x3），二值化阈值
// 二值化方法：rgb求和，再与阈值比较，<=则置0，否则置255
int CBitmapProcess::colorBinaryzation(int width, int height, unsigned char *rgbData, unsigned char *binaryData, int threshold)
{
	if(width<=0 || height <=0 || !rgbData || !binaryData)
		return -1;

	// 灰度值=0.3R+0.59G+0.11B
	for(int i=0;i<width*height;i++)
	{
		unsigned char r=rgbData[3*i];
		unsigned char g=rgbData[3*i+1];
		unsigned char b=rgbData[3*i+2];
		
		unsigned char result=0;
		if(r+g+b<=threshold)
			result=0;
		else
			result=255;

		binaryData[3*i]=result;
		binaryData[3*i+1]=result;
		binaryData[3*i+2]=result;
	}
	
	return 0;
}

// 彩色图像二值化
// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高x3），二值图像数据（长度为宽x高），二值化阈值， 阈值应用于（0-R，1-G，2-B，其他-B）
// 二值化方法：指定r、g或b值和相应的阈值比较，<=则置0，否则置255
int CBitmapProcess::colorBinaryzation(int width, int height, unsigned char *rgbData, unsigned char *binaryData, unsigned char threshold, char appto)
{
	if(width<=0 || height <=0 || !rgbData || !binaryData)
		return -1;
	
	int v=appto;
	if(v<0 || v>2)
		v=2;

	for(int i=0;i<width*height;i++)
	{
		if(rgbData[3*i+v]<=threshold)
			binaryData[i]=0;
		else
			binaryData[i]=255;
	}

	return 0;
}

// 八位彩色图像二值化
// 即一个字节代表一个像素，颜色值由调色板决定
// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高），二值图像数据（长度为宽x高），二值化阈值
// 二值化方法：rgb求和，再与阈值比较，<=则置0，否则置255
int CBitmapProcess::color8Binaryzation(int width, int height, BITMAPINFO *info, unsigned char *rgbData, unsigned char *binaryData, int threshold)
{
	if(width<=0 || height <=0 || !info || !rgbData || !binaryData || threshold==0)
		return -1;

	for(int i=0;i<width*height;i++)
	{
		unsigned char r=info->bmiColors[rgbData[i]].rgbRed;
		unsigned char g=info->bmiColors[rgbData[i]].rgbGreen;
		unsigned char b=info->bmiColors[rgbData[i]].rgbBlue;

		unsigned char grey=(unsigned char)(0.3*r+0.59*g+0.11*b);

		if(grey<=threshold)
			binaryData[i]=0;
		else
			binaryData[i]=255;
	}

	return 0;
}

int CBitmapProcess::color8Binaryzation(int width, int height, RGBQUAD *quad, unsigned char *rgbData, unsigned char *binaryData, int threshold)
{
	if(width<=0 || height <=0 || !quad || !rgbData || !binaryData || threshold==0)
		return -1;
	
	for(int i=0;i<width*height;i++)
	{
		unsigned char index=rgbData[i];
		unsigned char r=quad[rgbData[i]].rgbRed;
		unsigned char g=quad[rgbData[i]].rgbGreen;
		unsigned char b=quad[rgbData[i]].rgbBlue;

		if(r!=g || g!=b)
		{
			MessageBox(0,"","",0);
		}
		
		unsigned char grey=(unsigned char)(0.3*r+0.59*g+0.11*b);
		
		if(grey<=threshold)
			binaryData[i]=0;
		else
			binaryData[i]=255;
	}
	
	return 0;
}

// 灰度图像二值化
// 参数：图像宽度、图像高度、灰度图像数据（长度为宽x高），二值化阈值，二值图像数据（长度为宽x高）
// 二值化方法：灰度值与阈值比较，<=则置0，否则置255
int CBitmapProcess::greyBinaryzation(int width, int height, unsigned char *greyData, unsigned char threshold, unsigned char *binaryData)
{
	if(width<=0 || height <=0 || !greyData || !binaryData)
		return -1;
	
	for(int i=0;i<width*height;i++)
	{
		if(greyData[i]<=threshold)
			binaryData[i]=0;
		else
			binaryData[i]=255;
	}
	
	return 0;
}
