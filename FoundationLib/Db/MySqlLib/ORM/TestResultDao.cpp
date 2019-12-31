#include "StdAfx.h"
#include "TestResultDao.h"

CTestResultDao::CTestResultDao()
: m_opr(NULL)
{
}

CTestResultDao::CTestResultDao(CDbOperation *opr)
: m_opr(opr)
{
}

CTestResultDao::~CTestResultDao(void)
{
}

// 获取最后一个 AutoIncrement（即自增长字段） 插入数据后的 id 值
int CTestResultDao::getLastId()
{
	if(!m_opr)
		return -11;

	char *sql="select LAST_INSERT_ID()";

	ResultSet *rs=m_opr->executeQuery(sql, 0);
	if(!rs)
		return -12;

	if(rs->next()==false)
		return -13;

// 	ULONGLONG v=rs->getInt64(1);
	int v=rs->getInt(1);

	m_opr->closeResultSet(rs);

	return v;
}
