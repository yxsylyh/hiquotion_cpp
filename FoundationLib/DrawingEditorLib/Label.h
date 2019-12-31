// Label.h: interface for the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABEL_H__715C6C15_54CC_489C_A01B_D130516D7346__INCLUDED_)
#define AFX_LABEL_H__715C6C15_54CC_489C_A01B_D130516D7346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "Rectangle.h"

class CLabel : public CRectangle  
{
public:
	CLabel();
	CLabel(CRect rect, string caption, COLORREF color=RGB(0,0,0), int textAlign=0);
	virtual ~CLabel();

	// 属性
	
	string getType();                     // 获取绘制对象的类型

	// 获取和设置文本内容
	string getCaption();
	void setCaption(string caption);

	// 获取和设置前景色
	COLORREF getForeColor();
	void setForeColor(COLORREF color);

	// 获取和设置文本对齐方式
	int getTextAlign();
	void setTextAlign(int textAlign);

	// 获取和设置字体
	tagLOGFONTA getFont();
	void setFont(tagLOGFONTA font);

	
	// 方法
	virtual void Serialize(CArchive &ar);
	
	void draw(CDC *pDC);                // 屏幕上绘制
	void move(CSize moveShift);            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点


protected:
	DECLARE_SERIAL(CLabel);


	string m_caption;
	COLORREF m_foreColor;
	int m_textAlign;
	LOGFONT m_font;
};

#endif // !defined(AFX_LABEL_H__715C6C15_54CC_489C_A01B_D130516D7346__INCLUDED_)
