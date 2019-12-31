// FtpDownloadThread.h: interface for the CFtpDownloadThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPDOWNLOADTHREAD_H__DDD6F168_0942_41BF_8679_CADE7E355466__INCLUDED_)
#define AFX_FTPDOWNLOADTHREAD_H__DDD6F168_0942_41BF_8679_CADE7E355466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtpThreadBase.h"
#include <C++\3rdParty\CKFtpLib\include\CkFtp2.h>
#include "FtpProgress.h"
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventHandler.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>

class CFtpDownloadThread : public CFtpThreadBase, public IEventHandler
{
public:
	CFtpDownloadThread();
	virtual ~CFtpDownloadThread();

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
};

#endif // !defined(AFX_FTPDOWNLOADTHREAD_H__DDD6F168_0942_41BF_8679_CADE7E355466__INCLUDED_)
