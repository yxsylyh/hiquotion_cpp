#pragma once
#include <afxctl.h>
#include <string>

class CFolderOperation
{
public:
	CFolderOperation(void);
	~CFolderOperation(void);

	// 判断文件夹是否存在
	static BOOL isFolderExist(CString strPath);

	// 创建文件夹
	static BOOL createDir(CString strPath);

	// 创建多级目录
	static BOOL createDirEx(const CString& szPath);

	// 从全路径名中获取文件所在路径
	static CString getFolderFromFullPath(CString fullPath);

	// 获取程序所在当前路径
	static CString GetModulePath(HINSTANCE instance=NULL);

	// 带文件名的全路径
	static CString GetModuleFullPath(HINSTANCE instance=NULL);

	// 获取模块路径
	static CString getOcxPath(COleControlModule *module);

	// 给文件夹最后添加"\"
	static CString addGang(CString path);
	// 去掉相对路径左面的"\"或"/"
	static CString removeLeftGang(CString path);

	// 获取系统所在驱动
	static std::string getSystemDrive();

	// 获取 Windows 临时文件夹目录
	static CString getTempFolder();

	// 获取指定目录下的一级子目录列表
	static void getSubFolders(CString folder, CStringArray &subFolders, CString filter=
#ifdef _UNICODE
		L"*.*", BOOL clearSubFoldersArray = TRUE);
#else
		"*.*", BOOL clearSubFoldersArray = TRUE);
#endif

	// 分解文件路径为文件夹和文件名
	static void parsePath(CString path, CString &folder, CString &file);

	// 删除文件夹
	static BOOL removeFolder(CString folder);
};
