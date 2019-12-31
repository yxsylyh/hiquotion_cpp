// SystemDrives.h: interface for the CSystemDrives class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMDRIVES_H__D137DBFA_4BC7_41E3_B1E4_C3182B76151E__INCLUDED_)
#define AFX_SYSTEMDRIVES_H__D137DBFA_4BC7_41E3_B1E4_C3182B76151E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

struct DriveSpace
{
	ULARGE_INTEGER available;
	ULARGE_INTEGER total;
	ULARGE_INTEGER rested;
};

// 系统驱动器类
// 其中的方法，不能声明称static，因为vector的变量会导致无法解析的外部符号～～～
class CSystemDrives  
{
public:
	CSystemDrives();//{};
	virtual ~CSystemDrives();//{};

	std::vector<char> RemovableDrives;
	std::vector<char> FixedDrives;
	std::vector<char> RemoteDrives;
	std::vector<char> Cdroms;
	std::vector<char> RamdiskDrives;

	// 查询驱动器，并把驱动器按其类型，存储到各个驱动器列表中
	void queryDrives();

	// 查询指定类型的驱动器，类型0表示全部
	// #define DRIVE_REMOVABLE   2
	// #define DRIVE_FIXED       3
	// #define DRIVE_REMOTE      4
	// #define DRIVE_CDROM       5
	// #define DRIVE_RAMDISK     6
	void queryDrives(std::vector<char> &drives, UINT type=0);

	// 获取指定磁盘的剩余空间
	// 参数：盘符字符，剩余空间结构体
	// 返回值：成功与否
	BOOL getDriveSpace(char drvChar, DriveSpace &driveSpace);

	// 获取最大剩余空间的磁盘盘符和剩余空间大小（按字节）
	BOOL getMaxFreeSpaceDrive(std::vector<char> drives, char &drvChar, ULARGE_INTEGER *maxFreeSpace);

// 	// 获取驱动器列表
// 	BOOL getLogicalDriveStringList(std::vector<std::string> &drives);

	// 获取指定盘符（形如"C:\"）的底层驱动器字符串
	BOOL getDosDriveString(std::string driveString, std::string &drives);

	// 指定某类驱动器
	
	// 底层驱动路径转换成 Win32 路径
	CString convertDrvFoldertoWin32(CString drvFolder);

private:
	void clearDrives();
};

#endif // !defined(AFX_SYSTEMDRIVES_H__D137DBFA_4BC7_41E3_B1E4_C3182B76151E__INCLUDED_)
