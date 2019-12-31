// ClassProperty.h: interface for the CClassProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSPROPERTY_H__7151F377_8E51_4CD4_A045_20EE00793FB9__INCLUDED_)
#define AFX_CLASSPROPERTY_H__7151F377_8E51_4CD4_A045_20EE00793FB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClassProperty  
{
public:
	CClassProperty();
	CClassProperty(CString name, CString type, /*CString scope, */CString defaultValue);
	virtual ~CClassProperty();

	CString genDeclareCode();      // 生成声明代码
	CString genFunctionParaCode();      // 生成函数参数代码
	CString genConstructInitDefaltCode();    // 生成构造函数中初始化的代码
	CString genConstructInitCode();    // 生成构造函数中初始化的代码
	CString genGetCode();       // 生成 get 代码
	CString genSetCode();       // 生成 set 代码

	CString getName() const { return m_name; }
	void setName(CString val) { m_name = val; }

	CString getType() const { return m_type; }
	void setType(CString val) { m_type = val; }

// 	CString getScope() const { return m_scope; }
// 	void setScope(CString val) { m_scope = val; }

	CString getDefault() const { return m_default; }
	void setDefault(CString val) { m_default = val; }

private:
	CString m_name;     // 变量名
	CString m_type;     // 变量类型
// 	CString m_scope;    // 作用范围
	CString m_default;  // 变量默认值
};

#endif // !defined(AFX_CLASSPROPERTY_H__7151F377_8E51_4CD4_A045_20EE00793FB9__INCLUDED_)
