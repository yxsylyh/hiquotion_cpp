// FtpUploadThread.cpp: implementation of the CFtpUploadThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpUploadThread.h"
#include <C++\3rdParty\CKFtpLib\include\CkSettings.h>
#include "FtpProgressEvent.h"
#include <C++\FoudationLib\StringExtLib\StringExt.h>
#include "FtpMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpUploadThread::CFtpUploadThread()
{
	m_threadType=1;
	m_progress.Progress+=this;
}

CFtpUploadThread::~CFtpUploadThread()
{
	m_progress.Progress-=this;
	m_ftp.put_AbortCurrent(true);
	m_ftp.Disconnect();
	CkSettings::cleanupMemory();
}

Begin_Event_Map(CFtpUploadThread)
Event_Map(&m_progress, "Progress", OnProgress)
End_Event_Map()

UINT CFtpUploadThread::threadRun()
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
	if(success==false)
	{
		// m_ftpFolder 肯定不会是 "/"
		// 需要在 FTP 上创建多级目录
		CStringArray divfolders;
		CStringArray folders;
		CStringExt::Split(m_ftpFolder, divfolders, "/");
		if(divfolders.GetSize()==1)
		{
			// 因为如果目录存在也会返回false，所以不能判断返回结果
			success=m_ftp.CreateRemoteDir((LPTSTR)(LPCSTR)m_ftpFolder);
		}
		else /*if(divfolders.GetSize()>1)*/
		{
			folders.Add(divfolders[0]);
			int i=0;
			for(i=1;i<divfolders.GetSize();i++)
			{
				CString tmp;
				tmp.Format("%s/%s", folders[i-1], divfolders[i]);
				folders.Add(tmp);
			}

			for(i=1;i<divfolders.GetSize();i++)
			{
				// 因为如果目录存在也会返回false，所以不能判断返回结果
				success=m_ftp.CreateRemoteDir(folders[i]);
				Sleep(200);
				success=m_ftp.ChangeRemoteDir(folders[i]);
				if (success==false)
				{
					msg.Format("更改 ftp 目录为 %s 失败", folders[i]);
					m_message=(LPTSTR)(LPCSTR)msg;
					sendFailedEvent();
					return -1;
				}
			}
		}
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
	log.Format("D:\\ftpUploadThread%d.log", m_localFileId);
	m_ftp.put_DebugLogFilePath((LPTSTR)(LPCSTR)log);

	int retryTimes=m_retryTimes;
	success = m_ftp.PutFile((LPTSTR)(LPCSTR)m_localFullPath, (LPTSTR)(LPCSTR)m_ftpFileName);
	while(success==false && retryTimes>0)
	{
		success = m_ftp.PutFile((LPTSTR)(LPCSTR)m_localFullPath, (LPTSTR)(LPCSTR)m_ftpFileName);
		if(success!=false)
			break;
		
		retryTimes--;
	}
	if (success==false)
	{
		msg.Format("文件 %s 上传失败！\n%s", m_localFullPath, m_ftp.lastErrorText());
		m_message=(LPTSTR)(LPCTSTR)msg;
		sendFailedEvent();
		return -1;
	}

	sendSuccessEvent();
	
	m_ftp.Disconnect();
	
	return 0;
}

void CFtpUploadThread::OnProgress( IEvent *e )
{
	CFtpProgressEvent *ee=(CFtpProgressEvent *)e;
// 	if(m_hwnd)
// 		PostMessage(m_hwnd, FU_PROGRESS, (WPARAM)this, (LPARAM)ee->getProgress());
	sendProgressEvent(ee->getProgress());
}

void CFtpUploadThread::sendProgressEvent( UINT progress )
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FU_PROGRESS, (WPARAM)this, (LPARAM)progress);
	}
	else
	{
		CFtpProgressEvent e(this, "Progress", m_localFileId, progress);
		Progress.raiseEvent(this, &e);
	}
}

void CFtpUploadThread::sendSuccessEvent()
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FU_SUCCESS, (WPARAM)this, 0);
	}
	else
	{
		IEvent e(this, "Success");
		Progress.raiseEvent(this, &e);
	}
}

void CFtpUploadThread::sendFailedEvent()
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FU_FAILED, (WPARAM)this, 0);
	}
	else
	{
		IEvent e(this, "Failed", m_message.c_str());
		Progress.raiseEvent(this, &e);
	}
}
