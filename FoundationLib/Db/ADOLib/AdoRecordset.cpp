// AdoRecordset.cpp: implementation of the CAdoRecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoRecordset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoRecordset::CAdoRecordset(CAdoConnection *conn)
: m_conn(conn), m_isOpenBySelf(FALSE)
{
	HRESULT hr=m_pRecordset.CreateInstance( __uuidof( Recordset ));
	if( FAILED(hr) )
	{
		m_errMessage="创建数据库记录集对象失败！";
		m_isCreated=FALSE;
	}

	m_isCreated=TRUE;
}

CAdoRecordset::CAdoRecordset(_RecordsetPtr rec)
: m_conn(FALSE), m_isOpenBySelf(FALSE), m_pRecordset(rec)
{

}

CAdoRecordset::~CAdoRecordset()
{
	if(m_isOpenBySelf)
	{
		try
		{
			m_pRecordset->Close();
		}
		catch (_com_error &e)
		{
			m_errMessage=(LPCSTR)e.Description();
		}
	}
}

BOOL CAdoRecordset::open(CString tableName, int openWay)
{
	if(!m_conn)
	{
		m_errMessage="请先创建记录集对象。";
		m_isOpenBySelf=FALSE;
		return FALSE;
	}

	if(!m_conn->isConnected())
	{
		m_errMessage="数据库未连接。";
		m_isOpenBySelf=FALSE;
		return FALSE;
	}

	try
	{
// 		m_pRecordset->Open(_variant_t("zzspbc_o"), _variant_t((IDispatch *)pMyConnect,true), adOpenKeyset, adLockOptimistic, adCmdTable);
		switch(openWay)
		{
		case 0:
			m_pRecordset->Open(_variant_t(tableName), _variant_t((IDispatch *)m_conn->getAdoConnectionPtr(),true), adOpenKeyset, adLockOptimistic, adCmdTable);
			break;
		case 1:
			m_pRecordset->Open(_variant_t(tableName), _variant_t((IDispatch *)m_conn->getAdoConnectionPtr(),true), adOpenKeyset, adLockOptimistic, adCmdText);
			break;
		}
	}
	catch (_com_error &e)
	{
		m_errMessage="打开 " + tableName + " 失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		m_isOpenBySelf=FALSE;
		return FALSE;
	}

	m_isOpenBySelf=TRUE;
	return TRUE;
}

void CAdoRecordset::setFilter(CString filter)  // 相当于 where 条件（不包括 where 字符本身）
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return;
// 	}

	m_pRecordset->Filter=_variant_t(filter);
}

int CAdoRecordset::getRecordCount()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return 0;
// 	}

	int count=0;
	try
	{
		count=m_pRecordset->GetRecordCount();
	}
	catch (_com_error &e)
	{
		m_errMessage="获取记录数失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return 0;
	}

	return count;
}

BOOL CAdoRecordset::isEOF()
{
	return m_pRecordset->adoEOF==VARIANT_TRUE;
}

BOOL CAdoRecordset::isBOF()
{
	return m_pRecordset->BOF==VARIANT_TRUE;
}

BOOL CAdoRecordset::moveFirst()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}

	try
	{
		m_pRecordset->MoveFirst();
	}
	catch (_com_error &e)
	{
		m_errMessage="记录集 MoveFirst 操作失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}

BOOL CAdoRecordset::moveLast()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->MoveLast();
	}
	catch (_com_error &e)
	{
		m_errMessage="记录集 MoveLast 操作失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}

BOOL CAdoRecordset::moveNext()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->MoveNext();
	}
	catch (_com_error &e)
	{
		m_errMessage="记录集 MoveNext 操作失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAdoRecordset::movePrevious()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->MovePrevious();
	}
	catch (_com_error &e)
	{
		m_errMessage="记录集 MovePrevious 操作失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
	
	return TRUE;
}

CString CAdoRecordset::getFieldString(CString fieldName)  // 获取当前记录指定字段的字符串
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return "";
// 	}

	if(fieldName.GetLength()<=0)
	{
		m_errMessage="指定的字段名称为空字符串！";
		return "";
	}

	try
	{
		// 暂时先注释掉看看有没有什么问题
// 		if(m_pRecordset->adoEOF==VARIANT_TRUE)
// 		{
// 			m_errMessage="指定的字段名称为空字符串！";
// 			return "";
// 		}

		CString svalue=(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t(fieldName))->Value);
		return svalue;
	}
	catch (_com_error &e)
	{
		m_errMessage="获取字段 " + fieldName + "值失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return "";
	}
}

BOOL CAdoRecordset::setFieldString(CString fieldName, CString fieldValue)  // 设置当前记录的指定字段的值
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	if(fieldName.GetLength()<=0)
	{
		m_errMessage="指定的字段名称为空字符串！";
		return FALSE;
	}

	if(fieldValue.GetLength()<=0)
	{
		m_errMessage="指定的字段值为空字符串！";
		return FALSE;
	}
	
	try
	{
		m_pRecordset->Fields->GetItem(_variant_t(fieldName))->Value=_bstr_t(fieldValue);;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="设置字段 " + fieldName + "值为 " + fieldValue + " 失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

int CAdoRecordset::getFielInt(CString fieldName)  // 获取当前记录的指定字段的值
{
	if(fieldName.GetLength()<=0)
	{
		m_errMessage="指定的字段名称为空字符串！";
		return -1;
	}
	
	try
	{
		int nvalue=(m_pRecordset->Fields->GetItem(_variant_t(fieldName))->Value).dblVal;
		return nvalue;
	}
	catch (_com_error &e)
	{
		m_errMessage="获取字段 " + fieldName + "值失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return -1;
	}
}

BOOL CAdoRecordset::addNew()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}

	try
	{
		m_pRecordset->AddNew();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="调用 AddNew 方法失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::update()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->Update();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="调用 Update 方法失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::cancelUpdate()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->CancelUpdate();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="调用 CancelUpdate 方法失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::updateBatch(AffectEnum ae)
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->UpdateBatch(ae);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="调用 UpdateBatch 方法失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::cancelBatch(AffectEnum ae)
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->CancelBatch(ae);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="调用 CancelBatch 方法失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::deleteRecord(AffectEnum ae)  // 删除当前记录
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->Delete(ae);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="调用 Delete 方法失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::requery()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="请先打开记录集。";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->Requery(0);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="调用 Requery 方法失败！\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}
