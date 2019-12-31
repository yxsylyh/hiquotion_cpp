// FtpThreadBase.h: interface for the CFtpThreadBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPTHREADBASE_H__7227EFAA_1B82_4198_B366_F6A35646480F__INCLUDED_)
#define AFX_FTPTHREADBASE_H__7227EFAA_1B82_4198_B366_F6A35646480F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\MULTITHREADLIB\EventThread.h>

#define RETRY_TIMES 3

class CFtpThreadBase : public CEventThread  
{
public:
	CFtpThreadBase();
	virtual ~CFtpThreadBase();

	CDelegate Progress;
	CDelegate Failed;
	
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
	
	int getReadTimeout() const { return m_readTimeout; }
	void setReadTimeout(int val) { m_readTimeout = val; }

	HWND getHwnd() const { return m_hwnd; }
	void setHwnd(HWND val) { m_hwnd = val; }
	
	BOOL isRaiseWndEvent() const { return m_isRaiseWndEvent; }
	void setRaiseWndEvent(BOOL val) { m_isRaiseWndEvent = val; }

	UINT getThreadType() const { return m_threadType; }

	int getRetryTimes() const { return m_retryTimes; }
	void setRetryTimes(int val) { m_retryTimes = val; }

protected:
	CString m_ip;
	UINT m_port;
	CString m_user;
	CString m_psw;
	CString m_ftpFolder;
	CString m_ftpFileName;
	CString m_localFullPath;
	UINT m_localFileId;
	
	int m_connectTimeout;
	int m_readTimeout;
	
	HWND m_hwnd;
	
	BOOL m_isRaiseWndEvent;

	UINT m_threadType;

	int m_retryTimes;
};

#endif // !defined(AFX_FTPTHREADBASE_H__7227EFAA_1B82_4198_B366_F6A35646480F__INCLUDED_)
