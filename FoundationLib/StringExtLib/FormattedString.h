// FormattedString.h: interface for the CFormattedString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMATTEDSTRING_H__5B23918C_AF3B_460A_8848_7EC8BAE0F705__INCLUDED_)
#define AFX_FORMATTEDSTRING_H__5B23918C_AF3B_460A_8848_7EC8BAE0F705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class CFormattedString  
{
public:
	CFormattedString();
	virtual ~CFormattedString();

	static std::string formatString(char *msg, ...);
};

#endif // !defined(AFX_FORMATTEDSTRING_H__5B23918C_AF3B_460A_8848_7EC8BAE0F705__INCLUDED_)
