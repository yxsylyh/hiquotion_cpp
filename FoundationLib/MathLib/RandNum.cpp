#include "StdAfx.h"
#include "RandNum.h"

CRandNum::CRandNum(void)
{
}

CRandNum::~CRandNum(void)
{
}

// 随机生成 min 到 max 之间的一个整数
int CRandNum::generate(int min, int max)
{
	if(min==max)
		return min;

	if(min>max){
		int tmp=min;
		min=max;
		max=tmp;
	}

	srand(GetTickCount());
	return min+rand()%(max-min+1);

}
