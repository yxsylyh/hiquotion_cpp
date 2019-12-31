// EntityClassGen.h: interface for the CEntityClassGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITYCLASSGEN_H__B9A1DC1B_64B9_49E4_AB29_4AB4514F52E1__INCLUDED_)
#define AFX_ENTITYCLASSGEN_H__B9A1DC1B_64B9_49E4_AB29_4AB4514F52E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerList.h>
#include "ClassProperty.h"

class CEntityClassGen  
{
public:
	CEntityClassGen();
	CEntityClassGen(CString className, BOOL isIncludeStdAfx=TRUE);
	virtual ~CEntityClassGen();

	int genInclude(CString includeList);
	int genProperty(CString propertyList);

	CString genHeadFileCode(CString filename);
	CString genImplementFileCode(CString filename);
	
	int genFile(CString filename);

	CString genDefaultConstructDeclareCode();  // 生成默认构造函数的声明代码
	CString genConstructDeclareCode(); // 生成构造函数的声明代码
	CString genDefaultConstructCode();  // 生成默认构造函数代码，初始化所有变量为默认值
	CString genConstructCode(); // 生成构造函数代码，同时初始化所有变量为传入参数
	CString genDeconstructCode();  // 生成析构函数

	CString getClassname() const { return m_classname; }
	void setClassname(CString val) { m_classname = val; }

// 	CString getFilename() const { return m_filename; }
// 	void setFilename(CString val) { m_filename = val; }

private:
	CString m_classname;
	CStringArray m_include;
	CPointerList<CClassProperty *> m_propertyList;
// 	CString m_filename;

	BOOL m_isIncludeStdAfx;
};

#endif // !defined(AFX_ENTITYCLASSGEN_H__B9A1DC1B_64B9_49E4_AB29_4AB4514F52E1__INCLUDED_)
