// StringSimpleParser.h: interface for the CStringSimpleParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGSIMPLEPARSER_H__6BB8BAC8_FA59_4079_9D78_F37BC0EBD325__INCLUDED_)
#define AFX_STRINGSIMPLEPARSER_H__6BB8BAC8_FA59_4079_9D78_F37BC0EBD325__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "StringAnalyzer.h"

// 字符串简单解析类
// 用来解析指定字符串是否包含指定字符串（CStringAnalyzer 类）列表的序列
class CStringSimpleParser  
{
public:
	CStringSimpleParser();
	virtual ~CStringSimpleParser();

	void add(CStringAnalyzer *analyzer);

	// 解析 src 字符串
	int parse(CString src);

private:
	std::vector<CStringAnalyzer *> m_list;

};

#endif // !defined(AFX_STRINGSIMPLEPARSER_H__6BB8BAC8_FA59_4079_9D78_F37BC0EBD325__INCLUDED_)
