#include "StdAfx.h"
#include "PEImporterTable.h"
#include <Dbghelp.h> //ImageRvaToVa
#pragma comment(lib, "dbghelp.lib")

CPEImporterTable::CPEImporterTable(void)
{
}


CPEImporterTable::~CPEImporterTable(void)
{
}

int CPEImporterTable::getImporterTable(string file, ImporterTable &dllTable)
{
	m_errMsg="";
	dllTable.clear();

	if(file.length()<=0 || file.size()<=0)
	{
		m_errMsg="文件名为空！";
		return -1;
	}

	HANDLE hFile = CreateFile(
//		"F:\\vs.exe", //PE文件名
//		"F:\\adhapi.dll", //PE文件名
		file.c_str(),
		GENERIC_READ, 
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		m_errMsg="打开文件失败！";
		return -2;
	}

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY,    0, 0, NULL);
	if (hFileMapping == NULL || hFileMapping == INVALID_HANDLE_VALUE) 
	{ 
		m_errMsg="Could not create file mapping object.\n";
		return -3;
	}

	LPBYTE lpBaseAddress = (LPBYTE)MapViewOfFile(hFileMapping,   // handle to map object
		FILE_MAP_READ, 0, 0, 0);
	if (lpBaseAddress == NULL) 
	{ 
		m_errMsg="Could not map view of file."; 
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return -4;
	}

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		m_errMsg="NOT PE file!"; 
		UnmapViewOfFile(lpBaseAddress);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return -5;
	}

	PIMAGE_NT_HEADERS32 pNtHeaders = (PIMAGE_NT_HEADERS32)(lpBaseAddress + pDosHeader->e_lfanew);
	if(pNtHeaders->FileHeader.Machine!=IMAGE_FILE_MACHINE_I386)
	{
		if (pNtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_IA64 || pNtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64)
		{
			int ret=getImporterTable64(pNtHeaders, lpBaseAddress, dllTable);
			if(ret==0)
				return 0;
			else if(ret<0)
			{
				//m_errMsg 由函数getImporterTable64设置
				UnmapViewOfFile(lpBaseAddress);
				CloseHandle(hFileMapping);
				CloseHandle(hFile);
				return -100-ret;
			}
		}
		else
		{
			m_errMsg="NOT 32bit file, NOT 64bit file!";
			return -6;
		}
	}

	//导入表的rva：0x2a000;
	DWORD Rva_import_table = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(Rva_import_table == 0)
	{
		m_errMsg="no import table!";
		//关闭文件，句柄。。
		UnmapViewOfFile(lpBaseAddress);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		//getchar();
		return -7;
//				goto UNMAP_AND_EXIT;
	}

	//这个虽然是内存地址，但是减去文件开头的地址，就是文件地址了
	//这个地址可以直接从里面读取你想要的东西了
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(
		pNtHeaders, 
		lpBaseAddress, 
		Rva_import_table,
		NULL
		);

	//减去内存映射的首地址，就是文件地址了。。（很简单吧）
	//printf("FileAddress Of ImportTable: %p\n", ((DWORD)pImportTable - (DWORD)lpBaseAddress));

	//现在来到了导入表的面前：IMAGE_IMPORT_DESCRIPTOR 数组（以0元素为终止）
	//定义表示数组结尾的null元素！
	IMAGE_IMPORT_DESCRIPTOR null_iid;
	IMAGE_THUNK_DATA null_thunk;
	memset(&null_iid, 0, sizeof(null_iid));
	memset(&null_thunk, 0, sizeof(null_thunk));

	int i,j;
	//每个元素代表了一个引入的DLL。
	for(i=0; memcmp(pImportTable + i, &null_iid, sizeof(null_iid))!=0; i++)
	{
		//LPCSTR: 就是 const char*
		LPCSTR szDllName = (LPCSTR)ImageRvaToVa(
			pNtHeaders, lpBaseAddress, 
			pImportTable[i].Name, //DLL名称的RVA
			NULL);

		IMPORTED_Dll *dll=new IMPORTED_Dll;
		dll->dllName=szDllName;

		////拿到了DLL的名字
		//printf("-----------------------------------------\n");
		//printf("[%d]: %s\n", i, szDllName);
		//printf("-----------------------------------------\n");

		//现在去看看从该DLL中引入了哪些函数
		//我们来到该DLL的 IMAGE_TRUNK_DATA 数组（IAT：导入地址表）前面
		PIMAGE_THUNK_DATA32 pThunk = (PIMAGE_THUNK_DATA32)ImageRvaToVa(
			pNtHeaders, lpBaseAddress,
			pImportTable[i].OriginalFirstThunk, //【注意】这里使用的是OriginalFirstThunk
			NULL);

		for(j=0; memcmp(pThunk+j, &null_thunk, sizeof(null_thunk))!=0; j++)
		{
			IMPORTED_FUNCTION *func=new IMPORTED_FUNCTION;

			//这里通过RVA的最高位判断函数的导入方式，
			//如果最高位为1，按序号导入，否则按名称导入
			if(pThunk[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG32)
			{
				func->no=pThunk[j].u1.AddressOfData & 0xffff;
				//printf("\t [%d] \t %ld \t 按序号导入\n", j, pThunk[j].u1.AddressOfData & 0xffff);
			}
			else
			{
				//按名称导入，我们再次定向到函数序号和名称
				//注意其地址不能直接用，因为仍然是RVA！
				PIMAGE_IMPORT_BY_NAME pFuncName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(
					pNtHeaders,    lpBaseAddress,
					pThunk[j].u1.AddressOfData,
					NULL);
                
				func->no=pFuncName->Hint;
				func->funcName=(char *)pFuncName->Name;
				//printf("\t [%d] \t %ld \t %s\n", j, pFuncName->Hint, pFuncName->Name);
			}

			dll->funcNames.push_back(func);
		}

		dllTable.dllNames.push_back(dll);
	}

	return 0;
}

