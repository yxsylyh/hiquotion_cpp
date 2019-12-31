// HandArea.cpp: implementation of the CHandArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HandArea.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHandArea::CHandArea()
: IPokerArea(3, CPoint(0, 0))
{

}

CHandArea::~CHandArea()
{

}

// 判断是否可以落牌的方法
BOOL CHandArea::canDrop(CPoker *poker, CPoint relativeTopLeft)
{
	if(!poker)
		return FALSE;

// 	// 如果drop过来的牌下面还有牌，就不允许放牌
// 	if(poker->getUIHandler(0))
// 		return FALSE;

	CRect pokerRect=poker->getRect();
	
	CRect rect;
	for(int i=0;i<3;i++)
	{
		CRect relativeRect=m_rect[i];
		relativeRect.OffsetRect(relativeTopLeft);
		
		if(rect.IntersectRect(&pokerRect, &relativeRect))
		{
			if(!m_pokerColumnArea[i]->getBottomPoker())
			{
				m_pokerDropIndex=i;
				return TRUE;
			}
			else
				return FALSE;
		}
	}

	return FALSE;
}

// 事件处理
void CHandArea::OnSize(int cx, int cy)
{
	int left=cx/16;
	int width=cx/4;
	int interval=cx/16;
	
	int top=cy/20;
	int height=cy*4/5;
	
	for(int i=0;i<3;i++)
	{
// 		m_areaRect[i].left=left+i*(width+interval);
		m_areaRect[i].left=left+i*(CPoker::getWidth()+interval);
		m_areaRect[i].top=top;
		m_areaRect[i].right=m_areaRect[i].left+CPoker::getWidth(); //width;
		m_areaRect[i].bottom=top+height;
		
		m_pokerColumnArea[i]->setRect(m_areaRect[i]);
	}
}
