// FtpProgressEvent.h: interface for the CFtpProgressEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPPROGRESSEVENT_H__EE7D96AC_F320_4265_AC6F_ADD8C2EAD89D__INCLUDED_)
#define AFX_FTPPROGRESSEVENT_H__EE7D96AC_F320_4265_AC6F_ADD8C2EAD89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "C++\FOUDATIONLIB\EVENTLIB\EVENTEMU-仿MFC的事件处理\IEvent.h"

class CFtpProgressEvent : public IEvent  
{
public:
	CFtpProgressEvent();
	CFtpProgressEvent(IEventRaisable *sender, string eventId, UINT fileId, UINT progress);
	virtual ~CFtpProgressEvent();

	UINT getFileId() const { return m_fileId; }
	void setFileId(UINT val) { m_fileId = val; }

	UINT getProgress() const { return m_progress; }
	void setProgress(UINT val) { m_progress = val; }

private:
	UINT m_fileId;  // 该变量未用
	UINT m_progress;
};

#endif // !defined(AFX_FTPPROGRESSEVENT_H__EE7D96AC_F320_4265_AC6F_ADD8C2EAD89D__INCLUDED_)
