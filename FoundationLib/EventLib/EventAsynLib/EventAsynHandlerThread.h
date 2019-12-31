// EventAsynHandlerThread.h: interface for the CEventAsynHandlerThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTASYNHANDLERTHREAD_H__6F01832F_F57A_4BF1_BCDF_DFB4B2117CCF__INCLUDED_)
#define AFX_EVENTASYNHANDLERTHREAD_H__6F01832F_F57A_4BF1_BCDF_DFB4B2117CCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\MULTITHREADLIB\ThreadBase.h>
#include <C++\AdvancedLib\MultiThreadPattern\ProductorConsumerLib\ProductorConsumerPattern.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>

// 事件异步处理线程类
class CEventAsynHandlerThread : public CThreadBase, public IEventRaisable
{
public:
	CEventAsynHandlerThread(CProductorConsumerPattern<IEvent *> *consumer);
	virtual ~CEventAsynHandlerThread();

	CDelegate Consume;

protected:
	UINT threadRun();

protected:
	CProductorConsumerPattern<IEvent *> *m_consumer;
};

#endif // !defined(AFX_EVENTASYNHANDLERTHREAD_H__6F01832F_F57A_4BF1_BCDF_DFB4B2117CCF__INCLUDED_)
