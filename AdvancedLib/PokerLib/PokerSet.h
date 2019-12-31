// PokerSet.h: interface for the CPokerSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKERSET_H__BBEC10B1_3AEF_40BC_BBA3_923F18A1A5B2__INCLUDED_)
#define AFX_POKERSET_H__BBEC10B1_3AEF_40BC_BBA3_923F18A1A5B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Poker.h"
#include <C++\FoudationLib\DataStructLib\ValueList.h>

// 4）一副扑克牌
static CPoker poker[54];

// 一副扑克牌的类
class CPokerSet  
{
public:
	CPokerSet();
	virtual ~CPokerSet();

	// 初始化纸牌数组
	void init();
	// 设置纸牌大小
	void setPokerSize(int width, int height);
	// 设置未洗牌的顺序，如果参数为空，则按照顺序设置
	void setUnshuffled(int n[], int count=54);
	// 洗牌
	void shuffle(int times=1);
	// 获取第 index 张牌（原始顺序）
	CPoker *getPoker(int index);
	// 获取第 index 张牌（洗牌后的顺序）
	CPoker *getShuffledPoker(int index);

	int getPokerCount() const { return m_pokerCount; }
	void setPokerCount(int val);

private:
	CValueList<int> m_unshuffled;
	int m_shuffled[54];
	int m_pokerCount;
};

#endif // !defined(AFX_POKERSET_H__BBEC10B1_3AEF_40BC_BBA3_923F18A1A5B2__INCLUDED_)
