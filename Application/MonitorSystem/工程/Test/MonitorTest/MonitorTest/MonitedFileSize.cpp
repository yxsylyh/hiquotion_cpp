#include "StdAfx.h"
#include "MonitedFileSize.h"
#include <FileSysLib\FileOperation.h>

CMonitedFileSize::CMonitedFileSize(void)
{
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
		m_path=translatePath(m_path);
		if(!CFileOperation::isFileExist(m_path.c_str()))
		{
			return FALSE;
		}

		getStatus(&m_lastStatus);

		m_condition=configRoot.child_value("Condition");
		if(m_condition=="NotChanged")
			condition=0;
// 		else if(m_condition=="Greater")
// 			condition=1;
// 		else if(m_condition=="Less")
// 			condition=-1;
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

	CFileSizeStatus statusNow;
	getStatus(&statusNow);
	if(m_lastStatus.compare(&statusNow)==0)
		isSatisfied=TRUE;
	else
		isSatisfied=FALSE;

	// 将当前状态作为最后一次的状态
	m_lastStatus.FileSize=statusNow.FileSize;

	return isSatisfied;
}

void CMonitedFileSize::getStatus(IStatus *status)
{
	ULONGLONG size=CFileOperation::getFileSize(m_path.c_str());
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
