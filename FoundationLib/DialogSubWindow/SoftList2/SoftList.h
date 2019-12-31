// SoftList.h : main header file for the SOFTLIST application
//

#if !defined(AFX_SOFTLIST_H__EC65E33A_7430_4AA9_9703_8220A225BAEF__INCLUDED_)
#define AFX_SOFTLIST_H__EC65E33A_7430_4AA9_9703_8220A225BAEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoftListApp:
// See SoftList.cpp for the implementation of this class
//

class CSoftListApp : public CWinApp
{
public:
	CSoftListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSoftListApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTLIST_H__EC65E33A_7430_4AA9_9703_8220A225BAEF__INCLUDED_)
