// FtpProgress.h: interface for the CFtpProgress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPPROGRESS_H__778EA6D4_0D9B_4A7C_BE7E_27E68E41B681__INCLUDED_)
#define AFX_FTPPROGRESS_H__778EA6D4_0D9B_4A7C_BE7E_27E68E41B681__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\3rdParty\CKFtpLib\include\CkFtp2Progress.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>

// 参考地址（在页面最后）：
// https://www.chilkatsoft.com/refdoc/vcCkFtp2Ref.html

class CFtpProgress : public CkFtp2Progress, public IEventRaisable
{
public:
	CFtpProgress();
	virtual ~CFtpProgress();

	CDelegate Progress;
// 	CDelegate Complete;

	void PercentDone(int pctDone, bool  *abort);
// 	void TaskCompleted(CkTask &task);
	
	UINT getFileId() const { return m_fileId; }
	void setFileId(UINT val) { m_fileId = val; }

private:
	UINT m_fileId;
};

#endif // !defined(AFX_FTPPROGRESS_H__778EA6D4_0D9B_4A7C_BE7E_27E68E41B681__INCLUDED_)
