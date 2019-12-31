#pragma once

#include <string>
#include <vector>
using namespace std;

class CStringExt
{
public:
	CStringExt(void);
	~CStringExt(void);

	static void Split(CString source, CStringArray& dest, CString division);
	static void Split(CStringArray *splitStrings, CHAR *buffer, DWORD size, CHAR find);
	static CString Capital(CString str);  // 首字母大写
	static CString camel(CString str);    // 首字母小写
	// 取 c 左边的字符串
	// 如果没有 c，则返回全部字符串
	// mode>0，则从左往右找，mode小于0，则从右往左找
	// mode值表示找到第几个为止，mode默认值为1，即从左往右找到第1个为止
	// 如果mode为0，则认为mode就是1。
// 	static CString stringLeft(CString str, char c, int mode=1);
	// 取 subStr 右边的字符串
	// 如果没有 subStr，则返回全部字符串
	static BOOL stringRight(CString str, CString subStr, CString &dst, int mode=1);

	static void string_replace(string&s1,const string&s2,const string&s3);

#if _MSC_VER  >  1200   // greater than vc6
	static char* wideChartoMultiByte(const wchar_t* wp);
	static wchar_t* multiBytetoWideChar(const char* c);
	static std::wstring utf8toWideChar(const char* buf);
	static std::string wideChartoUTF8(const wchar_t* buf);

#endif

};
