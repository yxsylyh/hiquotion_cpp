// SystemDrives.cpp: implementation of the CSystemDrives class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemDrives.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemDrives::CSystemDrives()
{

}

CSystemDrives::~CSystemDrives()
{

}

// 查询驱动器，并把驱动器按其类型，存储到各个驱动器列表中
void CSystemDrives::queryDrives()
{
	clearDrives();
	
	CString drv="";
	char drvChar='\0';
	int drvType=DRIVE_UNKNOWN;
	for(int i=2;i<26;i++)
	{
		drvChar='A' + i;
		drv=drvChar;
		drv+=":\\";
		
		// #define DRIVE_UNKNOWN     0
		// #define DRIVE_NO_ROOT_DIR 1
		// #define DRIVE_REMOVABLE   2
		// #define DRIVE_FIXED       3
		// #define DRIVE_REMOTE      4
		// #define DRIVE_CDROM       5
		// #define DRIVE_RAMDISK     6
		drvType=GetDriveType(drv);
		switch(drvType)
		{
		case DRIVE_UNKNOWN:
			break;
		case DRIVE_NO_ROOT_DIR:
			break;
		case DRIVE_REMOVABLE:
			RemovableDrives.push_back(drvChar);
			break;
		case DRIVE_FIXED:
			FixedDrives.push_back(drvChar);
			break;
		case DRIVE_REMOTE:
			RemoteDrives.push_back(drvChar);
			break;
		case DRIVE_CDROM:
			Cdroms.push_back(drvChar);
			break;
		case DRIVE_RAMDISK:
			RamdiskDrives.push_back(drvChar);
			break;
		}
	}
};

// 查询指定类型的驱动器，类型0表示全部
void CSystemDrives::queryDrives(std::vector<char> &drives, UINT type/*=0*/)
{
	drives.clear();

	CString drv="";
	char drvChar='\0';
	for(int i=2;i<26;i++)
	{
		drvChar='A' + i;
		drv=drvChar;
		drv+=":\\";

		
		// #define DRIVE_UNKNOWN     0
		// #define DRIVE_NO_ROOT_DIR 1
		// #define DRIVE_REMOVABLE   2
		// #define DRIVE_FIXED       3
		// #define DRIVE_REMOTE      4
		// #define DRIVE_CDROM       5
		// #define DRIVE_RAMDISK     6
		int drvType=GetDriveType(drv);
		if(drvType==DRIVE_UNKNOWN || drvType==DRIVE_NO_ROOT_DIR)
			continue;

		if(type==0)
			drives.push_back(drvChar);
		else if(type==drvType)
			drives.push_back(drvChar);
	}
}

// 获取指定磁盘的剩余空间
// 参数：盘符字符，剩余空间结构体
// 返回值：成功与否
BOOL CSystemDrives::getDriveSpace(char drvChar, DriveSpace &driveSpace)
{
	CString drv=drvChar;
	drv+=":";
	DriveSpace space;
	memset(&space, 0x00, sizeof(DriveSpace));
	if(!GetDiskFreeSpaceEx(drv, &space.available, &space.total, &space.rested))
		return FALSE;

	driveSpace=space;
	return TRUE;
};

