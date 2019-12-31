// IPokerArea.h: interface for the IPokerArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOKERAREA_H__3FD1517B_61DD_4A93_8113_D017449E5004__INCLUDED_)
#define AFX_IPOKERAREA_H__3FD1517B_61DD_4A93_8113_D017449E5004__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Poker.h"
#include "PokerColumnArea.h"
#include "..\..\FoudationLib\DataStructLib\PointerList.h"

class IPokerArea : public IUIHandler
{
public:
	IPokerArea();
	IPokerArea(int count, CPoint relativePosition);
	virtual ~IPokerArea();

	// 初始化时添加牌
	void add(int columnIndex, CPoker *poker);
	
	// 设置扑克牌列对象
	void setPokerColumnArea(int count, CPoint relativePosition);

	// 判断是否可以落牌的方法
	virtual BOOL canDrop(CPoker *poker, CPoint relativeTopLeft=CPoint(0, 0)) { return FALSE; };

	// 获取下一个落牌的位置
	CPoint getNextDrop();

	// 落牌方法
	virtual void drop(CPoker *poker);

	// 获取所拾取纸牌的位置索引
	virtual int getPickupIndex(CPoker *poker);

	// 拾牌方法
	virtual void pickup(CPoker *poker);

protected:
	CPointerList<CPokerColumnArea *> m_pokerColumnArea;
	int m_count;
	
	int m_pokerDropIndex;
	int m_pokerPickupIndex;
};

#endif // !defined(AFX_IPOKERAREA_H__3FD1517B_61DD_4A93_8113_D017449E5004__INCLUDED_)
