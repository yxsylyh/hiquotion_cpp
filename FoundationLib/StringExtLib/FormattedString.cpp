// FormattedString.cpp: implementation of the CFormattedString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FormattedString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormattedString::CFormattedString()
{

}

CFormattedString::~CFormattedString()
{

}

std::string CFormattedString::formatString(char *msg, ...)
{
	char s[1000];
	memset(s, 0x00, 1000);
	va_list ap;
	int n=0,size=1000;
	va_start(ap, msg); //获得可变参数列表,分析fmt，得出各个参数的类型，也是分析参数中类似”%d%s“的字符串
	n=_vsnprintf(s, size, msg, ap); //写入字符串s
	va_end(ap); //释放资源,必须与va_start成对调用
	std::string str=s;
	return str;
}
