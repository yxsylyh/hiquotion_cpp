// PokerSet.cpp: implementation of the CPokerSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PokerSet.h"
#include <C++\FoudationLib\RandLib\Rand.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPokerSet::CPokerSet()
: m_pokerCount(52)
{
	init();
}

CPokerSet::~CPokerSet()
{

}

// 初始化纸牌数组
void CPokerSet::init()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		for(int j=0;j<13;j++)
		{
			poker[13*i+j].setPoker((PokerType)i, (PokerValue)j);
		}
	}

	for(i=0;i<54;i++)
	{
		m_unshuffled.push_back(i);
	}
}

// 设置纸牌大小
void CPokerSet::setPokerSize(int width, int height)
{
	for(int i=0;i<54;i++)
	{
		CRect rect=poker[i].getRect();
		rect.right=rect.left+width;
		rect.bottom=rect.top+height;
		poker[i].setRect(rect);
	}
}

// 设置未洗牌的顺序，如果参数为空，则按照顺序设置
void CPokerSet::setUnshuffled(int n[], int count)
{
	m_unshuffled.clear();

	int i=0;
	if(!n || count<=0)
	{
		for(i=0;i<54;i++)
		{
			m_unshuffled.push_back(i);
		}
		return;
	}

	for(i=0;i<count;i++)
	{
		m_unshuffled.push_back(n[i]);
	}
}

// 洗牌
void CPokerSet::shuffle(int times)
{
	if(times<1)
		times=1;

	memset(m_shuffled, 0, 54*sizeof(int));
	CRand rander;
	rander.init();
	for(int i=0;i<times;i++)
	{
		for(int j=0;j<m_pokerCount-1;j++)
		{
// 			rander.init();
			int rnd=rander.randNumberN(m_pokerCount-j);
			m_shuffled[j]=m_unshuffled.at(rnd);
			m_unshuffled.remove(m_unshuffled.at(rnd));
		}

		m_shuffled[m_pokerCount-1]=m_unshuffled.at(0);
		m_unshuffled.clear();

		if(times>1)
			setUnshuffled(m_shuffled, m_pokerCount);
	}
}

// 获取第 index 张牌（原始顺序）
CPoker *CPokerSet::getPoker(int index)
{
	if(index<0 || index >= m_pokerCount)
		return NULL;

	return &poker[index];
}
// 获取第 index 张牌（洗牌后的顺序）
CPoker *CPokerSet::getShuffledPoker(int index)
{
	if(index<0 || index >= m_pokerCount)
		return NULL;

	return &poker[m_shuffled[index]];
}

void CPokerSet::setPokerCount(int val)
{
	if(val>54)
		return;

	m_pokerCount = val;
}
