// BitmapProcess.h: interface for the CBitmapProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPPROCESS_H__F93A9E7C_8A0C_4A56_BE7C_1063B3206316__INCLUDED_)
#define AFX_BITMAPPROCESS_H__F93A9E7C_8A0C_4A56_BE7C_1063B3206316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBitmapProcess  
{
public:
	CBitmapProcess();
	virtual ~CBitmapProcess();

	// 彩色图像生成灰度图
	// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高x3），灰度图像数据（长度为宽x高）
	static int color2Gray(int width, int height, unsigned char *rgbData, unsigned char *greyData);
	static int color8bit2Gray(int width, int height, BITMAPINFO *info, unsigned char *rgbData, unsigned char *greyData);

	// 彩色图像二值化
	// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高x3），二值图像数据（长度为宽x高x3），二值化阈值
	// 二值化方法：rgb求和，再与阈值比较，<=则置0，否则置255
	static int colorBinaryzation(int width, int height, unsigned char *rgbData, unsigned char *binaryData, int threshold);
	
	// 八位彩色图像二值化
	// 即一个字节代表一个像素，颜色值由调色板决定
	// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高），二值图像数据（长度为宽x高），二值化阈值
	// 二值化方法：rgb求和，再与阈值比较，<=则置0，否则置255
	static int color8Binaryzation(int width, int height, BITMAPINFO *info, unsigned char *rgbData, unsigned char *binaryData, int threshold);
	static int color8Binaryzation(int width, int height, RGBQUAD *quad, unsigned char *rgbData, unsigned char *binaryData, int threshold);
	
	// 彩色图像二值化
	// 参数：图像宽度、图像高度、彩色RGB图像数据（长度为宽x高x3），二值图像数据（长度为宽x高），二值化阈值， 阈值应用于（0-R，1-G，2-B，其他-B）
	// 二值化方法：指定r、g或b值和相应的阈值比较，<=则置0，否则置255
	static int colorBinaryzation(int width, int height, unsigned char *rgbData, unsigned char *binaryData, unsigned char threshold, char appto);
	
	// 灰度图像二值化
	// 参数：图像宽度、图像高度、灰度图像数据（长度为宽x高），二值化阈值，二值图像数据（长度为宽x高）
	// 二值化方法：灰度值与阈值比较，<=则置0，否则置255
	static int greyBinaryzation(int width, int height, unsigned char *greyData, unsigned char threshold, unsigned char *binaryData);
};

#endif // !defined(AFX_BITMAPPROCESS_H__F93A9E7C_8A0C_4A56_BE7C_1063B3206316__INCLUDED_)
