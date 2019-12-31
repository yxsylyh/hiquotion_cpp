// FilledArea.h: interface for the CFilledArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILLEDAREA_H__1BF4F826_B86D_40E2_B920_91A2226D90B0__INCLUDED_)
#define AFX_FILLEDAREA_H__1BF4F826_B86D_40E2_B920_91A2226D90B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDrawing.h"

enum Shape
{
	Rect,
	Circle,
	Eclipse,
	RoundRectangle,
};

enum FillType
{
	Solid,        // 纯色填充
	Hatch,        // Hatch 图案填充
	Gradient,     // 渐变填充
	Picture,      // BMP 图片填充
	Figure,       // IFigure 类对象填充（该填充方式所绘制的图形可能会超出填充区域）
};

enum GradientType
{
	Horizen,      // 水平填充
	Vertical,     // 垂直填充
	Angel,        // 某角度直线填充
	Radial,       // 径向
	Clockwise,    // 顺时针
	Unclockwise,  // 逆时针
};

#pragma comment(lib,"cxImage\\cximage.lib")
#pragma comment(lib,"cxImage\\jasper.lib")
#pragma comment(lib,"cxImage\\Jpeg.lib")
#pragma comment(lib,"cxImage\\libdcr.lib")
#pragma comment(lib,"cxImage\\png.lib")
#pragma comment(lib,"cxImage\\Tiff.lib")
#pragma comment(lib,"cxImage\\zlib.lib")

#include <C++/3rdParty/cxImage/include/ximage.h>

#pragma comment(lib,"gdiplus.lib")
#define ULONG_PTR ULONG
#include <C++/3rdParty/GDIPlus/Includes/GdiPlus.h>

using namespace Gdiplus;

// 填充区域
// 纯色填充、渐变色填充、图案填充
// 填充样式
class CFilledArea : public IDrawing
{
public:
	CFilledArea();
	virtual ~CFilledArea();

	// 形状
	Shape getShape() const { return m_shape; }
	void setShape(Shape val) { m_shape = val; }

	// 背景填充颜色
	COLORREF getColor() const { return m_bgColor; }
	void setColor(COLORREF val) { m_bgColor = val; }

	// 填充类型
	FillType getFillType() const { return m_fillType; }
	void setFillType(FillType val) { m_fillType = val; }

	// 背景是否透明
	BOOL getBgTransparent() const { return m_bgTransparent; }
	void setBgTransparent(BOOL val) { m_bgTransparent = val; }

	// hatch 填充样式
	int getHatchStyle() const { return m_hatchStyle; }
	void setHatchStyle(int val) { m_hatchStyle = val; }

	// hatch 填充的前景色
	COLORREF getHatchColor() const { return m_hatchColor; }
	void setHatchColor(COLORREF val) { m_hatchColor = val; }

	// 渐变填充类型
	GradientType getGradientType() const { return m_gradientType; }
	void setGradientType(GradientType val) { m_gradientType = val; }

	// 渐变色
	Color getGradientColor1() const { return m_gradientColor1; }
	void setGradientColor1(Color val) { m_gradientColor1 = val; }
	Color getGradientColor2() const { return m_gradientColor2; }
	void setGradientColor2(Color val) { m_gradientColor2 = val; }

	// 图案填充用的 BMP 图片
	CxImage * getPicture() const { return m_picture; }
	void setPiture(CxImage * val) { m_picture = val; }

	// 圆角矩形的圆角大小
	POINT getRoundPoint() const { return m_roundPoint; }
	void setRoundPoint(POINT val) { m_roundPoint = val; }

	// Figure 方式填充
	IDrawing * getFillFigure() const { return m_fillFigure; }
	void setFillFigure(IDrawing * val) { m_fillFigure = val; }

	virtual void draw(CDC *pDC);        // 屏幕上绘制
	virtual void move(CSize moveShift); // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点

protected:
	Shape m_shape;
	COLORREF m_bgColor;
	FillType m_fillType;
	BOOL m_bgTransparent;
	int m_hatchStyle;     // 用于 Hatch 填充
	COLORREF m_hatchColor; // 用于 Hatch 填充的前景色
	GradientType m_gradientType;  // 用于 Gradient 填充
	Color m_gradientColor1;    // 用于渐变填充的第一个颜色
	Color m_gradientColor2;    // 用于渐变填充的第二个颜色
	Color *m_colorArray;  // 用于渐变填充的颜色数组
	REAL *positionArray;  // 用于渐变填充的位置数组
	CxImage *m_picture;    // 用于图片填充
	POINT m_roundPoint;   // 决定圆角矩形的圆弧大小
	IDrawing *m_fillFigure;    // Figure 方式填充
};

#endif // !defined(AFX_FILLEDAREA_H__1BF4F826_B86D_40E2_B920_91A2226D90B0__INCLUDED_)
