// BitmapOperation.h: interface for the CBitmapOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPOPERATION_H__D89F2A11_AF59_4616_85CA_2BD57300B00C__INCLUDED_)
#define AFX_BITMAPOPERATION_H__D89F2A11_AF59_4616_85CA_2BD57300B00C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBitmapOperation  
{
public:
	CBitmapOperation();
	virtual ~CBitmapOperation();

	static BOOL loadBmp(CString path);
	static void showFromFile(CDC *pDC, CRect &rect);
	static void showFromBuffer(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight, int imgLeft, int imgTop, int imgWidth, int imgHeight, unsigned char *buffer, BITMAPINFO *bmpInfo);
	static void showFromBuffer(CDC* pDC,CRect &rect, int imgLeft, int imgTop, int imgWidth, int imgHeight, unsigned char *buffer, BITMAPINFO *bmpInfo);
	static int GetColorNumber(WORD iBitCount);

	// 生成BMP Info，忽略调色板
	static void getBmpInfo(int width, int height, int bitCount, BITMAPINFO *bmpInfo);
	static BOOL saveBmp(CString path, BITMAPINFOHEADER header, RGBQUAD *quad, unsigned char *data, int dataLen);
};

#endif // !defined(AFX_BITMAPOPERATION_H__D89F2A11_AF59_4616_85CA_2BD57300B00C__INCLUDED_)
