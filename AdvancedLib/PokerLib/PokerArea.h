// PokerArea.h: interface for the CPokerArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKERAREA_H__D4DD0D97_6607_4A73_953B_77A170CAF0EC__INCLUDED_)
#define AFX_POKERAREA_H__D4DD0D97_6607_4A73_953B_77A170CAF0EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\UIHANDLERLIB\IUIHandler.h>
#include <C++\ADVANCEDLIB\POKERLIB\IPokerArea.h>
#include "PokerColumnArea.h"

#define POKER_COLUMN_COUNT 7

class CPokerArea : public IPokerArea  
{
public:
	CPokerArea();
	virtual ~CPokerArea();

	// 判断是否可以落牌的方法
	virtual BOOL canDrop(CPoker *poker, CPoint relativeTopLeft=CPoint(0, 0));

	// 获取当前的纸牌宽度
	int getPokerWidth() { return m_pokerWidth; }
	
protected:
	// 事件处理
	virtual void OnSize(int cx, int cy);

private:
	CRect m_areaRect[POKER_COLUMN_COUNT];

	int m_pokerWidth;
};

#endif // !defined(AFX_POKERAREA_H__D4DD0D97_6607_4A73_953B_77A170CAF0EC__INCLUDED_)
