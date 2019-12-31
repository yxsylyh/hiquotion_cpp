// DelegationCodeGen.h : main header file for the DELEGATIONCODEGEN application
//

#if !defined(AFX_DELEGATIONCODEGEN_H__A60473D1_7A9E_4205_B168_EFC1804F6013__INCLUDED_)
#define AFX_DELEGATIONCODEGEN_H__A60473D1_7A9E_4205_B168_EFC1804F6013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDelegationCodeGenApp:
// See DelegationCodeGen.cpp for the implementation of this class
//

class CDelegationCodeGenApp : public CWinApp
{
public:
	CDelegationCodeGenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelegationCodeGenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDelegationCodeGenApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELEGATIONCODEGEN_H__A60473D1_7A9E_4205_B168_EFC1804F6013__INCLUDED_)
