#include "StdAfx.h"
#include "UCmd.h"

HINSTANCE hModule;

pUCmmand1		mycmd;
pGetInfo	GetSAMIDToStr;

pGetInfo myGetName    ;     //读取姓名
pGetInfo myGetSex     ;     //读取性别
pGetInfo myGetFolk    ;     //读取民族
pGetInfo myGetBirth   ;     //读取出生
pGetInfo myGetAddr    ;     //读取住址
pGetInfo myGetIDNum   ;     //读取公民身份号码
pGetInfo myGetDep     ;     //读取签发机关
pGetInfo myGetBegin   ;     //读取有效期起
pGetInfo myGetEnd     ;     //读取有效期止
pGetInfo myGetNewAddr ;     //读取最新地址
pGetInfo myGetPicPath ;     //读取头像图片路径

// BOOL LoadDll();
// void FreeDll();

BOOL LoadDll()
{
	hModule=LoadLibrary(_T("RdCard.dll"));
	if(hModule ==NULL )
	{
		//AfxMessageBox(_T("加载动态库失败"));
		return FALSE;
	}

	mycmd		=(pUCmmand1)GetProcAddress(hModule,"UCommand1");

	GetSAMIDToStr	=(pGetInfo)GetProcAddress(hModule,"GetSAMIDToStr");

    myGetName    =(pGetInfo)GetProcAddress(hModule,"GetName");
    myGetSex     =(pGetInfo)GetProcAddress(hModule,"GetSex");
    myGetFolk    =(pGetInfo)GetProcAddress(hModule,"GetFolk");
    myGetBirth   =(pGetInfo)GetProcAddress(hModule,"GetBirth");
    myGetAddr    =(pGetInfo)GetProcAddress(hModule,"GetAddr");
    myGetIDNum   =(pGetInfo)GetProcAddress(hModule,"GetIDNum");
    myGetDep     =(pGetInfo)GetProcAddress(hModule,"GetDep");
    myGetBegin   =(pGetInfo)GetProcAddress(hModule,"GetBegin");
    myGetEnd     =(pGetInfo)GetProcAddress(hModule,"GetEnd");
    myGetNewAddr =(pGetInfo)GetProcAddress(hModule,"GetNewAddr");
    myGetPicPath =(pGetInfo)GetProcAddress(hModule,"GetBmpPath");


	if( (mycmd==NULL) )
	{
		return FALSE;
	}
    else
    {
        return TRUE;
    }
}

void FreeDll()
{
	if(hModule !=NULL )
	{
		FreeLibrary(hModule);
		hModule=NULL;
	}	

}
