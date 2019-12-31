// StringAnalyzer.cpp: implementation of the CStringAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AddressFilter.h"
#include "StringAnalyzer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <C++/FoundationLib/StringExtLib/StringExt.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringAnalyzer::CStringAnalyzer()
: m_optional(FALSE)
{

}

CStringAnalyzer::CStringAnalyzer(BOOL optional)
: m_optional(optional)
{

}

CStringAnalyzer::CStringAnalyzer(CString s, BOOL optional)
: m_optional(optional)
{
	m_list.push_back(s);
}

CStringAnalyzer::~CStringAnalyzer()
{

}

// 检查源字符串 src，是否包含 m_list 中指定的字符串
int CStringAnalyzer::check( CString src, CString &dst )
{
	if(src=="")
		return -1;

	if(m_list.size()<=0)
		return -1;

	CString srcStr=src;
	for(int i=0;i<m_list.size();i++)
	{
		CString s=m_list.at(i);
		if(s=="")
			continue;

		if(CStringExt::stringRight(srcStr, s, dst))
		{
			return 1;
		}
	}

	return 0;
}
