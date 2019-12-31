// ClipboardOperation.h: interface for the CClipboardOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPBOARDOPERATION_H__A230704F_F442_450C_BF51_4491138CDB1C__INCLUDED_)
#define AFX_CLIPBOARDOPERATION_H__A230704F_F442_450C_BF51_4491138CDB1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClipboardOperation  
{
public:
	CClipboardOperation();
	virtual ~CClipboardOperation();

	static BOOL open(HWND hwnd=NULL);
	static void close();
	static void clear();

	static void copyText(CString txt);

};

#endif // !defined(AFX_CLIPBOARDOPERATION_H__A230704F_F442_450C_BF51_4491138CDB1C__INCLUDED_)
