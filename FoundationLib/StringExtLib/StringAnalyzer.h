// StringAnalyzer.h: interface for the CStringAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGANALYZER_H__D9003D83_AAC9_4625_BA57_236C329E3A30__INCLUDED_)
#define AFX_STRINGANALYZER_H__D9003D83_AAC9_4625_BA57_236C329E3A30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

// 字符串分析类
// 包含待检测的字符列表，包含是否可选的标志，包含检查方法
class CStringAnalyzer  
{
public:
	CStringAnalyzer();
	CStringAnalyzer(BOOL optional);
	CStringAnalyzer(CString s, BOOL optional);
	virtual ~CStringAnalyzer();

	// 添加待检测字符串
	void add(CString s)
	{
		m_list.push_back(s);
	}

	// 检查源字符串 src，是否包含 m_list 中指定的字符串
	// 返回值：
	// 1，成功
	// 0，失败
	// -1，有错误
	int check(CString src, CString &dst);

	BOOL getOptional() const { return m_optional; }

private:
	std::vector<CString> m_list;
	BOOL m_optional;
};

#endif // !defined(AFX_STRINGANALYZER_H__D9003D83_AAC9_4625_BA57_236C329E3A30__INCLUDED_)
