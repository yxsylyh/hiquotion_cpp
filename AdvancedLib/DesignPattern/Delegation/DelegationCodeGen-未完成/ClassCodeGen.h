// ClassCodeGen.h: interface for the CClassCodeGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSCODEGEN_H__A441C41C_DFCD_4F5E_BC3C_368AE45AB49E__INCLUDED_)
#define AFX_CLASSCODEGEN_H__A441C41C_DFCD_4F5E_BC3C_368AE45AB49E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICodeGen.h"

class CClassCodeGen : public ICodeGen  
{
public:
	CClassCodeGen(string classModifier, string className);
	virtual ~CClassCodeGen();

	string genCode(int indent);  // indent Ëõ½ø
};

#endif // !defined(AFX_CLASSCODEGEN_H__A441C41C_DFCD_4F5E_BC3C_368AE45AB49E__INCLUDED_)