// 获取最大剩余空间的磁盘盘符和剩余空间大小（按字节）
BOOL CSystemDrives::getMaxFreeSpaceDrive(std::vector<char> drives, char &drvChar, ULARGE_INTEGER *maxFreeSpace)
{
	if(drives.size()<=0)
		return FALSE;

	DriveSpace space;
	ULARGE_INTEGER maxfree;
	memset(&maxfree, 0x00, sizeof(ULARGE_INTEGER));
	int maxindex=0;
	int first=0;

	// 找到第一个能够获取到最大空间的盘符（就是不操作失败的）
	while(!getDriveSpace(drives[first], space))
	{
		first++;
		if(first==drives.size())   // 终止条件
			break;
	}

	// 如果一个都没有，则返回失败
	if(first==drives.size())
		return FALSE;

	// 至少找到了一个
	maxfree=space.rested;
	maxindex=first;

	// 如果已经到了列表的最后，则返回成功，并把至少找到的一个给返回
	first++;
	if(first==drives.size())
	{
		drvChar=drives[maxindex];
		memcpy(&maxFreeSpace, &maxfree, sizeof(ULARGE_INTEGER));
		return TRUE;
	}

	// 说明列表中还有剩余的盘符，对于取剩余空间成功的盘符，要和前面找到的盘符的剩余空间做比较，并更新成最大者
	while(getDriveSpace(drives[first], space))
	{
		if(maxfree.QuadPart<space.rested.QuadPart)                    // 做比较
		{
			memcpy(&maxfree, &space.rested, sizeof(ULARGE_INTEGER));  // 更新成最大者
			maxindex=first;
		}
		first++;
		if(first==drives.size())     // 终止条件
			break;
	}
	
	// 全部比较完毕，返回成功，并把最大者给返回
	drvChar=drives[maxindex];
	memcpy(&maxFreeSpace, &maxfree, sizeof(ULARGE_INTEGER));
	return TRUE;
};

void CSystemDrives::clearDrives()
{
	RemovableDrives.clear();
	FixedDrives.clear();
	RemoteDrives.clear();
	Cdroms.clear();
	RamdiskDrives.clear();
}

// 底层驱动路径转换成 Win32 路径
CString CSystemDrives::convertDrvFoldertoWin32(CString drvFolder)
{
	if(drvFolder.GetLength()<=0)
		return "";

	if(drvFolder.Find("\\Device", 0)!=0)
		return drvFolder;
	
	std::vector<char> drives;
	queryDrives(drives, 0);
	CString sret=drvFolder;

	for(int i=0;i<drives.size();i++)
	{
		CString drv=drives.at(i);
		drv+=":";
		std::string drvName="";
		BOOL ret=getDosDriveString((LPTSTR)(LPCSTR)drv, drvName);
		drvName+="\\";
		if(sret.Find(drvName.c_str(), 0)==0)
			sret.Replace(drvName.c_str(), drv+"\\");
	}

	return sret;
}

// BOOL CSystemDrives::getLogicalDriveStringList(std::vector<std::string> &drives)
// {
// 	// 获取Logic Drive String长度
//     UINT uiLen = GetLogicalDriveStrings(0, NULL);
//     if (0 == uiLen)
//     {
//         return FALSE;
//     }
// 	
//     PTSTR pLogicDriveString = new TCHAR[uiLen + 1];
//     ZeroMemory(pLogicDriveString, uiLen + 1);
//     uiLen = GetLogicalDriveStrings(uiLen, pLogicDriveString);
//     if (0 == uiLen)
//     {
//         delete[]pLogicDriveString;
//         return FALSE;
//     }
// 	
// 	PTSTR pLogicIndex = pLogicDriveString;
// 	drives.clear();
// 
// 	do
//     {
// 		std::string drive=*pLogicIndex;
//         drives.push_back(drive);
// 
//         /*while*/ (*pLogicIndex++);
//     }
// 	while (*pLogicIndex);
// 	
// 
// }

// 获取底层驱动器列表
BOOL CSystemDrives::getDosDriveString(std::string driveString, std::string &drive)
{
	PTSTR pDosDriveName = new TCHAR[MAX_PATH];
	UINT uiLen = QueryDosDevice(driveString.c_str(), pDosDriveName, MAX_PATH);
	if (0 == uiLen)
	{
		DWORD ret=GetLastError();
		if (ERROR_INSUFFICIENT_BUFFER != ret)
		{
			return FALSE;
		}
		
		delete[]pDosDriveName;
		pDosDriveName = new TCHAR[uiLen + 1];
		uiLen = QueryDosDevice(driveString.c_str(), pDosDriveName, uiLen + 1);
		if (0 == uiLen)
		{
			return FALSE;
		}
	}
	
	drive=pDosDriveName;
	delete pDosDriveName;

	return TRUE;
}
