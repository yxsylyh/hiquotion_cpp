#pragma once

#if _MSC_VER<=1200
#define BIF_NEWDIALOGSTYLE   0x40
#define BIF_USENEWUI (BIF_NEWDIALOGSTYLE|BIF_EDITBOX)
#endif

class CDialogOperation
{
public:
	CDialogOperation(void);
	~CDialogOperation(void);

	// 打开文件对话框
	// 返回值：TRUE，选择了文件；FALSE，取消了
// 	static BOOL openFileDialog(CString &fileName, HWND hwnd=NULL, CString title="打开", CString filter="*.*\0*.*\0\0", CString defaultFileName="", CString defaultExt="*.*", DWORD flag=OFN_FILEMUSTEXIST|OFN_HIDEREADONLY);
	static BOOL openFileDialog(CString &fileName, CWnd *hwnd=NULL, CString filter="所有文件(*.*)|*.*||", CString defaultExt="*.*", CString defaultFileName="", CString title="打开", DWORD flag=OFN_FILEMUSTEXIST|OFN_HIDEREADONLY);

	// 打开文件对话框（文件多选）
	// 返回值：TRUE，选择了文件；FALSE，取消了
	static BOOL openMultiFilesDialog(CStringArray &fileNames, CWnd *hwnd=NULL, CString filter="所有文件(*.*)|*.*||", CString defaultExt="*.*", CString defaultFileName="", CString title="打开（文件可多选）", DWORD flag=OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT);
	
	// 保存文件对话框
	// 返回值：TRUE，选择了文件；FALSE，取消了
	static BOOL saveFileDialog(CString &fileNames, CWnd *hwnd=NULL, CString filter="所有文件(*.*)|*.*||", CString defaultExt="", CString defaultFileName="", CString title="保存", DWORD flag=OFN_OVERWRITEPROMPT);

	// 打开目录对话框
	static BOOL openFolderDlg(HWND hwnd,CString &folder,CString title="选择路径", CString initFolder="", BOOL isShowNewButton=FALSE);

};
