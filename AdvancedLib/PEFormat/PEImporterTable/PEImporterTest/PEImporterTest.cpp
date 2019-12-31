// PEImporterTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PEImporterTest.h"
#include <Dbghelp.h> //ImageRvaToVa
#include "PEImporterTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
			CPEImporterTable table;
			ImporterTable names;
			int ret=table.getImporterTable(
				"F:\\vs.exe",
//				"F:\\adhapi.dll", //PE文件名
				names);
			printf("ret=%d\n", ret);

			for(int i=0;i<names.dllNames.size();i++)
			{
				printf("DLL name: %s\n", names.dllNames[i]->dllName.c_str());

				for(int j=0;j<names.dllNames[i]->funcNames.size();j++)
				{
					if(names.dllNames[i]->funcNames[j]->funcName.size()<=0)
						printf("\tFUNC no:%d (仅通过函数号导入)\n", names.dllNames[i]->funcNames[j]->no, names.dllNames[i]->funcNames[j]->funcName.c_str());
					else
						printf("\tFUNC no:%d\t name: %s\n", names.dllNames[i]->funcNames[j]->no, names.dllNames[i]->funcNames[j]->funcName.c_str());
				}
			}
//			int i, j;
//			HANDLE hFile = CreateFile(
////				"F:\\vs.exe", //PE文件名
//				"F:\\adhapi.dll", //PE文件名
//				GENERIC_READ, 
//				FILE_SHARE_READ,
//				NULL,
//				OPEN_EXISTING,
//				FILE_ATTRIBUTE_NORMAL,
//				NULL);
//
//			if(hFile == INVALID_HANDLE_VALUE)
//			{
//				printf("Create File Failed.\n");
//				return 0;
//			}
//
//			HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY,    0, 0, NULL);
//
//			if (hFileMapping == NULL || hFileMapping == INVALID_HANDLE_VALUE) 
//			{ 
//				printf("Could not create file mapping object (%d).\n", GetLastError());
//				return 0;
//			}
//
//			LPBYTE lpBaseAddress = (LPBYTE)MapViewOfFile(hFileMapping,   // handle to map object
//				FILE_MAP_READ, 0, 0, 0);
// 
//			if (lpBaseAddress == NULL) 
//			{ 
//				printf("Could not map view of file (%d).\n", GetLastError()); 
//				return 0;
//			}
//
//			PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
//			PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)(lpBaseAddress + pDosHeader->e_lfanew);
//  			PIMAGE_NT_HEADERS64 pNtHeaders64 = (PIMAGE_NT_HEADERS64)(lpBaseAddress + pDosHeader->e_lfanew);
//  
//			//if(pNtHeaders->FileHeader.Machine!=IMAGE_FILE_MACHINE_I386)
//			//{
//			//	printf("NOT 32bit file!\n");
//			//	system("pause");
//			//	return 0;
//			//}
//
//			//导入表的rva：0x2a000;
//			DWORD Rva_import_table = pNtHeaders64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
//
//			if(Rva_import_table == 0)
//			{
//				printf("no import table!");
//				//关闭文件，句柄。。
//				UnmapViewOfFile(lpBaseAddress);
//				CloseHandle(hFileMapping);
//				CloseHandle(hFile);
//				getchar();
//				return 0;
////				goto UNMAP_AND_EXIT;
//			}
//
//			//这个虽然是内存地址，但是减去文件开头的地址，就是文件地址了
//			//这个地址可以直接从里面读取你想要的东西了
//			PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(
//				pNtHeaders, 
//				lpBaseAddress, 
//				Rva_import_table,
//				NULL
//				);
//
//			//减去内存映射的首地址，就是文件地址了。。（很简单吧）
//			printf("FileAddress Of ImportTable: %p\n", ((DWORD)pImportTable - (DWORD)lpBaseAddress));
//
//			//现在来到了导入表的面前：IMAGE_IMPORT_DESCRIPTOR 数组（以0元素为终止）
//			//定义表示数组结尾的null元素！
//			IMAGE_IMPORT_DESCRIPTOR null_iid;
//			IMAGE_THUNK_DATA64 null_thunk;
//			memset(&null_iid, 0, sizeof(null_iid));
//			memset(&null_thunk, 0, sizeof(null_thunk));
//
//			//每个元素代表了一个引入的DLL。
//			for(i=0; memcmp(pImportTable + i, &null_iid, sizeof(null_iid))!=0; i++)
//			{
//				//LPCSTR: 就是 const char*
//				LPCSTR szDllName = (LPCSTR)ImageRvaToVa(
//					pNtHeaders, lpBaseAddress, 
//					pImportTable[i].Name, //DLL名称的RVA
//					NULL);
//
//				//拿到了DLL的名字
//				printf("-----------------------------------------\n");
//				printf("[%d]: %s\n", i, szDllName);
//				printf("-----------------------------------------\n");
//
//				//现在去看看从该DLL中引入了哪些函数
//				//我们来到该DLL的 IMAGE_TRUNK_DATA 数组（IAT：导入地址表）前面
//				PIMAGE_THUNK_DATA64 pThunk = (PIMAGE_THUNK_DATA64)ImageRvaToVa(
//					pNtHeaders, lpBaseAddress,
//					pImportTable[i].OriginalFirstThunk, //【注意】这里使用的是OriginalFirstThunk
//					NULL);
//
//				for(j=0; memcmp(pThunk+j, &null_thunk, sizeof(null_thunk))!=0; j++)
//				{
//					//这里通过RVA的最高位判断函数的导入方式，
//					//如果最高位为1，按序号导入，否则按名称导入
//					if(pThunk[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG64)
//					{
//						printf("\t [%d] \t %ld \t 按序号导入\n", j, pThunk[j].u1.AddressOfData & 0xffff);
//					}
//					else
//					{
//						//按名称导入，我们再次定向到函数序号和名称
//						//注意其地址不能直接用，因为仍然是RVA！
//						PIMAGE_IMPORT_BY_NAME pFuncName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(
//							pNtHeaders,    lpBaseAddress,
//							pThunk[j].u1.AddressOfData,
//							NULL);
//                
//						printf("\t [%d] \t %ld \t %s\n", j, pFuncName->Hint, pFuncName->Name);
//					}
//				}
//			}
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	system("pause");

	return nRetCode;
};

