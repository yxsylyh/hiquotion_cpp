// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Label.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLabel::CLabel()
: m_caption(""), m_foreColor(RGB(0, 0, 0)), m_textAlign(0), m_oldFont(NULL), m_textWrapped(TRUE)
{
	memset(&m_logFont,0x00,sizeof(m_logFont));
	strcpy(m_logFont.lfFaceName,"宋体");
	m_logFont.lfHeight=16;
	m_logFont.lfWidth=8;
	m_logFont.lfUnderline=0;
	m_logFont.lfStrikeOut=0;

	m_borderStyle=-1;
	m_fillStyle=1;
}

CLabel::CLabel(int left, int top, int right, int bottom, std::string caption, COLORREF color, int textAlign)
: CRectangle(left, top, right, bottom), m_caption(caption), m_foreColor(color), m_textAlign(textAlign), m_oldFont(NULL), m_textWrapped(TRUE)
{
	memset(&m_logFont,0x00,sizeof(m_logFont));
	strcpy(m_logFont.lfFaceName,"宋体");
	m_logFont.lfHeight=16;
	m_logFont.lfWidth=8;
	m_logFont.lfUnderline=0;
	m_logFont.lfStrikeOut=0;
	
	m_borderStyle=-1;
	m_fillStyle=1;
}

CLabel::CLabel(CRect rect, std::string caption, COLORREF color, int textAlign)
: CRectangle(rect), m_caption(caption), m_foreColor(color), m_textAlign(textAlign), m_oldFont(NULL), m_textWrapped(TRUE)
{
	memset(&m_logFont,0x00,sizeof(m_logFont));
	strcpy(m_logFont.lfFaceName,"宋体");
	m_logFont.lfHeight=16;
	m_logFont.lfWidth=8;
	m_logFont.lfUnderline=0;
	m_logFont.lfStrikeOut=0;

	m_borderStyle=-1;
	m_fillStyle=1;
}

CLabel::~CLabel()
{

}

// 属性

// 获取和设置文本内容
std::string CLabel::getCaption()
{
	return m_caption;
}

void CLabel::setCaption(std::string caption)
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
	return m_logFont;
}

void CLabel::setFont(tagLOGFONTA font)
{
	m_logFont=font;
}

// 方法

void CLabel::preparePenAndBrush(CDC *pDC)  // 在绘图前，先准备好笔和画刷
{
	IShape::preparePenAndBrush(pDC);

	m_font.CreateFontIndirect(&m_logFont);
	m_oldFont=pDC->SelectObject(&m_font);
}

void CLabel::restorePenAndBrush(CDC *pDC)  // 绘图之后，恢复原来的笔和画刷
{
	IShape::restorePenAndBrush(pDC);

	if(m_oldFont)
	{
		pDC->SelectObject(m_oldFont);
		m_oldFont=NULL;
	}

	if(m_font.GetSafeHandle())
		m_font.DeleteObject();
}

void CLabel::drawMe(CDC *pDC, CPoint point)
{
	CRect rect=m_rect;
	rect.OffsetRect(point);
	
	pDC->MoveTo(rect.TopLeft());
	pDC->Rectangle(rect);
	pDC->SetTextColor(m_foreColor);
	//	pDC->SetTextAlign(m_textAlign);
	pDC->SetTextJustification(3,2);
	pDC->MoveTo(rect.TopLeft());
	pDC->SetBkMode(TRANSPARENT);    // 设置文字背景透明，等于使用矩形的背景色
	UINT flag=m_textAlign;
	// 判断文本是单行显示，还是折行显示
	if(m_textWrapped)
		flag |= DT_WORDBREAK;
	else
		flag |= DT_SINGLELINE;
	pDC->DrawText(m_caption.c_str(),rect, flag);  // 第三个参数表示对齐方式，0-居左，1-居中，2-居右
}

void CLabel::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}
