// Rand.h: interface for the CRand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAND_H__1FD08539_6DA3_4281_A833_E1F237C97074__INCLUDED_)
#define AFX_RAND_H__1FD08539_6DA3_4281_A833_E1F237C97074__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 生成随机数的类（使用 rand 标准函数）
class CRand  
{
public:
	CRand();
	virtual ~CRand();

	// 用时钟作为种子来初始化随机序列
	void init();
	// 产生 [low, high) 之间的随机数
	int randNumber(int low, int high);
	// 产生 [0, n) 的随机数
	int randNumberN(int n);
};

#endif // !defined(AFX_RAND_H__1FD08539_6DA3_4281_A833_E1F237C97074__INCLUDED_)
