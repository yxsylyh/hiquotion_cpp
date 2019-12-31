#include "StdAfx.h"
#include "SystemOperation.h"
#include"tlhelp32.h"

CSystemOperation::CSystemOperation(void)
{
}

CSystemOperation::~CSystemOperation(void)
{
}

void CSystemOperation::DoEvents()
{
	MSG msg;
	while(::PeekMessage(&msg, NULL,0,0,PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

HANDLE CSystemOperation::ShellEx(CString appPath, CString para, CString directory, BOOL isShow, HWND hwnd)
{
	SHELLEXECUTEINFO exeInfo;
	exeInfo.cbSize=sizeof(SHELLEXECUTEINFO);
	exeInfo.fMask = (SEE_MASK_DOENVSUBST|SEE_MASK_FLAG_DDEWAIT|0x04000000|SEE_MASK_NOCLOSEPROCESS); //|SEE_MASK_NO_CONSOLE);
	exeInfo.hwnd = hwnd;
	exeInfo.lpVerb = "open";
	exeInfo.lpFile = appPath;
	exeInfo.lpParameters = para;
	exeInfo.lpDirectory = directory;
	exeInfo.nShow = isShow ? SW_SHOW : SW_HIDE;
	exeInfo.hInstApp = NULL;
	exeInfo.lpIDList = NULL;
	exeInfo.lpClass = NULL;
	exeInfo.hkeyClass = NULL;
	exeInfo.dwHotKey = NULL;
	exeInfo.hMonitor = NULL;
	exeInfo.hIcon = NULL;
	exeInfo.hProcess = NULL;

	BOOL ret=::ShellExecuteEx(&exeInfo);
	if(!ret)
		return NULL;

	return exeInfo.hProcess;
}

BOOL CSystemOperation::ShellWait(DWORD &retCode, CString appPath, CString para, CString directory, BOOL isShow, HWND hwnd)
{
	HANDLE hProcess=ShellEx(appPath, para, directory, isShow, hwnd);
	if(!hProcess)
		return FALSE;
	
	DWORD exitCode=0;
	::WaitForSingleObject(hProcess,INFINITE);
	GetExitCodeProcess(hProcess, &exitCode);
	::CloseHandle(hProcess);

	retCode=exitCode;
	return TRUE;
}

BOOL CSystemOperation::ShellWait( DWORD &retCode, HANDLE &hProcess, CString appPath, CString para/*=""*/, CString directory/*=""*/, BOOL isShow/*=FALSE*/ , HWND hwnd )
{
	hProcess=ShellEx(appPath, para, directory, isShow, hwnd);
	if(!hProcess)
		return FALSE;
	
	DWORD exitCode=0;
	::WaitForSingleObject(hProcess,INFINITE);
	GetExitCodeProcess(hProcess, &exitCode);
	::CloseHandle(hProcess);
	
	retCode=exitCode;
	return TRUE;
}
// Gloabal Callback Function for EnumWindows()
// for Process Handle to Wnd Handle
BOOL CALLBACK EnumWinProc(HWND hwnd, LPARAM lParam)
{
    DWORD dwID;
    EnumParam* pep = (EnumParam*)lParam;
    GetWindowThreadProcessId(hwnd,   &dwID);
    if (dwID == pep->dwProcessID)
    {
        pep->hMainWnd = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND CSystemOperation::HProcess2HWnd(HANDLE hProcess)
{
	if(!hProcess)
		return NULL;

	DWORD pid=GetProcessIDbyProcessHandle(hProcess);
	if(pid==0)
		return NULL;

	EnumParam ep;
	ep.dwProcessID=pid;
	ep.hMainWnd=NULL;
	EnumWindows((WNDENUMPROC)EnumWinProc, (long)&ep);
	return ep.hMainWnd;
}

// typedef NTSTATUS (WINAPI * PFN_ZWQUERYINFORMATIONPROCESS)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG); 
// typedef DWORD (WINAPI * GetProcessId)(HANDLE); 

DWORD CSystemOperation::GetProcessIDbyProcessHandle(HANDLE hProcess) 
{ 
//     HINSTANCE hNtDll = LoadLibraryW(L"ntdll.dll");
// 	if (hNtDll == NULL)
// 		return 0xffffffff;
// 	
// 	PFN_ZWQUERYINFORMATIONPROCESS fnProcInfo = (PFN_ZWQUERYINFORMATIONPROCESS)::GetProcAddress(hNtDll, "ZwQueryInformationProcess");
// 	if (fnProcInfo == NULL)
// 	{
// 		CloseHandle(hNtDll);
// 		return 0xffffffff;
// 	}
// 	
// 	PROCESS_BASIC_INFORMATION pbi;
// 	ZeroMemory(&pbi, sizeof(PROCESS_BASIC_INFORMATION));
// 	if (fnProcInfo(hProcess, 0, &pbi, sizeof(PROCESS_BASIC_INFORMATION), NULL) == 0)
// 	{
// 		CloseHandle(hNtDll);
// 		return pbi.UniqueProcessId;
//      }
// 	else
//     {
// 		CloseHandle(hNtDll);
// 		return 0xffffffff;
// 	}
	




//     HINSTANCE hdll = LoadLibrary("kernel32.dll"); 
//     if (hdll == NULL)
// 		return 0; 
//     
// 	GetProcessId fnGetProcessId = GetProcessId(::GetProcAddress(hdll, "GetProcessId")); 
//     if (fnGetProcessId == NULL) 
//     { 
//         FreeLibrary(hdll); 
//         return 0; 
//     }

	DWORD pid=0;
#if _MSC_VER >= 1500   // vc9 or higher
	pid=(DWORD)GetProcessId(hProcess);
#endif // _MSC_VER >= 1500

// 	FreeLibrary(hdll); 
	return pid; 
}

DWORD CSystemOperation::GetProcessidFromName(CString name)
{
	PROCESSENTRY32 pe;
	DWORD id = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe))
		return 0;
	while (1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot, &pe) == FALSE)
			break;
		if (strcmp(pe.szExeFile, name) == 0)
		{
			id = pe.th32ProcessID;
			break;
		}
	}
	CloseHandle(hSnapshot);
	return id;
}

BOOL CSystemOperation::isWow64()
{
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( GetModuleHandle(_T("kernel32")), "IsWow64Process");
	if (NULL != fnIsWow64Process)
	{
		fnIsWow64Process(GetCurrentProcess(),&bIsWow64);
	}
	return bIsWow64;
}

int CSystemOperation::getOSArchFlag()
{
	if(isWow64())
		return 2;   // 010
	else
		return 1;   // 001
}

int CSystemOperation::getVersionFlag()
{
	OSVERSIONINFOEX os; 
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);   

	if(!GetVersionEx((OSVERSIONINFO *)&os))
		return 0;

	switch(os.dwMajorVersion)
	{
	case 5:
		switch(os.dwMinorVersion)
		{
		case 1:
			return 1;   // xp  000001
			break;
		case 2:
			return 2;   // server 2003  000010
			break;
		}
		break;
	case 6:
		switch(os.dwMinorVersion)
		{
		case 0:
			return 4;   // vista  000100
			break;
		case 1:
			return 8;   // windows 7  001000
			break;
		case 2:
			return 16;   // windows 8  010000
			break;
		case 3:
			return 32;   // windows 8.1  100000
			break;
		case 4:
			return 64;   // windows 10 预览版   1000000
		}
		break;
	case 10:
		switch(os.dwMinorVersion)
		{
		case 0:
			return 64;   // windows 10   1000000
			break;
		}
	}
	return 0;
}

