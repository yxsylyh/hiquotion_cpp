// FileVersion.cpp: implementation of the CVersion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileVersion.h"
#include <winver.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileVersion::CFileVersion()
{

}

CFileVersion::~CFileVersion()
{

}

void CFileVersion::getFileVersion(CString fullPath, WORD &v1, WORD &v2, WORD &v3, WORD &v4)
{
	DWORD dwVerInfoSize = 0;
    DWORD dwVerHnd;
    VS_FIXEDFILEINFO * pFileInfo;
	
	v1=0;
	v2=0;
	v3=0;
	v4=0;
	
	dwVerInfoSize = ::GetFileVersionInfoSize((LPTSTR)(LPCSTR)fullPath, &dwVerHnd);
    if (dwVerInfoSize)
    {
        // If we were able to get the information, process it:
        HANDLE  hMem;
        LPVOID  lpvMem;
        unsigned int uInfoSize = 0;
        
        hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
        lpvMem = GlobalLock(hMem);
        ::GetFileVersionInfo((LPTSTR)(LPCSTR)fullPath, dwVerHnd, dwVerInfoSize, lpvMem);
        
        ::VerQueryValue(lpvMem, (LPTSTR)("\\"), (void**)&pFileInfo, &uInfoSize);
		
        // Product version from the FILEVERSION of the version info resource 
        v1 = HIWORD(pFileInfo->dwProductVersionMS); 
        v2= LOWORD(pFileInfo->dwProductVersionMS);
        v3 = HIWORD(pFileInfo->dwProductVersionLS);
        v4 = LOWORD(pFileInfo->dwProductVersionLS); 
        
    }
	
}

void CFileVersion::versionString2Int( std::string str,int *version )
{
	std::string st1("");
    int j = 0;
    for (int i = 0;i< str.size();i++)
    {
        if (str[i] == '.')
        {
            version[j++] = atoi(st1.c_str());
            st1 = "";
        }else
        {
            st1 += str[i];
        }
    }
    version[j++] = atoi(st1.c_str());
}

int CFileVersion::compareVersion( CString ver1, CString ver2 )
{
	if(ver1.GetLength()<=0 || ver2.GetLength()<=0)
		return -100;

	int nVer1[4], nver2[4];
	memset(nVer1, 0, 4*sizeof(int));
	memset(nver2, 0, 4*sizeof(int));

	versionString2Int((LPTSTR)(LPCSTR)ver1, nVer1);
	versionString2Int((LPTSTR)(LPCSTR)ver2, nver2);

	//比较两个版本
	int k = memcmp(nVer1, nver2, 4*sizeof(int));
	if (k == 0)
		return 0;
	else if (k < 0)
		return -1;
	else
		return 1;
}
