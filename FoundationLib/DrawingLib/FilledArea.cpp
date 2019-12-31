// FilledArea.cpp: implementation of the CFilledArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FilledArea.h"

#include <C++\3rdParty\GDIPlus\Includes\GdiplusTypes.h>
#include <C++\3rdParty\GDIPlus\Includes\GdiplusGpStubs.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilledArea::CFilledArea()
{
	m_shape=Rect;
	m_bgColor=RGB(0,0,0);
	m_fillType=Solid;
	m_bgTransparent=FALSE;
	m_hatchStyle=HS_HORIZONTAL;     // 用于 Hatch 填充
	m_hatchColor=RGB(0,0,0); // 用于 Hatch 填充的前景色
	m_gradientType=Horizen;  // 用于 Gradient 填充
	m_gradientColor1=RGB(0,0,0);    // 用于渐变填充的第一个颜色
	m_gradientColor2=RGB(255,255,255);    // 用于渐变填充的第二个颜色
	m_picture=NULL;    // 用于图片填充
	m_roundPoint.x=5;   // 决定圆角矩形的圆弧大小
	m_roundPoint.y=5;   // 决定圆角矩形的圆弧大小
	m_fillFigure=NULL;  // Figure 方式填充
}

CFilledArea::~CFilledArea()
{

}

void CFilledArea::draw(CDC *pDC)                // 屏幕上绘制
{
	if(!pDC)
		return;

	CPen pen;
	CPen *oldPen=NULL;
	
	CBrush brush;
	CBrush *oldBrush=NULL;
	Gdiplus::Graphics graphics(pDC->GetSafeHdc());
	
	// 获取视图客户区大小
	// 定义一个线性渐变画刷，按红黄蓝绿的顺序四种颜色渐变
	Gdiplus::LinearGradientBrush linGrBrush(Gdiplus::Point(100,0),Gdiplus::Point(100,m_rect.Height()/2),Gdiplus::Color(255,255,0,0),Gdiplus::Color(255,255,0,255));
	Gdiplus::Color colors[] = {
		Gdiplus::Color(255, 255, 0, 0),   // red
		Gdiplus::Color(255, 255, 255, 0), //yellow
		Gdiplus::Color(255, 0, 255, 0),   // green
		Gdiplus::Color(255, 0, 255, 255),   // 青
		Gdiplus::Color(255, 0, 0, 255),   // blue
		Gdiplus::Color(255, 255, 0, 255)  // 紫
	};
// 	Gdiplus::REAL positions[] = {0.0f, 0.33f, 0.66f, 1.0f};  
	Gdiplus::REAL positions[] = {0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f};  
	BOOL ret=FALSE;
	switch(m_fillType)
	{
	case Solid:  // 实心填充
		brush.CreateSolidBrush(m_bgColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	case Hatch:  // Hatch 填充
// 		if(m_bgTransparent)
// 			pDC->SetBkMode(TRANSPARENT);
// 		else
// 			pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_bgColor); // 这个是用在写字时去掉背景色的。。。
		brush.CreateHatchBrush(m_hatchStyle, m_hatchColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	case Gradient:
		// 定义一个画图对象
		linGrBrush.SetInterpolationColors(colors, positions,6);
		// 填充指定区域矩形
		graphics.FillRectangle(&linGrBrush,m_rect.Width()/2,0,80,m_rect.Height()/2);
// 		AfxMessageBox("暂未实现");
// 		GDI+的多色线性渐变画刷（也可以实现任意角度的渐变画刷，但不知道任意角度绘制多色渐变是否可以）
// 		在头文件中加入下面的代码：
// #include <GdiPlus.h>
// using namespace Gdiplus;
// #pragma comment(lib,"gdiplus.lib")
// 		初始化：
// 		GdiplusStartupInput gdiplusStartupInput; 
// 		ULONG_PTR gdiplusToken; 
// 		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); 
//		使用
// 		Gdiplus::Rect rc(0,0,100,100);
//		//  第四个参数可以是渐变色的角度 (Gdiplus::REAL)(90 - iRotation));  //  渐变色的角度
// 		Gdiplus::LinearGradientBrush brush(rc,RGB(255,0,0,255), RGB(255,255,0,0), LinearGradientModeVertical);
// 		Gdiplus::REAL pos[] = {0.0f,0.3f,0.7f,1.0f};
// 		Gdiplus::Color cor[] = {Gdiplus::Color(255,0,0,255),Gdiplus::Color(255,0,255,0), Gdiplus::Color(255,255,255,0), Gdiplus::Color(255,255,0,0)};
// 		brush.SetInterpolation(&cor[0],&pos[0],4);
// 		CDC *pDC = GetDC();
// 		Gdiplus::Graphics draw = Gdiplus::Graphics::FromHDC(pDC->GetSafeHdc();
// 		draw.FillRectangle(&brush,rc);
// 		ReleaseDC(pDC);
// 		销毁：
// 		ULONG_PTR gdiplusToken = NULL; 
// 		GdiplusShutdown(gdiplusToken);
		break;
	case Picture:
// 		AfxMessageBox("暂未实现！因为不支持DIB位图。。。这功能太弱了！");
		break;
// 		if(m_patternBitmap)
// 		{
// 			ret=brush.CreatePatternBrush(m_patternBitmap);
// 			oldBrush=pDC->SelectObject(&brush);
// 		}
// 		break;
	case Figure:
		pDC->SetBkColor(m_bgColor); // 这个是用在写字时去掉背景色的。。。
		break;
	}
	
	if(m_bgTransparent)
		pDC->SetBkMode(TRANSPARENT);
	else
		pDC->SetBkMode(OPAQUE);
	
	pDC->MoveTo(m_rect.TopLeft());

	int length=0;
	if(m_fillType==Picture)
	{
		if(m_picture)
		{
			if(m_picture->IsValid())
				m_picture->Draw2(pDC->GetSafeHdc(), m_rect);
		}
	}
	else if(m_fillType==Figure)
	{
		pen.CreatePen(PS_SOLID,0, m_hatchColor);
		oldPen=pDC->SelectObject(&pen);
		if(m_fillFigure)
		{
			CPoint pt=m_fillFigure->getFirstPoint();
			pt.Offset(m_rect.TopLeft());
			m_fillFigure->draw(pDC, pt);
		}
	}
	else if(m_fillType==Gradient)
	{

	}
	else if(!m_bgTransparent || m_fillType==Hatch)
	{
		pen.CreatePen(PS_NULL,1, RGB(0,0,0));
		oldPen=pDC->SelectObject(&pen);
		switch(m_shape)
		{
		case Rect:
			pDC->Rectangle(m_rect);
			break;
		case Circle:
			length=min(m_rect.Width(), m_rect.Height());
			pDC->Ellipse(m_rect.left, m_rect.top, m_rect.left+length, m_rect.top+length);
			break;
		case Eclipse:
			pDC->Ellipse(m_rect);
			break;
		case RoundRectangle:
			pDC->RoundRect(m_rect, m_roundPoint);
			break;
		}
	}

	if(oldBrush)
		pDC->SelectObject(oldBrush);
	if(oldPen)
		pDC->SelectObject(oldPen);
}

void CFilledArea::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}
