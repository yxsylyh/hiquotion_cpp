// SystemVersion.h: interface for the CSystemVersion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMVERSION_H__2C55ECFD_16C6_4BB1_B38D_1363BF8CC1DD__INCLUDED_)
#define AFX_SYSTEMVERSION_H__2C55ECFD_16C6_4BB1_B38D_1363BF8CC1DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum SystemVersion
{
	Unknown,
	WinNT4_0,
	Win95,
	Win98,
	WinME,
	Win2000, // 5
	WinXP,   // 6
	WinXPx64,
	WinServer2003,
	WinServer2003R2,
	WinVista,
	WinServer2008,
	Win7,    // 12
	WinServer2008R2,
	Win8,    // 14
	WinServer2012,
	Win8_1,  // 16
	Win10,   // 17
};

class CSystemVersion  
{
public:
	CSystemVersion();
	virtual ~CSystemVersion();

	static SystemVersion getSystemVersion();
};

#endif // !defined(AFX_SYSTEMVERSION_H__2C55ECFD_16C6_4BB1_B38D_1363BF8CC1DD__INCLUDED_)
