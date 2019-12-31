// Shortcut.h: interface for the CShortcut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHORTCUT_H__0C471C15_2FB6_456E_8AA7_2428A610B6CB__INCLUDED_)
#define AFX_SHORTCUT_H__0C471C15_2FB6_456E_8AA7_2428A610B6CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShortcut  
{
public:
	CShortcut();
	virtual ~CShortcut();

	/*

	特别说明：调用前需要调用
	
	CoInitialize(NULL);
	
	调用之后需要调用

	CoUninitialize();

	这两个语句可以在程序加载和程序退出时分别调用。

	**************

	函数功能：对指定文件在指定的目录下创建其快捷方式

	函数参数：
	lpszFileFullPath    指定文件，为NULL表示当前进程的EXE文件。
	lpszLnkFileDir  指定目录，不能为NULL。
	lpszLnkFileName 快捷方式名称，为NULL表示EXE文件名（.EXE会用.LNK替换）。
	wHotkey         为0表示不设置快捷键
	pszDescription  备注
	iShowCmd        运行方式，默认为常规窗口

    快捷键说明：
  低位上是virtual key code，高位上可以是ALT,CTRL等组合键。可以用MAKEWORD(low, high)来生成一个WORD，如Ctrl+F12可以用MAKEWORD(VK_F12, HOTKEYF_CONTROL)表示、
  
	ALT,CTRL等组合键：
  HOTKEYF_ALT       ALT key 
  HOTKEYF_CONTROL   CTRL key 
  HOTKEYF_EXT       Extended key 
  HOTKEYF_SHIFT     SHIFT key 

	*/
	static BOOL createFileShortcut(LPCSTR lpszFileFullPath, LPCSTR lpszLnkFileDir, LPCSTR lpszLnkFileName="", LPCSTR lpszArguments="", LPCSTR lpszWorkDir="", WORD wHotkey=0, LPCTSTR lpszDescription="", int iShowCmd = SW_SHOWNORMAL);
};

#endif // !defined(AFX_SHORTCUT_H__0C471C15_2FB6_456E_8AA7_2428A610B6CB__INCLUDED_)
