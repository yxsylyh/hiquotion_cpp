// FtpDownload.h: interface for the CFtpDownload class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPDOWNLOAD_H__0653673C_1F76_4795_BA3D_855BFF52E17D__INCLUDED_)
#define AFX_FTPDOWNLOAD_H__0653673C_1F76_4795_BA3D_855BFF52E17D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventHandler.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>
#include <C++\3rdParty\CKFtpLib\include\CkFtp2.h>
#include "FtpProgress.h"

class CFtpDownload : public IEventHandler, public IEventRaisable
{
public:
	CFtpDownload();
	virtual ~CFtpDownload();

	int download();

	CDelegate Progress;
	
	CString getIp() const { return m_ip; }
	void setIp(CString val) { m_ip = val; }
	
	UINT getPort() const { return m_port; }
	void setPort(UINT val) { m_port = val; }
	
	CString getUser() const { return m_user; }
	void setUser(CString val) { m_user = val; }
	
	CString getPsw() const { return m_psw; }
	void setPsw(CString val) { m_psw = val; }
	
	CString getFtpFolder() const { return m_ftpFolder; }
	void setFtpFolder(CString val) { m_ftpFolder = val; }
	
	CString getFtpFileName() const { return m_ftpFileName; }
	void setFtpFileName(CString val) { m_ftpFileName = val; }
	
	CString getLocalFullPath() const { return m_localFullPath; }
	void setLocalFullPath(CString val) { m_localFullPath = val; }
	
	UINT getLocalFileId() const { return m_localFileId; }
	void setLocalFileId(UINT val) { m_localFileId = val; }
	
	int getConnectTimeout() const { return m_connectTimeout; }
	void setConnectTimeout(int val) { m_connectTimeout = val; }

	HWND getHwnd() const { return m_hwnd; }
	void setHwnd(HWND val) { m_hwnd = val; }
	
	CString getErrMsg() const { return m_message; }

protected:
	void OnProgress(IEvent *e);
	// 	void OnComplete(IEvent *e);
	
	void sendProgressEvent(UINT progress);
	
protected:
	Declare_Event_Map()
		
private:
	CkFtp2 m_ftp;
	CFtpProgress m_progress;
	
	CString m_ip;
	UINT m_port;
	CString m_user;
	CString m_psw;
	CString m_ftpFolder;
	CString m_ftpFileName;
	CString m_localFullPath;
	UINT m_localFileId;
	
	int m_connectTimeout;

	HWND m_hwnd;

	CString m_message;

	int m_retryTimes;
};

#endif // !defined(AFX_FTPDOWNLOAD_H__0653673C_1F76_4795_BA3D_855BFF52E17D__INCLUDED_)
