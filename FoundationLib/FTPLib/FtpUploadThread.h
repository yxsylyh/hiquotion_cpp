// FtpUploadThread.h: interface for the CFtpUploadThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPUPLOADTHREAD_H__F4EC9567_4772_4F6B_9277_A1AB26E708A6__INCLUDED_)
#define AFX_FTPUPLOADTHREAD_H__F4EC9567_4772_4F6B_9277_A1AB26E708A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtpThreadBase.h"
#include <C++\3rdParty\CKFtpLib\include\CkFtp2.h>
#include "FtpProgress.h"
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventHandler.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>

class CFtpUploadThread : public CFtpThreadBase, public IEventHandler
{
public:
	CFtpUploadThread();
	virtual ~CFtpUploadThread();

// 	CDelegate Progress;
// 	CDelegate Failed;

protected:
	UINT threadRun();

	void OnProgress(IEvent *e);
// 	void OnComplete(IEvent *e);

	void sendProgressEvent(UINT progress);
	void sendSuccessEvent();
	void sendFailedEvent();

protected:
	Declare_Event_Map()

private:
	CkFtp2 m_ftp;
	CFtpProgress m_progress;

// 	CString m_ip;
// 	UINT m_port;
// 	CString m_user;
// 	CString m_psw;
// 	CString m_ftpFolder;
// 	CString m_ftpFileName;
// 	CString m_localFullPath;
// 	UINT m_localFileId;
// 
// 	int m_connectTimeout;
// 	HWND m_hwnd;
// 
// 	BOOL m_isRaiseWndEvent;
};

#endif // !defined(AFX_FTPUPLOADTHREAD_H__F4EC9567_4772_4F6B_9277_A1AB26E708A6__INCLUDED_)
