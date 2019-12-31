#pragma once

#include <string>

// struct for EnumWIndows
// for Process Handle to Wnd Handle
struct   EnumParam
{
    HWND hMainWnd;
    DWORD dwProcessID;
};

// #if !defined NTSTATUS
// typedef LONG NTSTATUS;
// #endif
// 
// #if !defined PROCESSINFOCLASS
// typedef LONG PROCESSINFOCLASS;
// #endif
// 
// #if !defined PPEB
// typedef struct _PEB *PPEB;
// #endif
// 
// #define ULONG_PTR long
// 
// #if !defined PROCESS_BASIC_INFORMATION
// typedef struct _PROCESS_BASIC_INFORMATION
// {
// 	PVOID Reserved1;
// 	PPEB PebBaseAddress;
// 	PVOID Reserved2[2];
// 	ULONG_PTR UniqueProcessId;
// 	PVOID Reserved3;
// } PROCESS_BASIC_INFORMATION; #endif; 

#define ProcessBasicInformation 0  

typedef struct  
{  
	DWORD ExitStatus;  
	DWORD PebBaseAddress;  
	DWORD AffinityMask;  
	DWORD BasePriority;  
	ULONG UniqueProcessId;  
	ULONG InheritedFromUniqueProcessId;  
}   PROCESS_BASIC_INFORMATION;  

class CSystemOperation
{
public:
	CSystemOperation(void);
	~CSystemOperation(void);

	static void DoEvents();
	static HANDLE ShellEx(CString appPath, CString para="", CString directory="", BOOL isShow=FALSE, HWND hwnd=NULL);
	static BOOL ShellWait(DWORD &retCode, CString appPath, CString para="", CString directory="", BOOL isShow=FALSE, HWND hwnd=NULL);
	static BOOL ShellWait(DWORD &retCode, HANDLE &hProcess, CString appPath, CString para="", CString directory="", BOOL isShow=FALSE, HWND hwnd=NULL);
	static DWORD GetProcessIDbyProcessHandle(HANDLE hProcess);
	static DWORD GetProcessidFromName(CString name);
	static HWND HProcess2HWnd(HANDLE hProcess);

	static BOOL isWow64();
	static int getOSArchFlag();
	static int getVersionFlag();

	static DWORD getParentProcessId(DWORD dwProcessId);
	static std::string GetProcessName(DWORD processID);
	static std::string GetProcessName32(DWORD processID);
	static std::string GetModuleName32(DWORD pid, HMODULE hModule);

	static BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
	static BOOL killProcess(DWORD id);
};