// ntdll!NtQueryInformationProcess (NT specific!)  
//  
// The function copies the process information of the  
// specified type into a buffer  
//  
// NTSYSAPI  
// NTSTATUS  
// NTAPI  
// NtQueryInformationProcess(  
//    IN HANDLE ProcessHandle,              // handle to process  
//    IN PROCESSINFOCLASS InformationClass, // information type  
//    OUT PVOID ProcessInformation,         // pointer to buffer  
//    IN ULONG ProcessInformationLength,    // buffer size in bytes  
//    OUT PULONG ReturnLength OPTIONAL      // pointer to a 32-bit  
//                                          // variable that receives  
//                                          // the number of bytes  
//                                          // written to the buffer   
// ); 
typedef LONG (__stdcall *PROCNTQSIP)(HANDLE,UINT,PVOID,ULONG,PULONG);

DWORD CSystemOperation::getParentProcessId(DWORD dwProcessId)
{
	LONG						status;
	DWORD						dwParentPID = (DWORD)-1;
	HANDLE						hProcess;
	PROCESS_BASIC_INFORMATION	pbi;

	memset(&pbi, 0x00, sizeof(PROCESS_BASIC_INFORMATION));
	
	PROCNTQSIP NtQueryInformationProcess = (PROCNTQSIP)GetProcAddress(  
		GetModuleHandle("ntdll"), "NtQueryInformationProcess"); 
	
	if(NULL == NtQueryInformationProcess)
	{
		return (DWORD)-1;
	}
	// Get process handle
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, dwProcessId);
	if (!hProcess)
	{
		return (DWORD)-1;
	}
	
	// Retrieve information
	status = NtQueryInformationProcess( hProcess,
		ProcessBasicInformation,
		(PVOID)&pbi,
		sizeof(PROCESS_BASIC_INFORMATION),
		NULL
		);
	
	// Copy parent Id on success
	if  (!status)
	{
		dwParentPID = pbi.InheritedFromUniqueProcessId;
	}
	
	CloseHandle (hProcess);
	
	return dwParentPID;
}

