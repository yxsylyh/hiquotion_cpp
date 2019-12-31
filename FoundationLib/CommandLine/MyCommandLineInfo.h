#pragma once
#include "afxwin.h"

class CMyCommandLineInfo :
	public CCommandLineInfo
{
public:
	CMyCommandLineInfo(void);
	~CMyCommandLineInfo(void);

	CString para;

	void ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast);
};
