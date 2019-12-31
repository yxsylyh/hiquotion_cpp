// EVENTEMU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EVENTEMU.h"
#include "MyButton.h"
#include "ClickEventHandler.h"
#include "Z.h"
#include "D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
	}

// 	CMyButton btn;
// 	CClickEventHandler handler;
// 	btn.Click+=&handler;
// 	btn.Clicked();

	// CZ means Window Class(for example, a Dialog)
// 	CZ z;
// 	z.emuEventRaise();

	CD d;
	d.raiseEvent();

	system("pause");

	return nRetCode;
}


