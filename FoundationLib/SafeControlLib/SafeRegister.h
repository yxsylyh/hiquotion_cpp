#pragma once

/*

	使用方法

	1、在 控件名称.cpp 的 const GUID CDECL BASED_CODE _tlid = 定义下面添加如下定义（VS2010 在这个定义下 const GUID CDECL _tlid）

	const CATID CLSID_SafeItem =
			{ 0x5ded544d, 0xaf, 0x44fb, { 0x9f, 0xf1, 0xa, 0x1, 0xf5, 0x19, 0x26, 0xba } };

	其中的 Class ID 是在 控件名称Ctrl.cpp 中 IMPLEMENT_OLECREATE_EX 定义的那个，再添加上括号（上面的只是一个示例）

	2、在 控件名称.cpp 中替换 DllRegister 方法内容为

		return CSafeRegister::registerServer(_tlid, CLSID_SafeItem, CATID_SafeForInitializing, CATID_SafeForScripting);

		【建议保留最前面的 AFX_MANAGE_STATE(_afxModuleAddrThis);】

	3、在 控件名称.cpp 中替换 DllUnregister 方法内容为

		return CSafeRegister::unregisterServer(_tlid, CLSID_SafeItem, CATID_SafeForInitializing, CATID_SafeForScripting, _wVerMajor, _wVerMinor);

		【建议保留最前面的 AFX_MANAGE_STATE(_afxModuleAddrThis);】

	4、编译通过即可

*/

#include "comcat.h"
#include "Objsafe.h"

class CSafeRegister
{
public:
	CSafeRegister(void);
	~CSafeRegister(void);

	static HRESULT registerServer(GUID _tlid, GUID CLSID_SafeItem, CATID CATID_SafeForInitializing, CATID CATID_SafeForScripting);
	static HRESULT unregisterServer(GUID _tlid, GUID CLSID_SafeItem, CATID CATID_SafeForInitializing, CATID CATID_SafeForScripting, WORD _wVerMajor, WORD _wVerMinor);
};
