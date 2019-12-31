// AdoRecordset.h: interface for the CAdoRecordset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADORECORDSET_H__E989F70F_923D_4A91_9B16_0387E2B5FE0C__INCLUDED_)
#define AFX_ADORECORDSET_H__E989F70F_923D_4A91_9B16_0387E2B5FE0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++/FoudationLib/IClassBase.h>
#include "AdoConnection.h"

class CAdoRecordset : public IClassBase
{
public:
	CAdoRecordset(CAdoConnection *conn);
	CAdoRecordset(_RecordsetPtr rec);
	virtual ~CAdoRecordset();

	BOOL open(CString tableName, int openWay=0);
	BOOL isOpen() const { return m_isOpenBySelf; }
	void setFilter(CString filter);  // 相当于 where 条件（不包括 where 字符本身）
	int getRecordCount();
	BOOL isEOF();
	BOOL isBOF();
	BOOL moveFirst();
	BOOL moveLast();
	BOOL moveNext();
	BOOL movePrevious();
	CString getFieldString(CString fieldName);  // 获取当前记录的指定字段的值
	BOOL setFieldString(CString fieldName, CString fieldValue);  // 设置当前记录的指定字段的值
	int getFielInt(CString fieldName);  // 获取当前记录的指定字段的值
	BOOL addNew();
	BOOL update();
	BOOL cancelUpdate();
	BOOL updateBatch(AffectEnum ae);
	BOOL cancelBatch(AffectEnum ae);
	BOOL deleteRecord(AffectEnum ae);  // 删除当前记录
	BOOL requery();

private:
	CAdoConnection *m_conn;
	_RecordsetPtr m_pRecordset;

	BOOL m_isCreated;
	BOOL m_isOpenBySelf;
};

#endif // !defined(AFX_ADORECORDSET_H__E989F70F_923D_4A91_9B16_0387E2B5FE0C__INCLUDED_)
