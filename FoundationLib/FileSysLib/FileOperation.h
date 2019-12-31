// FileOperation.h: interface for the CFileOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPERATION_H__1D073143_EBBB_4F30_BFEE_94F75335B8A7__INCLUDED_)
#define AFX_FILEOPERATION_H__1D073143_EBBB_4F30_BFEE_94F75335B8A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileOperation  
{
public:
	CFileOperation();
	virtual ~CFileOperation();

	static void getFileNamesinFolder(CString folder,CString filter,CStringArray *files,BOOL isClearArray=TRUE);
	static void getFileNamesinFolderExt(CString folder,CStringArray *filters,CStringArray *files,BOOL isClearArray=TRUE);

	// 从指定目录获取所有指定扩展名的文件（包含子目录）列表
	// withFullFolder 指定返回列表中的每项，是包含全路径还是相对路径（默认是包含全路径）
	static void getFilesFromFolder(CString root,CString folder,CString filter,CStringArray *files, bool withFullFolder = true);

	// 从指定的全路径中获取文件夹和文件名
	static void getFileInfoFromPath(CString fullPath, CString &folder, CString &fileName);

	// 从全路径中获取文件名（带扩展名的）
	static CString getFileName(CString fullPath);

	static CString getFileNameNoExt(CString fileNameNoPath);

	// 针对已知名称和扩展名的文件，找到添加数字后缀的文件
	// 比如 abc.hit，则找到 abc_1.hit；123_4.ef，则找到123_5.ef 等等
	static CString GetFullFileNameNoExt(CString path,CString prefix,CString filter);

	static BOOL isFileExist(CString fileFullPath);

	static ULONGLONG getFileSize(CString fileFullPath);

	static CString getFileExtName(CString file);

	static CString getTempFileFullPath(CString folder, CString prefix=TEXT("tmp"));
};

#endif // !defined(AFX_FILEOPERATION_H__1D073143_EBBB_4F30_BFEE_94F75335B8A7__INCLUDED_)
