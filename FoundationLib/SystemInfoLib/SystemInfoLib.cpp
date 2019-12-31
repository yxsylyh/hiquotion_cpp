// SystemInfoLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SystemInfoLib.h"
#include "SystemDrives.h"

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

		CSystemDrives sysdrv;
		sysdrv.queryDrives();
		char maxDrvChar;
		ULARGE_INTEGER maxDrvFreeSpace;
		if(!sysdrv.getMaxFreeSpaceDrive(sysdrv.FixedDrives, maxDrvChar, &maxDrvFreeSpace))
			printf("failed!\n");
		else
			printf("max free space drive is %c\n", maxDrvChar);

		system("pause");
	}

	return nRetCode;
}


