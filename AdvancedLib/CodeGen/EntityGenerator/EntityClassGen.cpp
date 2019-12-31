// EntityClassGen.cpp: implementation of the CEntityClassGen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EntityGenerator.h"
#include "EntityClassGen.h"
#include <C++\FoudationLib\StringExtLib\StringExt.h>
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>
#include <C++\FoudationLib\FileSysLib\FileOperation.h>
#include "TypeValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntityClassGen::CEntityClassGen()
{

}

CEntityClassGen::CEntityClassGen( CString className, BOOL isIncludeStdAfx )
: m_classname(className), m_isIncludeStdAfx(isIncludeStdAfx)
{
	
}

CEntityClassGen::~CEntityClassGen()
{

}

int CEntityClassGen::genInclude( CString includeList )
{
	if(includeList.GetLength()<=0)
		return 0;

	m_include.RemoveAll();
	CStringExt::Split(includeList, m_include, "\r\n");
	if(m_include.GetSize()<=0)
		return -1;  // 有问题了

	return 0;
}

int CEntityClassGen::genProperty( CString propertyList )
{
	if(propertyList.GetLength()<=0)
		return 0;

	CStringArray lst;
	CStringExt::Split(propertyList, lst, "\r\n");
	if(lst.GetSize()<=0)
		return -1;  // 有问题了

	m_propertyList.destroyAll();
	m_propertyList.clear();

	for(int i=0;i<lst.GetSize();i++)
	{
		CString item=lst.GetAt(i);
		if(item.GetLength()<=0)
			continue;

		CStringArray itemList;
		CStringExt::Split(item, itemList, ",");
		if(itemList.GetSize()<=0)
			continue;

		CString name=itemList.GetAt(0);
		CString type, /*scope, */defaultValue;

		// 默认的类型是整型
		if(itemList.GetSize()<=1)
		{
			type="int";
// 			scope="public";
			defaultValue=CTypeValue::getDefaultValue(type);
		}
		else if(itemList.GetSize()<=2)
		{
			if(itemList.GetAt(1).GetLength()<=0)
				type="int";
			else
				type=itemList.GetAt(1);

// 			scope="public";
			defaultValue=CTypeValue::getDefaultValue(type);
		}
// 		else if(itemList.GetSize()<=3)
// 		{
// 			if(itemList.GetAt(1).GetLength()<=0)
// 				type="int";
// 			else
// 				type=itemList.GetAt(1);
// 			
// // 			if(itemList.GetAt(2).GetLength()<=0)
// // 				scope="public";
// // 			else
// // 				scope=itemList.GetAt(2);
// 			
// 			defaultValue=CTypeValue::getDefaultValue(type);
// 		}
		else
		{
			if(itemList.GetAt(1).GetLength()<=0)
				type="int";
			else
				type=itemList.GetAt(1);
			
// 			if(itemList.GetAt(2).GetLength()<=0)
// 				scope="public";
// 			else
// 				scope=itemList.GetAt(2);
			
			if(itemList.GetAt(2).GetLength()<=0)
				defaultValue=CTypeValue::getDefaultValue(type);
			else
				defaultValue=itemList.GetAt(2);
		}

		CClassProperty *prop=new CClassProperty(name, type, defaultValue);
		m_propertyList.push_back(prop);
	}

	return 0;
}

CString CEntityClassGen::genHeadFileCode(CString filename)
{
// #define FILENAME_H

	CString def=filename;
	def.MakeUpper();
	CString src="#ifndef " + def + "_H" + "\r\n";
	src+="#define " + def + "_H" + "\r\n\r\n";

// #if _MSC_VER > 1000
// #pragma once
// #endif // _MSC_VER > 1000

	src+="#if _MSC_VER > 1000\r\n";
	src+="#pragma once\r\n";
	src+="#endif // _MSC_VER > 1000\r\n";

	// 生成 #include

	CString incld;
	if(m_include.GetSize()>0)
	{
		for(int i=0;i<m_include.GetSize();i++)
		{
			incld+="#include " + m_include.GetAt(i) + "\r\n";
		}

		src+=incld + "\r\n";
	}

	// 生成类名

	src+="class " + m_classname + "\r\n";
	src+="{\r\n";

	// 生成 public
	src+="public:\r\n";

	{
		// 生成构造函数和析构函数

		src+="\t";
		src+=genDefaultConstructDeclareCode() + ";\r\n";

		if(m_propertyList.size()>0)
		{
			src+="\t";
			src+=genConstructDeclareCode() + ";\r\n";
		}
		
		src+="\t";
		src+=genDeconstructCode() + "\r\n";

		src+="\r\n";

		// 生成 get, set 方法
		for(int i=0;i<m_propertyList.size();i++)
		{
			CClassProperty *prop=m_propertyList.at(i);
			if(!prop)
				continue;

			src+="\t";
			src+=prop->genGetCode() + "\r\n";

			src+="\t";
			src+=prop->genSetCode() + "\r\n";

			src+="\r\n";
		}
	}

	src+="\r\n";

	// 生成 private
	src+="private:\r\n";

	{
		// 生成内部变量

		for(int i=0;i<m_propertyList.size();i++)
		{
			CClassProperty *prop=m_propertyList.at(i);
			if(!prop)
				continue;
			
			src+="\t";
			src+=prop->genDeclareCode() + "\r\n";
		}
		
		src+="\r\n";
	}

	src+="}\r\n";

	src+="\r\n";

	src+="#endif // " + def + "_H";

	src+="\r\n";
	
	return src;
}

