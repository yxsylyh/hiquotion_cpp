#include "StdAfx.h"
#include "MonitedFileSize.h"
#include <FileSysLib\FileOperation.h>

CMonitedFileSize::CMonitedFileSize(void)
{
	Type="";
	Status="";

	m_path="";
	m_condition="";

	condition=0;
}

CMonitedFileSize::CMonitedFileSize(string type, string status)
{
	Type=type;
	Status=status;

	m_path="";
	m_condition="";

	condition=0;
}

CMonitedFileSize::~CMonitedFileSize(void)
{
}

BOOL CMonitedFileSize::readConfig(pugi::xml_node configRoot)
{
	try
	{
		m_path=configRoot.child_value("Path");
		m_translatedPath=translatePath(m_path);
		if(!CFileOperation::isFileExist(m_translatedPath.c_str()))
		{
			return FALSE;
		}

		getStatus(&m_lastStatus);

		m_condition=configRoot.child_value("Condition");
		CString scondition=m_condition.c_str();
		scondition=scondition.MakeLower();
		if(scondition=="notchanged")
			condition=0;
		else if(scondition=="greater")
			condition=1;
		else if(scondition=="less")
			condition=-1;
		else
			condition=0;
	}
	catch (CException* e)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMonitedFileSize::isConditionSatisfied()
{
	BOOL isSatisfied=FALSE;

	m_translatedPath=translatePath(m_path);
	if(!CFileOperation::isFileExist(m_translatedPath.c_str()))
	{
		return FALSE;
	}

	CFileSizeStatus statusNow;
	getStatus(&statusNow);
	if(m_lastStatus.compare(&statusNow)==condition)
		isSatisfied=TRUE;
	else
		isSatisfied=FALSE;

	// 将当前状态作为最后一次的状态
	m_lastStatus.FileSize=statusNow.FileSize;

	return isSatisfied;
}

void CMonitedFileSize::getStatus(IStatus *status)
{
	ULONGLONG size=CFileOperation::getFileSize(m_translatedPath.c_str());
	CFileSizeStatus *fstatus=(CFileSizeStatus *)status;
	fstatus->FileSize=size;
}

string CMonitedFileSize::translatePath(string path)
{
	CTime time=CTime::GetCurrentTime();
	CString sYear=time.Format("%Y");
	CString sMonth=time.Format("%m");
	CString sDay=time.Format("%d");

	CString spath=path.c_str();
	int n=0;
	spath=spath.MakeUpper();
	n=spath.Replace("%YEAR%",sYear);
	spath.Replace("%MONTH%",sMonth);
	spath.Replace("%DAY%",sDay);

	return (LPTSTR)(LPCSTR)spath;
}

string CMonitedFileSize::toString()
{
	string s="监控 " + Type + " 对象的 " + Status + "。";
	s+="\r\n文件路径：";
	s+=m_translatedPath;
	s+="\r\n满足条件：";
	s+=m_condition;

	return s;
}
