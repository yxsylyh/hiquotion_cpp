// ClassProperty.cpp: implementation of the CClassProperty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EntityGenerator.h"
#include "ClassProperty.h"
#include "TypeValue.h"
#include <C++\FoudationLib\StringExtLib\StringExt.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClassProperty::CClassProperty()
{

}

CClassProperty::CClassProperty( CString name, CString type, /*CString scope, */CString defaultValue )
:m_name(name), m_type(type), /*m_scope(scope), */m_default(defaultValue)
{
	
}

CClassProperty::~CClassProperty()
{

}

CString CClassProperty::genDeclareCode()
{
	return m_type + " m_" + m_name + ";";
}

CString CClassProperty::genFunctionParaCode()
{
	return m_type + " " + m_name;
}

CString CClassProperty::genConstructInitDefaltCode()
{
	return "m_" + m_name + "(" + m_default + ")";
}

CString CClassProperty::genConstructInitCode()
{
	return "m_" + m_name + "(" + m_name + ")";
}

CString CClassProperty::genGetCode()
{
	return m_type + " get" + CStringExt::capital(m_name) + "() { return m_" + m_name + "; }";
}

CString CClassProperty::genSetCode()
{
	return "void set" + CStringExt::capital(m_name) + "(" + m_type + " val) { m_" + m_name + "=val; }";
}
