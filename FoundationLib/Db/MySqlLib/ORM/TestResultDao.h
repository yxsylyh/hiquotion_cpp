#pragma once

#include "DbOperation.h"

class CTestResultDao
{
public:
	CTestResultDao();
	CTestResultDao(CDbOperation *opr);
	~CTestResultDao(void);

	// 获取最后一个 AutoIncrement（即自增长字段） 插入数据后的 id 值
	int getLastId();

protected:
	CDbOperation *m_opr;
};
