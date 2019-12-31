// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma warning(disable : 4786)

#if !defined(AFX_STDAFX_H__53D6BBF6_BE92_4CB5_80CB_1D151ECD0455__INCLUDED_)
#define AFX_STDAFX_H__53D6BBF6_BE92_4CB5_80CB_1D151ECD0455__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

// TODO: reference additional headers your program requires here
#include <C++\3rdParty\GDIPlus\Includes\GdiPlus.h>
using namespace Gdiplus;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__53D6BBF6_BE92_4CB5_80CB_1D151ECD0455__INCLUDED_)
