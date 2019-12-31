// StringSimpleParser.cpp: implementation of the CStringSimpleParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AddressFilter.h"
#include "StringSimpleParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringSimpleParser::CStringSimpleParser()
{

}

CStringSimpleParser::~CStringSimpleParser()
{

}

void CStringSimpleParser::add(CStringAnalyzer *analyzer)
{
	m_list.push_back(analyzer);
}

// 解析 src 字符串
// 返回值：
// 1，成功
// 0，失败
// -1，src 为空
// -2，CStringAnalyzer 检查失败
int CStringSimpleParser::parse( CString src )
{
	if(src=="")
		return -1;

	for(int i=0;i<m_list.size();i++)
	{
		CStringAnalyzer *analyzer=m_list.at(i);
		if(!analyzer)
			continue;

		if(src=="")
			return 0;

		int ret=analyzer->check(src, src);
		if(ret==-1)
			return -2;

		if(ret==0 && analyzer->getOptional())
			return 0;
	}

	return 1;
}
