// Shortcut.cpp: implementation of the CShortcut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shortcut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShortcut::CShortcut()
{

}

CShortcut::~CShortcut()
{

}

BOOL CShortcut::createFileShortcut(LPCSTR lpszFileFullPath, LPCSTR lpszLnkFileDir, LPCSTR lpszLnkFileName, LPCSTR lpszArguments, LPCSTR lpszWorkDir, WORD wHotkey, LPCTSTR lpszDescription, int iShowCmd)
{
	if (lpszLnkFileDir == NULL)
		return FALSE;
	
	HRESULT hr;
	IShellLink     *pLink;  //IShellLink对象指针
	IPersistFile   *ppf; //IPersisFil对象指针
	
	//创建IShellLink对象
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
	if (FAILED(hr))
		return FALSE;
	
	//从IShellLink对象中获取IPersistFile接口
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
	if (FAILED(hr))
	{
		pLink->Release();
		return FALSE;
	}
	
	//目标
	if (lpszFileFullPath == NULL)
		pLink->SetPath(_pgmptr);
	else
		pLink->SetPath(lpszFileFullPath);
	
	//工作目录
	if (lpszWorkDir != NULL)
		pLink->SetWorkingDirectory(lpszWorkDir);

	// 参数
	if(lpszArguments!=NULL)
		pLink->SetArguments(lpszArguments);
	
	//快捷键
	if (wHotkey != 0)
		pLink->SetHotkey(wHotkey);
	
	//备注
	if (lpszDescription != NULL)
		pLink->SetDescription(lpszDescription);
	
	//显示方式
	pLink->SetShowCmd(iShowCmd);
	
	
	//快捷方式的路径 + 名称
	char szBuffer[MAX_PATH];
	if (lpszLnkFileName != NULL) //指定了快捷方式的名称
		sprintf(szBuffer, "%s\\%s", lpszLnkFileDir, lpszLnkFileName);
	else   
	{
		//没有指定名称，就从取指定文件的文件名作为快捷方式名称。
		char *pstr;
		if (lpszFileFullPath != NULL)
			pstr = strrchr(lpszFileFullPath, '\\');
		else
			pstr = strrchr(_pgmptr, '\\');
		
		if (pstr == NULL)
		{	
			ppf->Release();
			pLink->Release();
			return FALSE;
		}
		//注意后缀名要从.exe改为.lnk
		sprintf(szBuffer, "%s\\%s", lpszLnkFileDir, pstr);
		int nLen = strlen(szBuffer);
		szBuffer[nLen - 3] = 'l';
		szBuffer[nLen - 2] = 'n';
		szBuffer[nLen - 1] = 'k';
	}
	//保存快捷方式到指定目录下
	WCHAR  wsz[MAX_PATH];  //定义Unicode字符串
	MultiByteToWideChar(CP_ACP, 0, szBuffer, -1, wsz, MAX_PATH);
	
	hr = ppf->Save(wsz, TRUE);
	
	ppf->Release();
	pLink->Release();
	return SUCCEEDED(hr);
}
