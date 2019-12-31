// Rand.cpp: implementation of the CRand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRand::CRand()
{
	init();
}

CRand::~CRand()
{

}

// 用时钟作为种子来初始化随机序列
void CRand::init()
{
	srand((unsigned int)time(NULL));
}

// 产生 [low, high) 之间的随机数（使用 rand 标准函数）
int CRand::randNumber(int low, int high)
{
	return low + rand() % (high - low + 1);
}

// 产生 [0, n) 的随机数
int CRand::randNumberN(int n)
{
	return randNumber(0, n);
}
