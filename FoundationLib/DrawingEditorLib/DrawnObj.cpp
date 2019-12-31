// DrawnObj.cpp : implementation file
//

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "DrawnObj.h"
#include "SystemPropertyLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CDrawnObj, CObject, 0)

/////////////////////////////////////////////////////////////////////////////
// CDrawnObj

CDrawnObj::CDrawnObj()
{
	m_rect=CRect(0,0,30,20);
	m_selected=FALSE;
	m_properties=NULL;
}

CDrawnObj::CDrawnObj(CRect rect)
{
	m_rect=rect;
	m_selected=FALSE;
}

CDrawnObj::~CDrawnObj()
{
}


BEGIN_MESSAGE_MAP(CDrawnObj, CWnd)
	//{{AFX_MSG_MAP(CDrawnObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDrawnObj message handlers

// 属性

string CDrawnObj::getType()                    // 获取绘制对象的类型
{
	return "CDrawnObj";
}

// 获取绘制对象的名字
string CDrawnObj::getName()
{
	return m_name;
}

// 设置绘制对象的名字
void CDrawnObj::setName(string name)
{
	m_name=name;
}

CRect CDrawnObj::getRect()
{
	return m_rect;
}

void CDrawnObj::setRect(CRect rc)
{
	m_rect=rc;
}

// 获取该绘制对象是否被选择
BOOL CDrawnObj::getSelected()
{
	return m_selected;
}

// 设置该绘制对象是否被选择
void CDrawnObj::setSelected(BOOL isSelected)
{
	m_selected=isSelected;
}

BOOL CDrawnObj::operator ==(CDrawnObj *drawnObj)
{
	if(getName()==drawnObj->getName())
		return TRUE;
	else
		return FALSE;
}

void CDrawnObj::draw(CDC *pDC)                // 屏幕上绘制
{

}

// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
void CDrawnObj::drawOnCreating(CDC *pDC)
{
	draw(pDC);
}

BOOL CDrawnObj::isHitMe(CPoint hitPoint)      // 点鼠标左键后，是否点中了该绘制对象
{
	return FALSE;
}

void CDrawnObj::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{

}

CTracker CDrawnObj::getTracker()     // 获取选中框
{
	CTracker tracker;
	return tracker;
}

void CDrawnObj::moveHandle(int nHandle, CPoint point)  // 移动绘制对象Tracker的第nHandle号句柄到point点上
{
	m_rect=getTracker().moveTrackerHandle(nHandle,point);
}

// 判断绘制对象是否与指定的矩形区域相交
BOOL CDrawnObj::intersection(CRect rc)
{
 	CRect rect;
	return rect.IntersectRect(&m_rect,&rc); 
// 	return m_rect.IntersectRect(&m_rect,&rc);
}


void CDrawnObj::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_rect.left;
		ar << m_rect.top;
		ar << m_rect.right;
		ar << m_rect.bottom;
		ar << (DWORD)getSelected();
	}
	else
	{
		// get the document back pointer from the archive
//		m_pDocument = (CDrawDoc*)ar.m_pDocument;
// 		ASSERT_VALID(m_pDocument);
// 		ASSERT_KINDOF(CDrawDoc, m_pDocument);
		
		ar >> m_rect.left;
		ar >> m_rect.top;
		ar >> m_rect.right;
		ar >> m_rect.bottom;
		DWORD dtmp=0;
		ar >> dtmp;
		setSelected((BOOL)dtmp);
	}

}
