// FileVersion.h: interface for the CVersion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEVERSION_H__4CF7B62C_EB7D_4FD2_B7FC_F7891EB1979D__INCLUDED_)
#define AFX_FILEVERSION_H__4CF7B62C_EB7D_4FD2_B7FC_F7891EB1979D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

#pragma comment(lib, "version.lib")

class CFileVersion  
{
public:
	CFileVersion();
	virtual ~CFileVersion();

	static void getFileVersion(CString fullPath, WORD &v1, WORD &v2, WORD &v3, WORD &v4);

	// 比较ver1和ver2哪个版本高
	// 内部调用了 versionString2Int()
	// 返回值：
	// -1：ver2版本高，0：版本相同，1：ver1版本高，-100无法比较或出现错误
	static int compareVersion(CString ver1, CString ver2);
private:
	static void versionString2Int(std::string str,int *version);
};

#endif // !defined(AFX_FILEVERSION_H__4CF7B62C_EB7D_4FD2_B7FC_F7891EB1979D__INCLUDED_)
