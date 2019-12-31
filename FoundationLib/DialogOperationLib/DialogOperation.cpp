#include "StdAfx.h"
#include "DialogOperation.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>

CDialogOperation::CDialogOperation(void)
{
}

CDialogOperation::~CDialogOperation(void)
{
}

// 打开文件对话框
// 返回值：TRUE，选择了文件；FALSE，取消了
// BOOL CFileDialogOperation::openFileDialog(CString &fileName, HWND hwnd, CString title, CString filter, CString defaultFileName, CString defaultExt, DWORD flag)
BOOL CDialogOperation::openFileDialog(CString &fileName, CWnd *hwnd, CString filter, CString defaultExt, CString defaultFileName, CString title, DWORD flag)
{
	CFileDialog openDlg(TRUE, defaultExt, defaultFileName, flag, filter, hwnd);
	openDlg.m_ofn.lpstrTitle=title;
	if(openDlg.DoModal()==IDOK)
	{
		fileName=openDlg.GetPathName();
		return TRUE;
	}
	return FALSE;

}

// 打开文件对话框（文件多选）
// 返回值：TRUE，选择了文件；FALSE，取消了
BOOL CDialogOperation::openMultiFilesDialog(CStringArray &fileNames, CWnd *hwnd, CString filter, CString defaultExt, CString defaultFileName, CString title, DWORD flag)
{
	CFileDialog openDlg(TRUE, defaultExt, defaultFileName, flag|OFN_ALLOWMULTISELECT, filter, hwnd);
	openDlg.m_ofn.lpstrTitle=title;
	if(openDlg.DoModal()==IDOK)
	{
		POSITION pos=openDlg.GetStartPosition();
		while(pos)
		{
			CString name=openDlg.GetNextPathName(pos);
			fileNames.Add(name);
		}
		return TRUE;
	}
	return FALSE;
}

// 保存文件对话框
// 返回值：TRUE，选择了文件；FALSE，取消了
BOOL CDialogOperation::saveFileDialog(CString &fileName, CWnd *hwnd,  CString filter, CString defaultExt, CString defaultFileName, CString title, DWORD flag)
{
	CFileDialog openDlg(FALSE, defaultExt, defaultFileName, flag, filter, hwnd);
	openDlg.m_ofn.lpstrTitle=title;
	if(openDlg.DoModal()==IDOK)
	{
		fileName=openDlg.GetPathName();
		return TRUE;
	}
	return FALSE;
}

// 初始化打开目录对话框初始目录的回调函数
int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
       if(uMsg == BFFM_INITIALIZED)
       {
              SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
       }
       return 0; 
}

// 打开目录对话框
BOOL CDialogOperation::openFolderDlg(HWND hwnd,CString &folder,CString title, CString initFolder, BOOL sShowNewButton)
{
	CString sFolderPath;
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//初始化入口参数bi开始
	bi.hwndOwner = hwnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = "选择路径";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	if(sShowNewButton)  // 是否显示“新建文件夹”按钮
		bi.ulFlags |= BIF_USENEWUI;
	bi.lpfn = NULL;
	bi.iImage = 0;
	bi.lParam =0;
	bi.lpfn = NULL;
	if(initFolder.GetLength()>0)
	{
		if(CFolderOperation::isFolderExist(initFolder))
		{
			bi.lParam =(long)(initFolder.GetBuffer(initFolder.GetLength()));//初始化路径，形如(_T("c:\\Symbian"));
			bi.lpfn = BrowseCallbackProc;
		}
	}
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(!pIDList)
		return FALSE;

	SHGetPathFromIDList(pIDList, Buffer);
	//取得文件夹路径到Buffer里
	sFolderPath = Buffer;//将路径保存在一个CString对象里
	folder=sFolderPath;

	return TRUE;
}
