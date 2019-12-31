// IPokerArea.cpp: implementation of the IPokerArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPokerArea.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IPokerArea::IPokerArea()
: m_pokerDropIndex(-1), m_pokerPickupIndex(-1)
{

}

IPokerArea::IPokerArea(int count, CPoint relativePosition)
{
	setPokerColumnArea(count, relativePosition);
}

IPokerArea::~IPokerArea()
{
	m_pokerColumnArea.destroyAll();
}

// 初始化时添加牌
void IPokerArea::add(int columnIndex, CPoker *poker)
{
	if(columnIndex<0 || columnIndex>=m_count)
		return;

	m_pokerColumnArea[columnIndex]->drop(poker);
}

// 设置扑克牌列对象
void IPokerArea::setPokerColumnArea(int count, CPoint relativePosition)
{
	if(count<=0)
		return;

	m_count=count;

	// 如果需要重新设置 CPokerColumnArea，则需要清除 CPokerColumnArea 对象，需要把this的所有area 树节点全部delete掉
	// 这里不需要重新设置，所以这些代码暂时注释掉（因为还没有删除 CTreeNode 子节点的方法
// 	CTreeNode<IUIHandler *>::

	m_pokerColumnArea.destroyAll();
	m_pokerColumnArea.clear();

	for(int i=0;i<m_count;i++)
	{
		CPokerColumnArea *area=new CPokerColumnArea();
		area->setRelativePositioin(relativePosition);
		area->setBorderStyle(-1);
		area->setFillStyle(TRANSPARENT);
		area->setMovingEffected(ChildHandled);
		m_pokerColumnArea.push_back(area);
		addUIHandler(area);
	}
}

// 获取下一个落牌的位置
CPoint IPokerArea::getNextDrop()
{
	if(m_pokerDropIndex>=0 && m_pokerDropIndex<m_count)
	{
		return m_pokerColumnArea[m_pokerDropIndex]->getNextDrop();
	}
	else
		return CPoint(0, 0);
}

// 落牌方法
void IPokerArea::drop(CPoker *poker)
{
	if(!poker)
		return;

	m_pokerPickupIndex=getPickupIndex(poker);
	if(m_pokerDropIndex>=0 && m_pokerDropIndex<m_count)
	{
		m_pokerColumnArea[m_pokerDropIndex]->drop(poker);
		m_pokerDropIndex=-1;
	}
}

// 获取所拾取纸牌的位置索引
int IPokerArea::getPickupIndex(CPoker *poker)
{
	if(!poker)
		return -1;
	
	for(int i=0;i<m_count;i++)
	{
		if(!m_pokerColumnArea[i])
			continue;

		if(m_pokerColumnArea[i]->contain(poker))
			return i;
	}
	
	return -2;
}

// 拾牌方法
void IPokerArea::pickup(CPoker *poker)
{
	if(!poker)
		return;
	
	m_pokerPickupIndex=getPickupIndex(poker);
	if(m_pokerPickupIndex>=0 && m_pokerPickupIndex<m_count)
	{
		if(!m_pokerColumnArea[m_pokerPickupIndex])
			return;
		
		m_pokerColumnArea[m_pokerPickupIndex]->pickup(poker);
		m_pokerPickupIndex=-1;
	}
}

