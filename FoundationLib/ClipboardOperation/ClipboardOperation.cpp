// ClipboardOperation.cpp: implementation of the CClipboardOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClipboardOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardOperation::CClipboardOperation()
{

}

CClipboardOperation::~CClipboardOperation()
{

}

BOOL CClipboardOperation::open(HWND hwnd)
{
	return OpenClipboard(hwnd);
}

void CClipboardOperation::close()
{
	CloseClipboard();
}

void CClipboardOperation::clear()
{
	EmptyClipboard();
}

void CClipboardOperation::copyText( CString txt )
{
	if(txt.GetLength()<=0)
		return;

	HANDLE hClip;      //声明一个句柄  
	CString str;  
	char *pBuf;  
	clear();  //置空这个剪切板，且得到剪切板的所有权  
	hClip=GlobalAlloc(GMEM_MOVEABLE,txt.GetLength()+1);  
	//申请锁定一块存放数据的内存区域  
	pBuf=(char *)GlobalLock(hClip);//得到指向内存区域的第一个字节指针  
	strcpy(pBuf,txt);//将文本框的值拷贝到内存中  
	GlobalUnlock(hClip);//解除内存锁定  
	SetClipboardData(CF_TEXT,hClip);//设置数据到剪切板中  
	close();//关闭剪切板
}