typedef DWORD (__stdcall *fnGetProcessImageFileName)(HANDLE, LPTSTR , DWORD); // 跟x86/x64无关，但路径是驱动层的"\Device\HarddiskVolume1\..."形式，需要再转换

std::string CSystemOperation::GetProcessName(DWORD processID)
{
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	
	char *procName = new char[MAX_PATH];
	memset(procName, 0x00, MAX_PATH);
	
	if (hProcess)
    {
		HMODULE hMod=LoadLibrary("Psapi");
		if(hMod)
		{
// 			fnGetModuleFileNameEx getModuleFileNameEx = (fnGetModuleFileNameEx)GetProcAddress(
// 				hMod, "GetModuleFileNameExA");
			fnGetProcessImageFileName getProcessImageFileName = (fnGetProcessImageFileName)GetProcAddress(
				hMod, "GetProcessImageFileNameA");
			if(getProcessImageFileName)
				getProcessImageFileName(hProcess, procName, MAX_PATH);

			FreeLibrary(hMod);
		}

		CloseHandle (hProcess);
   }

	std::string sprocName=procName;
	delete procName;
	return sprocName;
}

// DWORD WINAPI GetModuleFileNameEx(
// 								 _In_     HANDLE  hProcess,
// 								 _In_opt_ HMODULE hModule,
// 								 _Out_    LPTSTR  lpFilename,
// 								 _In_     DWORD   nSize
// );
typedef DWORD (__stdcall *fnGetModuleFileNameEx)(HANDLE, HMODULE, LPTSTR , DWORD);  // HANDLE 指定的进程架构（x86/x64）必须和调用进程架构相同

std::string CSystemOperation::GetProcessName32(DWORD processID)
{
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	
	char *procName = new char[MAX_PATH];
	memset(procName, 0x00, MAX_PATH);
	
	if (hProcess)
    {
		HMODULE hMod=LoadLibrary("Psapi");
		if(hMod)
		{
			fnGetModuleFileNameEx getModuleFileNameEx = (fnGetModuleFileNameEx)GetProcAddress(
				hMod, "GetModuleFileNameExA");
// 			fnGetProcessImageFileName getProcessImageFileName = (fnGetProcessImageFileName)GetProcAddress(
// 				hMod, "GetProcessImageFileNameA");
			if(getModuleFileNameEx)
				getModuleFileNameEx(hProcess, NULL, procName, MAX_PATH);
			
			FreeLibrary(hMod);
		}
		
		CloseHandle (hProcess);
	}
	
	std::string sprocName=procName;
	delete procName;
	return sprocName;

}

std::string CSystemOperation::GetModuleName32(DWORD pid, HMODULE hModule)
{
	char *procName = new char[MAX_PATH];
	memset(procName, 0x00, MAX_PATH);
	
	HANDLE hProcess=OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (hProcess)
    {
		HMODULE hMod=LoadLibrary("Psapi");
		if(hMod)
		{
			fnGetModuleFileNameEx getModuleFileNameEx = (fnGetModuleFileNameEx)GetProcAddress(
				hMod, "GetModuleFileNameExA");
			if(getModuleFileNameEx)
				getModuleFileNameEx(hProcess, hModule, procName, MAX_PATH);
			
			FreeLibrary(hMod);
		}
		
		CloseHandle (hProcess);
	}
	
	std::string sprocName=procName;
	delete procName;
	return sprocName;
}

BOOL CSystemOperation::SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid))
	{
		printf("/nLookupPrivilegeValue error:%d", GetLastError());
		return FALSE;
	}
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;
	AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL);
	if (GetLastError() != ERROR_SUCCESS)
	{
		printf("AdjustTokenPrivileges failed: %u/n", GetLastError());
		return FALSE;
	}
	return TRUE;
}

BOOL CSystemOperation::killProcess(DWORD id)
{
	HANDLE hProcess = NULL, hProcessToken = NULL;
	BOOL IsKilled = FALSE, bRet = FALSE;
	__try
	{

		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hProcessToken))
		{
			printf("/nOpen Current Process Token failed:%d", GetLastError());
			__leave;
		}
		//printf("/nOpen Current Process Token ok!"); 
		if (!SetPrivilege(hProcessToken, SE_DEBUG_NAME, TRUE))
		{
			__leave;
		}
		printf("/nSetPrivilege ok!");

		if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id)) == NULL)
		{
			printf("/nOpen Process %d failed:%d", id, GetLastError());
			__leave;
		}
		//printf("/nOpen Process %d ok!",id); 
		if (!TerminateProcess(hProcess, 1))
		{
			printf("/nTerminateProcess failed:%d", GetLastError());
			__leave;
		}
		IsKilled = TRUE;
	}
	__finally
	{
		if (hProcessToken != NULL) CloseHandle(hProcessToken);
		if (hProcess != NULL) CloseHandle(hProcess);
	}
	return(IsKilled);
}
