// FtpDownloadThread.cpp: implementation of the CFtpDownloadThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpDownloadThread.h"
#include <C++\3rdParty\CKFtpLib\include\CkSettings.h>
#include "FtpProgressEvent.h"
#include <C++\FoudationLib\StringExtLib\StringExt.h>
#include "FtpMessage.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>
#include <C++\FoudationLib\FileSysLib\FileOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpDownloadThread::CFtpDownloadThread()
{
	m_threadType=0;
	m_progress.Progress+=this;
}

CFtpDownloadThread::~CFtpDownloadThread()
{
	m_progress.Progress-=this;
	m_ftp.put_AbortCurrent(true);
	m_ftp.Disconnect();
	CkSettings::cleanupMemory();
}

UINT CFtpDownloadThread::threadRun()
{
	CString msg;
	bool success = m_ftp.UnlockComponent("AARONKFTP_p9PO06K09ZnG");
	if(success==false)
	{
		m_message="FTP 组件授权失败！\n";
		m_message+=m_ftp.lastErrorText();
		sendFailedEvent();
		return -1;
	}
	
	m_ftp.put_Hostname((LPTSTR)(LPCSTR)m_ip);
	m_ftp.put_Port((int)m_port);
	m_ftp.put_Username((LPTSTR)(LPCSTR)m_user);
	m_ftp.put_Password((LPTSTR)(LPCSTR)m_psw);
	
	if(m_connectTimeout>0)  // 默认是 30 秒
		m_ftp.put_ConnectTimeout(m_connectTimeout);
	if(m_readTimeout>0)
		m_ftp.put_ReadTimeout(m_readTimeout);
	m_ftp.put_Passive(true);  // 默认是 true
	m_ftp.put_PassiveUseHostAddr(true);  // 忽略服务端本机ip地址

	m_ftp.put_EventCallbackObject(&m_progress);

	success = m_ftp.Connect();
	if (success==false) {
		msg.Format("ftp 连接服务器(%s:%d) 失败", m_ip, m_port);
		m_message=(LPTSTR)(LPCSTR)msg;
		sendFailedEvent();
		return -1;
	}

	success = m_ftp.ChangeRemoteDir(m_ftpFolder);
	if (success==false){
		msg.Format("更改 ftp 目录为 %s 失败", m_ftpFolder);
		m_message=(LPTSTR)(LPCSTR)msg;
		sendFailedEvent();
		return -1;
	}

	m_ftp.put_RestartNext(true); // 下次重传
	CString log;
	log.Format("D:\\ftpDownloadThread%d.log", m_localFileId);
	m_ftp.put_DebugLogFilePath((LPTSTR)(LPCSTR)log);

	// 获取路径
	CString path=CFolderOperation::getFolderFromFullPath(m_localFullPath);

	// 路径不存在，则创建
	if(!CFolderOperation::isFolderExist(path))
		CFolderOperation::createDirEx(path);

	// 路径还不存在，说明创建失败，或没有权限
	if(!CFolderOperation::isFolderExist(path))
	{
		msg.Format("创建路径 %s 失败！", path);
		m_message=(LPTSTR)(LPCTSTR)msg;
		sendFailedEvent();
		return -1;
	}

	int retryTimes=m_retryTimes;
	success = m_ftp.GetFile((LPTSTR)(LPCSTR)m_ftpFileName, (LPTSTR)(LPCSTR)m_localFullPath);
	while(success==false && retryTimes>0)
	{
		success = m_ftp.GetFile((LPTSTR)(LPCSTR)m_ftpFileName, (LPTSTR)(LPCSTR)m_localFullPath);
		if(success!=false)
			break;

		retryTimes--;
	}
	if (success==false)
	{
		msg.Format("文件 %s 下载失败！\n%s", m_localFullPath, m_ftp.lastErrorText());
		m_message=(LPTSTR)(LPCTSTR)msg;
		sendFailedEvent();
		return -1;
	}

	sendSuccessEvent();
	
	m_ftp.Disconnect();

	return 0;
}

Begin_Event_Map(CFtpDownloadThread)
Event_Map(&m_progress, "Progress", OnProgress)
End_Event_Map()

void CFtpDownloadThread::OnProgress( IEvent *e )
{
	CFtpProgressEvent *ee=(CFtpProgressEvent *)e;
	sendProgressEvent(ee->getProgress());
}

void CFtpDownloadThread::sendProgressEvent( UINT progress )
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FD_PROGRESS, (WPARAM)this, (LPARAM)progress);
	}
	else
	{
		CFtpProgressEvent e(this, "Progress", m_localFileId, progress);
		Progress.raiseEvent(this, &e);
	}
}

void CFtpDownloadThread::sendSuccessEvent()
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FD_SUCCESS, (WPARAM)this, 0);
	}
	else
	{
		IEvent e(this, "Success");
		Progress.raiseEvent(this, &e);
	}
}

void CFtpDownloadThread::sendFailedEvent()
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FD_FAILED, (WPARAM)this, 0);
	}
	else
	{
		IEvent e(this, "Failed", m_message.c_str());
		Progress.raiseEvent(this, &e);
	}
}
