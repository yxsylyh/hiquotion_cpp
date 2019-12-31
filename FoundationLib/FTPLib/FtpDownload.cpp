// FtpDownload.cpp: implementation of the CFtpDownload class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpDownload.h"
#include <C++\3rdParty\CKFtpLib\include\CkSettings.h>
#include "FtpProgressEvent.h"
#include "FtpMessage.h"
#include "..\FileSysLib\FolderOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpDownload::CFtpDownload()
: m_port(21), m_connectTimeout(0), m_ftpFolder("/")
{
	m_progress.Progress+=this;
}

CFtpDownload::~CFtpDownload()
{
	m_progress.Progress-=this;
	m_ftp.put_AbortCurrent(true);
	m_ftp.Disconnect();
	CkSettings::cleanupMemory();
}

int CFtpDownload::download()
{
	CString msg;
	bool success = m_ftp.UnlockComponent("AARONKFTP_p9PO06K09ZnG");
	if(success==false)
	{
		m_message="FTP 组件授权失败！\n";
		m_message+=m_ftp.lastErrorText();
// 		sendFailedEvent();
		return -1;
	}
	
	m_ftp.put_Hostname((LPTSTR)(LPCSTR)m_ip);
	m_ftp.put_Port((int)m_port);
	m_ftp.put_Username((LPTSTR)(LPCSTR)m_user);
	m_ftp.put_Password((LPTSTR)(LPCSTR)m_psw);
	
	if(m_connectTimeout>0)  // 默认是 30 秒
		m_ftp.put_ConnectTimeout(m_connectTimeout);
	m_ftp.put_Passive(true);  // 默认是 true
	m_ftp.put_PassiveUseHostAddr(true);  // 忽略服务端本机ip地址
	
	m_ftp.put_EventCallbackObject(&m_progress);
	
	success = m_ftp.Connect();
	if (success==false) {
		msg.Format("ftp 连接服务器(%s:%d) 失败", m_ip, m_port);
		m_message=(LPTSTR)(LPCSTR)msg;
// 		sendFailedEvent();
		return -2;
	}
	
	success = m_ftp.ChangeRemoteDir("/");
	if (success==false){
		msg.Format("更改 ftp 目录为根目录时失败", m_ftpFolder);
		m_message=(LPTSTR)(LPCSTR)msg;
// 		sendFailedEvent();
		return -3;
	}
	
	success = m_ftp.ChangeRemoteDir(m_ftpFolder);
	if (success==false){
		msg.Format("更改 ftp 目录为 %s 时失败", m_ftpFolder);
		m_message=(LPTSTR)(LPCSTR)msg;
// 		sendFailedEvent();
		return -4;
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
// 		sendFailedEvent();
		return -5;
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
// 		sendFailedEvent();
		return -6;
	}
	
	m_ftp.Disconnect();

// 	sendSuccessEvent();
	
	return 0;
}

Begin_Event_Map(CFtpDownload)
Event_Map(&m_progress, "Progress", OnProgress)
End_Event_Map()

void CFtpDownload::OnProgress( IEvent *e )
{
	CFtpProgressEvent *ee=(CFtpProgressEvent *)e;
	// 	if(m_hwnd)
	// 		PostMessage(m_hwnd, FU_PROGRESS, (WPARAM)this, (LPARAM)ee->getProgress());
	sendProgressEvent(ee->getProgress());
}

void CFtpDownload::sendProgressEvent( UINT progress )
{
// 	if(m_isRaiseWndEvent)
// 	{
// 		if(m_hwnd)
// 			PostMessage(m_hwnd, FD_PROGRESS, (WPARAM)this, (LPARAM)progress);
// 	}
// 	else
// 	{
		CFtpProgressEvent e(this, "Progress", m_localFileId, progress);
		Progress.raiseEvent(this, &e);
// 	}
}
