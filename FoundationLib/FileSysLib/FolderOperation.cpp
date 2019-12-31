#include "stdafx.h"

#include "FolderOperation.h"
#include <vector>
using namespace std;


CFolderOperation::CFolderOperation(void)
{
}

CFolderOperation::~CFolderOperation(void)
{
}

// 判断文件夹是否存在
BOOL CFolderOperation::isFolderExist(CString strPath)
{
    DWORD dwAttr;  
    dwAttr = GetFileAttributes(strPath);  
    if(dwAttr == -1L) //pszDir所指目标不存在
        return FALSE; 
    if(dwAttr & FILE_ATTRIBUTE_DIRECTORY) //pszDir所指目标是文件夹
        return TRUE; 
    return FALSE;//pszDir所指目标是文件
}


// 创建文件夹
BOOL CFolderOperation::createDir(CString strPath)
{   
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
	return ::CreateDirectory( strPath, &attrib);
}

// 创建多级目录
BOOL CFolderOperation::createDirEx(const CString& szPath)
{
	CString strDir(szPath);//存放要创建的目录字符串
	//确保以'\'结尾以创建最后一个目录
	if (strDir.GetAt(strDir.GetLength()-1)!='\\')
	{
		strDir+='\\';
	}
	vector<CString> vpath;//存放每一层目录字符串
	CString strTemp;//一个临时变量,存放目录字符串
	//遍历要创建的字符串
	for (int i=0;i<strDir.GetLength();++i)
	{
		if (strDir.GetAt(i) != '\\') 
		{//如果当前字符不是'\\'
			strTemp+=(strDir.GetAt(i));
		}
		else 
		{//如果当前字符是'\\'
			vpath.push_back(strTemp);//将当前层的字符串添加到数组中
			strTemp+=('\\');
		}
	}

	//遍历存放目录的数组,创建每层目录
	BOOL bSuccess = TRUE;//成功标志
	for (int j=0;j<(int)vpath.size();j++) 
	{
		//如果CreateDirectory执行成功,返回true,否则返回false
		CString path=vpath[j];
		if(!isFolderExist(path))
			bSuccess &= createDir(path);
	}

	return bSuccess;
}

CString CFolderOperation::getFolderFromFullPath( CString fullPath )
{
	return fullPath.Left(fullPath.ReverseFind('\\'));
}

// 获取程序所在当前路径
CString CFolderOperation::GetModulePath(HINSTANCE instance)
{
// 	TCHAR path[MAX_PATH*10];
// // 	::GetModuleFileName(AfxGetInstanceHandle(),path,MAX_PATH*10);
// 	::GetModuleFileName(NULL,path,MAX_PATH*10);
// 	CString strTemp = _T("");
// 	CString strLocalPath = _T("");
// 	strTemp.Format("%s",path);
	CString strTemp = GetModuleFullPath();
	CString strLocalPath = _T("");
	strLocalPath = getFolderFromFullPath(strTemp);
	return strLocalPath;
}

// 带文件名的全路径
CString CFolderOperation::GetModuleFullPath(HINSTANCE instance)
{
	TCHAR path[MAX_PATH*10];
	// 	::GetModuleFileName(AfxGetInstanceHandle(),path,MAX_PATH*10);
	::GetModuleFileName(instance,path,MAX_PATH*10);
	CString strTemp = _T("");
	strTemp.Format(TEXT("%s"),path);
	return strTemp;

// 	TCHAR moduleName[MAX_PATH] = {0}; 
// 	GetModuleFileName(instance,moduleName,MAX_PATH); 
// 	TCHAR _strLongPath[MAX_PATH] = _T("\0");
// 	::GetLongPathName(moduleName, _strLongPath, MAX_PATH);
// 	CString strPath(_strLongPath);
// 	return strPath;
}

// 获取模块路径
CString CFolderOperation::getOcxPath(COleControlModule *module)
{
	if(!module)
		return TEXT("");

	return getFolderFromFullPath(module->m_pszHelpFilePath);
}

// 给文件夹最后添加"\"
CString CFolderOperation::addGang(CString path)
{
	if(path.GetLength()<=0)
#ifdef _UNICODE
		return L"";
#else
		return "";
#endif

#ifdef _UNICODE
	if (path.Right(1) != L'\\')
	{
		return path + L"\\";
	}
#else
	char *ch=(LPTSTR)(LPCSTR)path.Right(1);
	if(ch[0]!='\\')
	{
		return path + "\\";
	}
#endif

	return path;
}

