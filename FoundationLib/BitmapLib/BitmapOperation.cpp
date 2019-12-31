// BitmapOperation.cpp: implementation of the CBitmapOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BitmapOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static HBITMAP m_hBmpFromFile=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitmapOperation::CBitmapOperation()
{

}

CBitmapOperation::~CBitmapOperation()
{

}

BOOL CBitmapOperation::loadBmp(CString path)
{
	m_hBmpFromFile=(HBITMAP)LoadImage(NULL,path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!m_hBmpFromFile)
		return FALSE;
	
	return TRUE;
}

void CBitmapOperation::showFromFile(CDC *pDC, CRect &rect)
{
	if(!pDC)
		return;
	
	if(!m_hBmpFromFile)
		return;
	
	CDC memDC;
	CBitmap bmp,*pOldBmp;
	
	bmp.Attach(m_hBmpFromFile);
	memDC.CreateCompatibleDC(pDC);
	pOldBmp=memDC.SelectObject(&bmp);
	
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);
	
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	
	bmp.Detach();
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
}

void CBitmapOperation::showFromBuffer(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight, int imgLeft, int imgTop, int imgWidth, int imgHeight, unsigned char *buffer, BITMAPINFO *bmpInfo)
{
	if(!pDC)
		return;

	if(!pDC->GetSafeHdc())
		return;

	// 设置拉伸模式，返回0则失败
	if(pDC->SetStretchBltMode(COLORONCOLOR)==0)
		return;

	StretchDIBits(pDC->GetSafeHdc(),//向下移动
		nLeft, nTop, nWidth, nHeight,
		0, 0, imgWidth, imgHeight,
		buffer, bmpInfo,
		DIB_RGB_COLORS,SRCCOPY);

}

void CBitmapOperation::showFromBuffer(CDC* pDC,CRect &rect, int imgLeft, int imgTop, int imgWidth, int imgHeight, unsigned char *buffer, BITMAPINFO *bmpInfo)
{
	showFromBuffer(pDC, rect.left, rect.top, rect.Width(), rect.Height(), imgLeft, imgTop, imgWidth, imgHeight, buffer, bmpInfo);
}

void CBitmapOperation::getBmpInfo(int width, int height, int bitCount, BITMAPINFO *bmpInfo)
{
	if(!bmpInfo)
		return;

	//判断位图的位数
	if(bitCount<=1)
		bitCount=1;
	else if(bitCount<=4)
		bitCount=4;
	else if(bitCount<=8)
		bitCount=8;
	else if (bitCount<=16)
		bitCount=16;
	else if (bitCount<=24)
		bitCount=24;
	else if(bitCount<=32)
		bitCount=32;
	else
		bitCount=4;

	bmpInfo->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpInfo->bmiHeader.biClrUsed=GetColorNumber(bitCount);
	bmpInfo->bmiHeader.biBitCount=bitCount;
	bmpInfo->bmiHeader.biPlanes=1;
	bmpInfo->bmiHeader.biCompression=0;
	bmpInfo->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpInfo->bmiHeader.biWidth=width;
	bmpInfo->bmiHeader.biHeight=height;
	bmpInfo->bmiHeader.biSizeImage=0;

	bmpInfo->bmiColors[0].rgbBlue=255;
	bmpInfo->bmiColors[0].rgbGreen=255;
	bmpInfo->bmiColors[0].rgbRed=255;
	bmpInfo->bmiColors[0].rgbReserved=0;

}

int CBitmapOperation::GetColorNumber(WORD iBitCount)
{
	//判断位图的位数
	if(iBitCount<=1)
		iBitCount=1;
	else if(iBitCount<=4)
		iBitCount=4;
	else if(iBitCount<=8)
		iBitCount=8;
	else if (iBitCount<=16)
		iBitCount=16;
	else if (iBitCount<=24)
		iBitCount=24;
	else if(iBitCount<=32)
		iBitCount=32;
	else
		iBitCount=4;

	switch(iBitCount)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		return 0;
	}
}

// void CBitmapOperation::genBmpBuffer(BITMAPINFOHEADER header, RGBQUAD *quad, unsigned char *data, int dataLen, char *bmp, int *bmpLen)
// {
// 	if(!data)
// 		return;
// 
// 	if(dataLen<=0)
// 		return;
// 
// 	BITMAPFILEHEADER head;
// 	head.bfType=0x4D42;
// 	head.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+header.biClrUsed*sizeof(RGBQUAD)+dataLen;
// 	head.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+header.biClrUsed*sizeof(RGBQUAD);
// 	head.bfReserved1=0;
// 	head.bfReserved2=0;
// 
// 	char *bmpBuffer=new char[head.bfSize];
// 	int len=0;
// 
// 	memcpy(bmpBuffer, &head, sizeof(BITMAPFILEHEADER));
// 	len=sizeof(BITMAPFILEHEADER);
// 	memcpy(bmpBuffer+len, &header, sizeof(BITMAPINFOHEADER));
// 	len+=sizeof(BITMAPINFOHEADER);
// 	for(int i=0;i<(int)header.biClrUsed;i++)
// 	{
// 		memcpy(bmpBuffer+len,&quad[i],sizeof(RGBQUAD));
// 		len+=sizeof(RGBQUAD);
// 	}
// 	memcpy(bmpBuffer, data, dataLen);
// 	len+=dataLen;
// 
// 	bmp=bmpBuffer;
// 	*bmpLen=len;
// }

BOOL CBitmapOperation::saveBmp(CString path, BITMAPINFOHEADER header, RGBQUAD *quad, unsigned char *data, int dataLen)
{
	if(path=="")
		return FALSE;

	if(!data)
		return FALSE;

	if(dataLen<=0)
		return FALSE;
	
	BITMAPFILEHEADER head;
	head.bfType=0x4D42;
	head.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+header.biClrUsed*sizeof(RGBQUAD)+dataLen;
	head.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+header.biClrUsed*sizeof(RGBQUAD);
	head.bfReserved1=0;
	head.bfReserved2=0;
	
	CFile img;
	if(!img.Open(path, OF_DELETE | OF_CREATE | CFile::modeWrite | CFile::shareDenyWrite))
		return FALSE;
	
	img.Write(&head, sizeof(BITMAPFILEHEADER));
	img.Write(&header, sizeof(BITMAPINFOHEADER));
	for(int i=0;i<(int)header.biClrUsed;i++)
		img.Write(&quad[i],sizeof(RGBQUAD));
	img.Write(data, dataLen);
	
	img.Close();
	
	return TRUE;

}
