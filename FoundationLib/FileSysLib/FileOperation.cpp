// FileOperation.cpp: implementation of the CFileOperation class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

#include "FileOperation.h"
#include "FolderOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOperation::CFileOperation()
{

}

CFileOperation::~CFileOperation()
{

}

void CFileOperation::getFileNamesinFolder(CString folder,CString filter,CStringArray *files,BOOL isClearArray)
{
	if(!files)
		return;
	
	if (isClearArray)
		files->RemoveAll();

	CFileFind sFinder;
#ifdef _UNICODE
	CString strFile = L"", strFileFound = L"";
	strFile.Format(L"%s%s", CFolderOperation::addGang(folder), filter);
#else
	CString strFile = "", strFileFound = "";
	strFile.Format("%s%s", CFolderOperation::addGang(folder), filter);
#endif
	BOOL bFind = sFinder.FindFile(strFile);
	while(bFind)
	{
		bFind = sFinder.FindNextFile();
		strFileFound = sFinder.GetFileName();
		files->Add(strFileFound);
	}
	sFinder.Close();
}

void CFileOperation::getFileNamesinFolderExt(CString folder,CStringArray *filters,CStringArray *files,BOOL isClearArray)
{
	if(!filters)
		return;

	if(!files)
		return;

	if(isClearArray)
		files->RemoveAll();

	for(int i=0;i<filters->GetSize();i++)
	{
		CString filter=filters->GetAt(i);
		if(filter.GetLength()<=0)
			continue;

		getFileNamesinFolder(folder, filter, files, FALSE);
	}
}

// 从指定目录获取所有指定扩展名的文件（包含子目录）列表
// withFullFolder 指定返回列表中的每项，是包含全路径还是相对路径（默认是包含全路径）
void CFileOperation::getFilesFromFolder(CString root,CString folder,CString filter,CStringArray *files, bool withFullFolder)
{
	if(files==NULL)
		return;

	CString path=TEXT("");
	if(root.GetLength()<=0 && folder.GetLength()<=0)
		path=TEXT(".");
	else if(root.GetLength()>0 && folder.GetLength()<=0)
		path=root;
	else if(root.GetLength()<=0 && folder.GetLength()>0)
		path=folder;
	else if(root.GetLength()>0 && folder.GetLength()>0)
		path=root + TEXT("\\") + folder;

	if(filter.GetLength()<=0)
		filter=TEXT("*.*");

	// 获取当前文件夹下的所有子文件夹
	CStringArray subfolderList;
	CFolderOperation::getSubFolders(path, subfolderList);

	// 获取当前文件夹下的指定filter的所有文件
	CStringArray fileList;
	getFileNamesinFolder(path, filter, &fileList);

	// 将当前文件夹下的文件添加到 files 列表中
	CString fileName=TEXT("");
	int i=0;
	for(i=0;i<fileList.GetSize();i++)
	{
// 		if(withFullFolder)
// 		{
// 			if(folder!="")
// 				fileName=folder + "\\" + fileList[i];
// 			else
// 				fileName=fileList[i];
// 		}
// 		else
// 			fileName=fileList[i];

		if(withFullFolder)
		{
			fileName = path + TEXT("\\") + fileList[i];
		}
		else
		{
			if(folder.GetLength()>0)
				fileName=folder + TEXT("\\") + fileList[i];
			else
				fileName=fileList[i];
		}

		files->Add(fileName);
	}

	CString subFolder=TEXT("");
	// 对每个子文件夹，执行相同的操作
	for(i=0;i<subfolderList.GetSize();i++)
	{
		if(withFullFolder)
			subFolder = path + TEXT("\\") + subfolderList[i];
		else
		{
			if(folder.GetLength()>0)
				subFolder = folder + TEXT("\\") + subfolderList[i];
			else
				subFolder = subfolderList[i];
		}

		getFilesFromFolder(root, subFolder, filter, files, withFullFolder);
	}
}

// 从指定的全路径中获取文件夹和文件名
void CFileOperation::getFileInfoFromPath(CString fullPath, CString &folder, CString &fileName)
{
	// 如果原串为空，则全返回空串
	if(fullPath.GetLength()<=0)
	{
		folder=TEXT("");
		fileName= TEXT("");
		return;
	}

	int pos=fullPath.ReverseFind(TEXT('\\'));
	// 如果未找到，则等于只有文件名
	if(pos<0)
	{
		folder=TEXT("");
		fileName=fullPath;
		return;
	}

	folder=fullPath.Left(pos);
	fileName=fullPath.Right(fullPath.GetLength()-pos-1);
}

BOOL CFileOperation::isFileExist(CString fileFullPath)
{
	CFileFind find;
	BOOL result=FALSE;
	if(find.FindFile(fileFullPath)) 
    	result=TRUE; 
	find.Close();
	return result;
}

CString CFileOperation::getFileName( CString fullPath )
{
	CString name;
	// 获取不带扩展名的文件名
	int pos=fullPath.ReverseFind(TEXT('\\'));
	if(pos>0)    //////////////////////////////////////// ==0 的时候是否表示文件名形如“.abcd”的形式？？？
		name=fullPath.Right(fullPath.GetLength()-pos-1);
	else
		name=fullPath;
	
	return name;
}

// 从（可带可不带路径的）文件名中提取没有扩展名的部份
CString CFileOperation::getFileNameNoExt(CString fileNameNoPath)
{
	CString nameNoExt;
	// 获取不带扩展名的文件名
	int pos=fileNameNoPath.ReverseFind(TEXT('.'));
	if(pos>0)    //////////////////////////////////////// ==0 的时候是否表示文件名形如“.abcd”的形式？？？
		nameNoExt=fileNameNoPath.Left(pos);
	else
		nameNoExt=fileNameNoPath;
	
	return nameNoExt;
}


CString CFileOperation::GetFullFileNameNoExt(CString path,CString prefix,CString filter)
{
	int i=1;
	CFileFind fileFind;
	CString tmp;
	tmp.Format(TEXT("%s%s_%d%s"),path,prefix,i,filter);
	while(fileFind.FindFile(tmp))
	{
		i+=1;
		tmp.Format(TEXT("%s%s_%d%s"),path,prefix,i,filter);
	}
	tmp.Format(TEXT("%s%s_%d"),path,prefix,i);
	return tmp;
}

ULONGLONG CFileOperation::getFileSize(CString fileFullPath)
{
	CFileStatus status;
	memset(&status,0,sizeof(CFileStatus));
	CFile::GetStatus(fileFullPath,status);
	return status.m_size;
}

CString CFileOperation::getFileExtName(CString file)
{
	if(file.GetLength()<=0)
		return TEXT("");

	int pos=file.ReverseFind(TEXT('.'));
	if(pos==-1)
		return file;
	else
		return file.Right(file.GetLength()-pos-1);
}

CString CFileOperation::getTempFileFullPath(CString folder, CString prefix)
{
	TCHAR name[MAX_PATH-14];
	GetTempFileName(folder,prefix,0,name);
	CString ret=name;
	return ret;
}
