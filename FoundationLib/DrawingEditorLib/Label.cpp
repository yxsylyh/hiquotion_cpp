// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Label.h"
#include "RectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLabel, CRectangle, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLabel::CLabel()
{
	m_caption="请添加文字";
	m_foreColor=RGB(0,0,0);
	m_textAlign=0;
	memset(&m_font,0x00,sizeof(m_font));
	strcpy(m_font.lfFaceName,"宋体");
	m_font.lfHeight=16;
	m_font.lfWidth=8;
	m_font.lfUnderline=0;
	m_font.lfStrikeOut=0;
}

CLabel::CLabel(CRect rect, string caption, COLORREF color, int textAlign) : CRectangle(rect)
{
	m_caption=caption;
	m_foreColor=RGB(0,0,0);
	m_foreColor=color;
	m_textAlign=textAlign;
	memset(&m_font,0x00,sizeof(m_font));
	strcpy(m_font.lfFaceName,"宋体");
	m_font.lfHeight=16;
	m_font.lfWidth=8;
	m_font.lfUnderline=0;
	m_font.lfStrikeOut=0;
}

CLabel::~CLabel()
{

}

// 属性

string CLabel::getType()                   // 获取绘制对象的类型
{
	return "CLabel";
}

// CTracker CLabel::getTracker()   // 获取选中框
// {
// 	CRectangleTracker rectTracker(m_rect);
// 	return rectTracker;
// }

// 获取和设置文本内容
string CLabel::getCaption()
{
	return m_caption;
}

void CLabel::setCaption(string caption)
{
	m_caption=caption;
}

// 获取和设置前景色
COLORREF CLabel::getForeColor()
{
	return m_foreColor;
}

void CLabel::setForeColor(COLORREF color)
{
	m_foreColor=color;
}

// 获取和设置文本对齐方式
int CLabel::getTextAlign()
{
	return m_textAlign;
}

void CLabel::setTextAlign(int textAlign)
{
	if(textAlign>=0 && textAlign<3)
		m_textAlign=textAlign;
	else
		m_textAlign=0;
}

// 获取和设置字体
tagLOGFONTA CLabel::getFont()
{
	return m_font;
}

void CLabel::setFont(tagLOGFONTA font)
{
	m_font=font;
}


// 方法

void CLabel::draw(CDC *pDC)                // 屏幕上绘制
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_borderColor;
	
	CPen pen;
	// PS_ENDCAP_ROUND 表示圆点
	// 	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|PS_ENDCAP_ROUND, 2, &logBrush);
	pen.CreatePen(m_borderStyle|PS_GEOMETRIC|PS_ENDCAP_SQUARE,m_borderWidth, &logBrush);
// 	CPen pen;
// 	pen.CreatePen(m_borderStyle,m_borderWidth,m_borderColor);
	CPen *oldPen=pDC->SelectObject(&pen);
	
	CBrush brush;
	CBrush *oldBrush=NULL;
	switch(m_fillStyle)
	{
	case 0:  // 实心填充
		brush.CreateSolidBrush(m_backColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	case 1:  // 透明填充
		
		// 		brush.CreateSysColorBrush(0);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:  // Hatch 填充
		brush.CreateHatchBrush(m_fillStyle-2,m_backColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	}

	CFont font;
	font.CreateFontIndirect(&m_font);
	CFont *oldFont=pDC->SelectObject(&font);

	pDC->MoveTo(m_rect.TopLeft());
	pDC->Rectangle(m_rect);
	pDC->SetBkMode(1);    // 设置文字背景透明，等于使用矩形的背景色
	pDC->SetTextColor(m_foreColor);
//	pDC->SetTextAlign(m_textAlign);
	pDC->SetTextJustification(3,2);
	pDC->DrawText(m_caption.c_str(),m_rect,m_textAlign+DT_WORDBREAK);  // 第三个参数表示对齐方式，0-居左，1-居中，2-居右

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldFont);
}

void CLabel::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}

void CLabel::Serialize(CArchive &ar)
{
	CRectangle::Serialize(ar);
	if (ar.IsStoring())
	{
		CString s=m_caption.c_str();
		ar << s;
		ar << m_foreColor;
		ar << m_textAlign;
		ar.Write(&m_font,sizeof(m_font));

	}
	else
	{
		CString s="";
		ar >> s;
		m_caption=s.GetBuffer(s.GetLength());
		ar >> m_foreColor;
		ar >> m_textAlign;
		if(m_textAlign<0 || m_textAlign>2)
			m_textAlign=0;
		ar.Read(&m_font,sizeof(m_font));
	}
	
}