CString CEntityClassGen::genImplementFileCode(CString filename)
{
	CString src;

	// #include "StdAfx.h"
	if(m_isIncludeStdAfx)
		src+="#include \"StdAfx.h\"\r\n";
	// #include 类名.h
	src+="#include \"" + filename + ".h\"\r\n";

	// 构造函数实现
	src+="\r\n";
	src+=genDefaultConstructCode();

	src+="\r\n";
	src+=genConstructCode();

	return src;
}

int CEntityClassGen::genFile( CString filename )
{
	if(filename.GetLength()<=0)
		return -1;

	// 创建 src 目录
	CString folder=CFolderOperation::addGang(CFolderOperation::GetModulePath())+"src";
	if(!CFolderOperation::isFolderExist(folder))
		CFolderOperation::createDir(folder);

	if(!CFolderOperation::isFolderExist(folder))
		return -2;

	CString headFile=CFolderOperation::addGang(folder)+filename+".h";
	CString implFile=CFolderOperation::addGang(folder)+filename+".cpp";

	// 删除已经存在的文件
	if(CFileOperation::isFileExist(headFile))
		DeleteFile(headFile);

	if(CFileOperation::isFileExist(headFile))
		return -3;

	// 删除已经存在的文件
	if(CFileOperation::isFileExist(implFile))
		DeleteFile(implFile);

	if(CFileOperation::isFileExist(implFile))
		return -4;

	// 打开文件，并写入数据
	CFile file;
	if(!file.Open(headFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
		return -5;

	CString src=genHeadFileCode(filename);
	file.Write(src.GetBuffer(src.GetLength()), src.GetLength());
	file.Close();

	// 打开文件，并写入数据
	if(!file.Open(implFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
		return -6;
	
	src=genImplementFileCode(filename);
	file.Write(src.GetBuffer(src.GetLength()), src.GetLength());
	file.Close();

	return 0;
}

CString CEntityClassGen::genDefaultConstructDeclareCode()
{
	return m_classname + "()";
}

CString CEntityClassGen::genConstructDeclareCode()
{
	CString src=m_classname + "(";
	CString para;
	if(m_propertyList.size()>0)
	{
		CClassProperty *prop=m_propertyList.at(0);
		if(prop)
			para+=prop->genFunctionParaCode();
	}

	for(int i=1;i<m_propertyList.size();i++)
	{
		CClassProperty *prop=m_propertyList.at(i);
		if(prop)
		{
			if(para.GetLength()<=0)
				para+=prop->genFunctionParaCode();
			else
			{
				para+=", ";
				para+=prop->genFunctionParaCode();
			}
		}
	}

	src+=para + ")";

	return src;
}

CString CEntityClassGen::genDefaultConstructCode()
{
	CString src=m_classname + "::" + genDefaultConstructDeclareCode() + "\r\n";
	src+=": ";

	CString code;
	if(m_propertyList.size()>0)
	{
		CClassProperty *prop=m_propertyList.at(0);
		if(prop)
			code+=prop->genConstructInitDefaltCode();
	}

	for(int i=1;i<m_propertyList.size();i++)
	{
		CClassProperty *prop=m_propertyList.at(i);
		if(prop)
		{
			if(code.GetLength()<=0)
				code+=prop->genConstructInitDefaltCode();
			else
			{
				code+=", ";
				code+=prop->genConstructInitDefaltCode();
			}
		}
	}

	src+=code;
	src+="\r\n";
	src+="{\r\n";
	src+="}\r\n";
	src+="\r\n";

	return src;
}

CString CEntityClassGen::genConstructCode()
{
	CString src=m_classname + "::" + genConstructDeclareCode() + "\r\n";
	src+=": ";
	
	CString code;
	if(m_propertyList.size()>0)
	{
		CClassProperty *prop=m_propertyList.at(0);
		if(prop)
			code+=prop->genConstructInitCode();
	}
	
	for(int i=1;i<m_propertyList.size();i++)
	{
		CClassProperty *prop=m_propertyList.at(i);
		if(prop)
		{
			if(code.GetLength()<=0)
				code+=prop->genConstructInitCode();
			else
			{
				code+=", ";
				code+=prop->genConstructInitCode();
			}
		}
	}
	
	src+=code;
	src+="\r\n";
	src+="{\r\n";
	src+="}\r\n";
	src+="\r\n";

	return src;
}

CString CEntityClassGen::genDeconstructCode()
{
	return "virtual ~" + m_classname + "(){};";
}
