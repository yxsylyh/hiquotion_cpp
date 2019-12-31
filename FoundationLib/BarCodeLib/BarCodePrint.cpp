// BarCodePrint.cpp: implementation of the CBarCodePrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BarCodePrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBarCodePrint::CBarCodePrint()
{

}

CBarCodePrint::~CBarCodePrint()
{

}

int CBarCodePrint::printBarCode(LPSTR text, CDC* pDC, float m_CodeWidth, float m_CodeHigh, float ratox, float ratoy, int x, int y)
{
	//  源码学习下载www.lvcode.com
	//    欢迎分享源码给Love代码
	CPen pen,*pOldPen;
	int High,i;
	LPSTR str=text;
	//设定条码左上脚初始点
// 	CPoint point(50,50);
	CPoint point(x, y);
	
	//画笔为黑色
	pen.CreatePen (PS_SOLID,int(m_CodeWidth*ratox),RGB(0,0,0));
	//将画笔选入打印设备环境
	pOldPen=pDC->SelectObject (&pen);
	High=int(m_CodeHigh*ratoy);
	
	while(*str)
	{
		for(i=0;i<(*str-'0');i++)
		{
			pDC->MoveTo (point);
			pDC->LineTo (point.x,point.y+High);
			point.x+=int(m_CodeWidth*ratox);
		}
		str++;
		point.x+=int(m_CodeWidth*ratox)*(*str-'0');
		str++;
	}
	pDC->SelectObject (pOldPen);
	pen.DeleteObject ();
	return 0;
}

BOOL CBarCodePrint::printText(CString text, CDC *pDC, LPRECT rect, int textAlign, LOGFONT *m_font)
{
	CFont *oldFont=NULL;
	if(m_font)
	{
		CFont font;
		font.CreateFontIndirect(m_font);
		oldFont=pDC->SelectObject(&font);
	}

	CPen pen,*pOldPen;
	//画笔为黑色
	pen.CreatePen (PS_SOLID,1,RGB(0,0,0));

	pOldPen=pDC->SelectObject (&pen);
	pDC->DrawText(text, rect, textAlign+DT_WORDBREAK);  // 第三个参数表示对齐方式，0-居左，1-居中，2-居右
	pDC->SelectObject (pOldPen);
	if(oldFont)
		pDC->SelectObject(oldFont);
	pen.DeleteObject ();

	return TRUE;
}
