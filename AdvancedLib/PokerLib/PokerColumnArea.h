// PokerColumnArea.h: interface for the CPokerColumnArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKERCOLUMNAREA_H__FB046CFD_8AE9_4FC4_8849_DFCDE2ABF766__INCLUDED_)
#define AFX_POKERCOLUMNAREA_H__FB046CFD_8AE9_4FC4_8849_DFCDE2ABF766__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\UIHANDLERLIB\IUIHandler.h>
#include "Poker.h"

class CPokerColumnArea : public IUIHandler
{
public:
	CPokerColumnArea();
	virtual ~CPokerColumnArea();

	// 判断是否可以落牌的方法
	virtual BOOL canDrop(CPoker *poker, CPoint relativeTopLeft=CPoint(0, 0));

	// 获取下一个落牌的位置
	CPoint getNextDrop();
	
	// 落牌方法
	virtual void drop(CPoker *poker);

	// 拾牌方法
	virtual void pickup(CPoker *poker);

	// 是否包含指定纸牌
	BOOL contain(CPoker *poker);

	// 获取本列中最下面一张牌
	CPoker *getBottomPoker();

	CPoint getRelativePositioin() const { return CPoint(m_relativeX, m_relativeY); }
	void setRelativePositioin(int x, int y) { m_relativeX = x; m_relativeY = y; }
	void setRelativePositioin(CPoint relativePosition) { m_relativeX = relativePosition.x; m_relativeY = relativePosition.y; }

protected:
	// 获取给定牌的上面一张牌
	CPoker *getParentofPokerChild(CPoker *pokerChild);

	// 事件处理
	virtual void OnSize(int cx, int cy) {};

private:
	int m_relativeX;
	int m_relativeY;

	CPoker *m_bottomPoker;

	// 这个纸牌子区应该是一个通用的区域，任何扑克牌游戏都有，那么这两个方法，应该由外部来指定比较好
	// 也就是说，内部应该有一个 IPokerArea 对象指针变量，由外部传入该对象，作为判断的策略
	// 目前该程序先不这样改，因为以后恐怕不会再做游戏了……
};

#endif // !defined(AFX_POKERCOLUMNAREA_H__FB046CFD_8AE9_4FC4_8849_DFCDE2ABF766__INCLUDED_)
