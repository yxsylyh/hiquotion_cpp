// ICodeGen.h: interface for the ICodeGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICODEGEN_H__55739D14_68EA_4640_8E55_C000C1ACBB3A__INCLUDED_)
#define AFX_ICODEGEN_H__55739D14_68EA_4640_8E55_C000C1ACBB3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class ICodeGen  
{
public:
	ICodeGen();
	virtual ~ICodeGen();

	virtual string genCode(int indent);  // indent Ëõ½ø

};

#endif // !defined(AFX_ICODEGEN_H__55739D14_68EA_4640_8E55_C000C1ACBB3A__INCLUDED_)