// 去掉相对路径左面的"\"或"/"
CString CFolderOperation::removeLeftGang(CString path)
{
	if(path.GetLength()<=0)
		return TEXT("");

#ifdef _UNICODE
	if(path.Left(1)==L"/" || path.Left(1)==L"\\")
		return path.Right(path.GetLength() - 1);
#else
	char *ch=(LPTSTR)(LPCSTR)path.Left(1);
	if(ch[0]=='/' || ch[0]=='\\')
		return path.Right(path.GetLength()-1);
#endif
	return path;
}

string CFolderOperation::getSystemDrive()
{
	TCHAR path[MAX_PATH*10];
	::GetWindowsDirectory(path,MAX_PATH*10);
	path[2]=TEXT('\0');
	CString systemDrive=path;
	return (LPCSTR)systemDrive.GetBuffer(systemDrive.GetLength());
}

// 获取 Windows 临时文件夹目录
CString CFolderOperation::getTempFolder()
{
#if _MSC_VER<=1200  // vc6.0 or lower
	return getenv(TEXT("TEMP"));
#else
#ifdef _UNICODE
#else
	char* env = NULL;
	size_t n = 0;
	errno_t ret = _dupenv_s(&env, &n, "TEMP");
	if (!ret)
		return TEXT("");

	CString envval = env;
	free(env);
	return envval;
#endif
#endif
}

// 获取指定目录下的一级子目录列表
void CFolderOperation::getSubFolders(CString folder, CStringArray &subFolders, CString filter, BOOL clearSubFoldersArray)
{
#ifdef _UNICODE
#else
	if(folder.GetLength()<=0)
		folder=".";

	if(!isFolderExist(folder))
		return;

	if (clearSubFoldersArray)
		subFolders.RemoveAll();

	WIN32_FIND_DATA   wfd;
	
	HANDLE hFind = FindFirstFile(addGang(folder)+filter, &wfd);
	do
	{
		if((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			CString fileName=wfd.cFileName;
			char *ch=(LPTSTR)(LPCSTR)fileName;
			// 不是 "."，也不是 ".."
			if(ch[0]!='.' || (ch[0]=='.' && ch[1]!='.'))
				subFolders.Add(fileName);
		}
	}
	while(FindNextFile(hFind,&wfd));

	FindClose(hFind);
#endif
}

// 分解文件路径为文件夹和文件名
void CFolderOperation::parsePath(CString path, CString &folder, CString &file)
{
	if(path.GetLength()<=0)
	{
		folder="";
		file="";
		return;
	}

	int pos=path.ReverseFind('\\');
	if(pos<=0)
	{
		// 只有文件名
		folder="";
		file=path;
		return;
	}

	if(pos==path.GetLength()-1)
	{
		// 没有文件名
		folder=path;
		file="";
		return;
	}

	folder = path.Left(pos);
	file=path.Right(path.GetLength()-pos-1);
}

// 删除文件夹
BOOL CFolderOperation::removeFolder(CString folder)
{
	CFileFind tempFind;
	CString tempFileFind;
	tempFileFind.Format(TEXT("%s\\*.*"),folder);
	BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();
		if(!tempFind.IsDots())
		{
			CString foundFileName=tempFind.GetFileName();
			if(tempFind.IsDirectory())
			{
				CString tempDir;
				tempDir.Format(TEXT("%s\\%s"),folder,foundFileName);
				SetFileAttributes(tempDir, FILE_ATTRIBUTE_NORMAL);
				// 删除 tempDir 内部的文件和文件夹
				removeFolder(tempDir);
				// 删除 tempDir 文件夹本身
				RemoveDirectory(tempDir);
			}
			else
			{
				CString tempFileName;
				tempFileName.Format(TEXT("%s\\%s"),folder,foundFileName);
				SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);
				DeleteFile(tempFileName);
			}
		}
	}
	tempFind.Close();
	if(!RemoveDirectory(folder))
		return FALSE;

	return TRUE;

	// 下面的代码只能删除非空目录

	//if(RemoveDirectory(folder))
	//	return TRUE;
	//else
	//	return FALSE;

	// 下面代码在窗体未创建之前好像调用不成功

//	SHFILEOPSTRUCT FileOp={0};
//	FileOp.fFlags = // FOF_ALLOWUNDO |   //允许放回回收站
//		FOF_NO_UI;          // 不出现任何 UI 界面
//// 		FOF_NOCONFIRMATION; //不出现确认对话框
//	FileOp.pFrom = (LPCSTR)folder;
//	FileOp.pTo = NULL;      //一定要是NULL
//	FileOp.wFunc = FO_DELETE;    //删除操作
//
//	if(SHFileOperation(&FileOp) == 0)
//		return TRUE;
//	else
//		return FALSE;
}
