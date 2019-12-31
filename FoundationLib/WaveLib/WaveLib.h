// WaveLib.h : main header file for the WAVELIB application
//

#if !defined(AFX_WAVELIB_H__ADBC5498_8DB6_4146_9FB8_7F030BBB1179__INCLUDED_)
#define AFX_WAVELIB_H__ADBC5498_8DB6_4146_9FB8_7F030BBB1179__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWaveLibApp:
// See WaveLib.cpp for the implementation of this class
//

class CWaveLibApp : public CWinApp
{
public:
	CWaveLibApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveLibApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWaveLibApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVELIB_H__ADBC5498_8DB6_4146_9FB8_7F030BBB1179__INCLUDED_)
