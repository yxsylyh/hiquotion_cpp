// ISimpleTest.h: interface for the ISimpleTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISIMPLETEST_H__0CBB2FC2_40C8_48B4_974A_5D5E624C5A08__INCLUDED_)
#define AFX_ISIMPLETEST_H__0CBB2FC2_40C8_48B4_974A_5D5E624C5A08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<class T>
class ISimpleTest  
{
public:
	ISimpleTest(){};
	virtual ~ISimpleTest(){};

	// 全局初始化
	virtual void globalInit(){};

	// 全局清理
	virtual void globalCleanup(){};

	// 测试用例初始化
	virtual T *testCaseInit()
	{
		return new T();
	}

	// 测试用例清理
	virtual void testCaseCleanup(T *t)
	{
		delete t;
	}

	// 开始测试
	virtual void startTest()
	{

	}
};

#endif // !defined(AFX_ISIMPLETEST_H__0CBB2FC2_40C8_48B4_974A_5D5E624C5A08__INCLUDED_)
