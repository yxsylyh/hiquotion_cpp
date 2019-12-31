# 安全控件类库

为 ocx 控件添加安全接口的类库。

## 	使用方法
0.新建控件工程，继承 Static
  
高级中选择：无窗口激活、优化的绘图

1.在 控件名称.cpp 的 const GUID CDECL BASED_CODE _tlid = 定义下面添加如下定义（VS2010 在这个定义下 const GUID CDECL _tlid）
  
```java
const CATID CLSID_SafeItem =
  { 0x5ded544d, 0xaf, 0x44fb, { 0x9f, 0xf1, 0xa, 0x1, 0xf5, 0x19, 0x26, 0xba } };
```
  
其中的 Class ID 是在 控件名称Ctrl.cpp 中 IMPLEMENT_OLECREATE_EX 定义的那个，再添加上括号（上面的只是一个示例）

2.在 控件名称.cpp 中替换 DllRegister 方法内容为
  
```java
return CSafeRegister::registerServer(_tlid, CLSID_SafeItem, CATID_SafeForInitializing, CATID_SafeForScripting);
```
  
【建议保留最前面的 AFX_MANAGE_STATE(_afxModuleAddrThis);】

3.在 控件名称.cpp 中替换 DllUnregister 方法内容为
  
```java
return CSafeRegister::unregisterServer(_tlid, CLSID_SafeItem, CATID_SafeForInitializing, CATID_SafeForScripting, _wVerMajor, _wVerMinor);
```
  
【建议保留最前面的 AFX_MANAGE_STATE(_afxModuleAddrThis);】

4.编译通过即可
