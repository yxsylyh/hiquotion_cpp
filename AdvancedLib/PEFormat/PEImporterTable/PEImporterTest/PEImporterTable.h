#pragma once

#include <string>
#include <vector>

using namespace std;


/******************************************************************************
* 
* PE 文件导入函数信息的获取
* 
* 获取内容：
* 
* PE文件导入的DLL文件名列表
* 每个导入DLL文件的导入函数列表
* 每个导入函数包括函数号和函数名（如果函数名为空，则只能以函数号导入）
* 
******************************************************************************/

struct IMPORTED_FUNCTION
{
	DWORD no;           // 序号
	string funcName;  // 函数名（如果函数名为空，则为按序号导入）
};

struct IMPORTED_Dll
{
	string dllName;
	vector<IMPORTED_FUNCTION *> funcNames;

	~IMPORTED_Dll()
	{ for each(IMPORTED_FUNCTION *func in funcNames){ delete func; } }
};

struct ImporterTable
{
	vector<IMPORTED_Dll *> dllNames;

	void clear()
	{
		for each(IMPORTED_Dll *dll in dllNames){ delete dll; }
	}

	~ImporterTable()
	{ clear(); }
};

class CPEImporterTable
{
public:
	CPEImporterTable(void);
	~CPEImporterTable(void);

//	int getImporterTable(string file, vector<vector<string > *> &dllNames);
	int getImporterTable(string file, ImporterTable &dllTable);

	string getErrMsg(){ return m_errMsg; };

protected:
	int getImporterTable64(PIMAGE_NT_HEADERS pNtHeaders, LPBYTE lpBaseAddress, ImporterTable &dllTable);

	string m_errMsg;
};

