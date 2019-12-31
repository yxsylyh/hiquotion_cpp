#pragma once

#include <C++\FoudationLib\FileSysLib\FileOperation.h>

template <class pFn>
class CDllDynamicLoader
{
public:
	CDllDynamicLoader(void){};
	~CDllDynamicLoader(void){};
	
	static pFn loadDll(CString dllFullpath, CString funcName, HINSTANCE &hdll)
	{
		// 如果 hdll 为空，则加载dll，否则直接使用
		if(!hdll)
		{
			if(dllFullpath.GetLength()<=0)
				return NULL;

			if(!CFileOperation::isFileExist(dllFullpath))
				return NULL;

			hdll=LoadLibrary(dllFullpath);
			if(!hdll)
				return NULL;
		}

		if(funcName.GetLength()<=0)
			return NULL;

		pFn fn=(pFn)GetProcAddress(hdll, funcName);
		if(!fn)
			return NULL;

		return fn;
	}

	static void freeDll(HINSTANCE hdll)
	{
		if(hdll)
		{
			FreeLibrary(hdll);
			hdll=NULL;
		}
	}
};
