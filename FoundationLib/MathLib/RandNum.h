#pragma once

class CRandNum
{
public:
	CRandNum(void);
	~CRandNum(void);

	// 随机生成 min 到 max 之间的一个整数
	static int generate(int min, int max);
};
