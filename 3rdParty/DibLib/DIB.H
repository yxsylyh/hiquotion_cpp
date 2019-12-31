// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__C25C4C35_9ECD_11D4_B71C_0000B48A052A__INCLUDED_)
#define AFX_DIB_H__C25C4C35_9ECD_11D4_B71C_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDib : public CGdiObject  
{
	DECLARE_DYNAMIC(CDib)

/*数据成员*/
public:
	BITMAPINFO* m_pBMI;
	BYTE* m_pDIBData;

/*构造函数、析构函数*/
public:
	CDib();
	virtual ~CDib();

/*成员函数*/
public://创建位图
	static CDib* PASCAL FromHandle(HBITMAP hBitmap);//由句柄创建位图
	BOOL CreateDIB(int nWidth, int nHeight, UINT nBitcount, const void* lpBits=NULL);
	int CreateDIBIndirect(LPBITMAPINFO pBMI, const void* lpBits);
public://设置图像数据, 得到图像数据
	DWORD SetDIBBits(DWORD dwCount, const void* lpBits);
	LPVOID GetDIBBits(DWORD dwCount = 0, LPVOID lpBits = NULL);

public://得到使用的颜色数
//	int GetColorUsed();
	int GetColorNumber(WORD iBitCount);
public://读入位图,保存位图
	int LoadBmp(LPCSTR filename);
	int SaveBmp(LPCSTR filename);

public://获取和设置调色板
	int GetPalette(UINT uStartIndex, UINT cEntries, RGBQUAD *pColors);
	void SetPalette(UINT uStartIndex, UINT cEntries, CONST RGBQUAD *pColors);
	void SetPalette(CPalette* pPal);

public://得到设备,释放设备
	CDC* GetDC(void);
	static BOOL ReleaseDC(CDC *pdc);

public://得到位图, 得到DibSection
	int GetBitmap(BITMAP* pBitMap);
	int GetDibSection(DIBSECTION* pDibSection);
	
public://得到宽度,高度,尺寸
	int GetWidth();
	int GetHeight();
	SIZE GetSize();

public://得到每行图像字节数,得到图像位数,得到图像数据,得到图像信息头
	int GetWidthBytes();
	int GetBitCount();
	LPVOID GetBits();
	LPBITMAPINFO GetBitmapInfo(void);

public:	//得到位图, 拷贝位图
	operator HBITMAP() const;
	CDib& operator = (CDib& copy);
	void ShowDIB(CDC* pDC,int nLeft,int nTop,int nWidth, int nHeight);
	void ShowDIB(CDC* pDC,CRect &rect);
	int GetDIBWidth(){return m_pBMI->bmiHeader.biWidth;}
	int GetDIBHeight(){return m_pBMI->bmiHeader.biHeight;}
	void Wait(double time);
};

#endif // !defined(AFX_DIB_H__C25C4C35_9ECD_11D4_B71C_0000B48A052A__INCLUDED_)



