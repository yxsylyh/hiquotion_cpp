#include "StdAfx.h"
#include "MyCommandLineInfo.h"

CMyCommandLineInfo::CMyCommandLineInfo(void)
{
}

CMyCommandLineInfo::~CMyCommandLineInfo(void)
{
}

void CMyCommandLineInfo::ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast)
{
	static int num = 0;    
	CCommandLineInfo::ParseParam(lpszParam, bFlag, bLast); 
	switch(num) 
	{    
	case 0: 
		para = CString(lpszParam); 
		break; 
	} 
	num++;
}

