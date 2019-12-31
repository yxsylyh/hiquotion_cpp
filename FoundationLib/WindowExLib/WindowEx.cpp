#include "stdafx.h"
#include "WindowEx.h"
#include <C++\FoundationLib\StringExtLib\StringExt.h>

CWindowEx::CWindowEx(void)
{
}

CWindowEx::~CWindowEx(void)
{
}

// windowPath 格式
// class:text/class:text/class:text/ ...
// 如果class或text没有，请保持空，但冒号不能省略
HWND CWindowEx::findWindow(HWND parent, CString windowPath)
{
	CStringArray array;
	CStringExt::Split(windowPath, array, "/");
	if(array.GetSize()<=0)
		return NULL;

	return findWindow(parent, array, 0);
}

HWND CWindowEx::findWindow(HWND parent, CStringArray &windowFolder, int deepLevel)
{
	CString folder=windowFolder.GetAt(deepLevel);
	CStringArray array;
	CStringExt::Split(folder, array, ":");
	if(array.GetSize()<2)
		return NULL;

	CString cls=array.GetAt(0);
	CString txt=array.GetAt(1);
// 	HWND hwnd=::FindWindowEx(parent, NULL, cls, txt);
	HWND hwnd=doOsApiFindWindowEx(parent, NULL, cls, txt);
	if(!hwnd)
		return NULL;

	if(deepLevel==windowFolder.GetSize()-1)
		return hwnd;

	while(hwnd)
	{
		HWND found=findWindow(hwnd, windowFolder, deepLevel+1);
		if(found)
			return found;

		return NULL;

// 		hwnd=::FindWindowEx(parent, hwnd, cls, txt);
		// 下面的代码会使程序陷入死循环
		hwnd=doOsApiFindWindowEx(parent, NULL, cls, txt);
	}

	return NULL;
}

HWND CWindowEx::doOsApiFindWindow( CString wndClass, CString title )
{
	HWND hwnd=NULL;
	if(title.GetLength()>0 && wndClass.GetLength()>0)
		hwnd=::FindWindow(wndClass, title);
	else if(title.GetLength()>0 && wndClass.GetLength()<=0)
		hwnd=::FindWindow(NULL, title);
	else if(title.GetLength()<=0 && wndClass.GetLength()>0)
		hwnd=::FindWindow(wndClass, NULL);

	return hwnd;
}

HWND CWindowEx::doOsApiFindWindowEx( HWND hWndParent, HWND hWndChildAfter, CString wndClass, CString title )
{
	HWND hwnd=NULL;
	if(title.GetLength()>0 && wndClass.GetLength()>0)
		hwnd=::FindWindowEx(hWndParent, hWndChildAfter, wndClass, title);
	else if(title.GetLength()>0 && wndClass.GetLength()<=0)
		hwnd=::FindWindowEx(hWndParent, hWndChildAfter, NULL, title);
	else if(title.GetLength()<=0 && wndClass.GetLength()>0)
		hwnd=::FindWindowEx(hWndParent, hWndChildAfter, wndClass, NULL);

	return hwnd;
}