int CPEImporterTable::getImporterTable64(PIMAGE_NT_HEADERS pNtHeaders, LPBYTE lpBaseAddress, ImporterTable &dllTable)
{
	//导入表的rva：0x2a000;
	PIMAGE_NT_HEADERS64 pNtHeaders64=(PIMAGE_NT_HEADERS64)pNtHeaders;
	DWORD Rva_import_table = pNtHeaders64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(Rva_import_table == 0)
	{
		m_errMsg="no import table(64 bit)!";
		//关闭文件，句柄。。
		//getchar();
		return -7;
//				goto UNMAP_AND_EXIT;
	}

	//这个虽然是内存地址，但是减去文件开头的地址，就是文件地址了
	//这个地址可以直接从里面读取你想要的东西了
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(
		pNtHeaders, 
		lpBaseAddress, 
		Rva_import_table,
		NULL
		);

	//减去内存映射的首地址，就是文件地址了。。（很简单吧）
	//printf("FileAddress Of ImportTable: %p\n", ((DWORD)pImportTable - (DWORD)lpBaseAddress));

	//现在来到了导入表的面前：IMAGE_IMPORT_DESCRIPTOR 数组（以0元素为终止）
	//定义表示数组结尾的null元素！
	IMAGE_IMPORT_DESCRIPTOR null_iid;
	IMAGE_THUNK_DATA64 null_thunk;
	memset(&null_iid, 0, sizeof(null_iid));
	memset(&null_thunk, 0, sizeof(null_thunk));

	int i,j;
	//每个元素代表了一个引入的DLL。
	for(i=0; memcmp(pImportTable + i, &null_iid, sizeof(null_iid))!=0; i++)
	{
		//LPCSTR: 就是 const char*
		LPCSTR szDllName = (LPCSTR)ImageRvaToVa(
			pNtHeaders, lpBaseAddress, 
			pImportTable[i].Name, //DLL名称的RVA
			NULL);

		IMPORTED_Dll *dll=new IMPORTED_Dll;
		dll->dllName=szDllName;

		////拿到了DLL的名字
		//printf("-----------------------------------------\n");
		//printf("[%d]: %s\n", i, szDllName);
		//printf("-----------------------------------------\n");

		//现在去看看从该DLL中引入了哪些函数
		//我们来到该DLL的 IMAGE_TRUNK_DATA 数组（IAT：导入地址表）前面
		PIMAGE_THUNK_DATA64 pThunk = (PIMAGE_THUNK_DATA64)ImageRvaToVa(
			pNtHeaders, lpBaseAddress,
			pImportTable[i].OriginalFirstThunk, //【注意】这里使用的是OriginalFirstThunk
			NULL);

		for(j=0; memcmp(pThunk+j, &null_thunk, sizeof(null_thunk))!=0; j++)
		{
			IMPORTED_FUNCTION *func=new IMPORTED_FUNCTION;

			//这里通过RVA的最高位判断函数的导入方式，
			//如果最高位为1，按序号导入，否则按名称导入
			if(pThunk[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG64)
			{
				func->no=pThunk[j].u1.AddressOfData & 0xffff;
				//printf("\t [%d] \t %ld \t 按序号导入\n", j, pThunk[j].u1.AddressOfData & 0xffff);
			}
			else
			{
				//按名称导入，我们再次定向到函数序号和名称
				//注意其地址不能直接用，因为仍然是RVA！
				PIMAGE_IMPORT_BY_NAME pFuncName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(
					pNtHeaders,    lpBaseAddress,
					pThunk[j].u1.AddressOfData,
					NULL);
                
				func->no=pFuncName->Hint;
				func->funcName=(char *)pFuncName->Name;
				//printf("\t [%d] \t %ld \t %s\n", j, pFuncName->Hint, pFuncName->Name);
			}

			dll->funcNames.push_back(func);
		}

		dllTable.dllNames.push_back(dll);
	}

	return 0;
}
