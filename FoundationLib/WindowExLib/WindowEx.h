#pragma once

/*

使用方法
	先用Windows API的FindWindow找到其窗口指针（参数是类名字符串和窗口名字符串，不指定的，用NULL）
	然后利用窗口指针中的窗口句柄作为第一参数，来调用findWindow，第二参数为第一参数的子窗口所在的“路径”

	窗口路径的定义是这样的：
	class:text/class:text/class:text/ ...	如果class或text没有，请保持空，但冒号不能省略

*/
class CWindowEx
{
public:
	CWindowEx(void);
	~CWindowEx(void);

	static HWND findWindow(HWND parent, CString windowPath);
	static HWND doOsApiFindWindow(CString wndClass, CString title);
	static HWND doOsApiFindWindowEx(HWND hWndParent, HWND hWndChildAfter, CString wndClass, CString title);

private:
	static HWND findWindow(HWND parent, CStringArray &windowFolder, int deepLevel);
};
