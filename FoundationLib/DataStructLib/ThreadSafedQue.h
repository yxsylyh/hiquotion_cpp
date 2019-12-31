// ThradSafedQue.h: interface for the CThradSafedQue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THRADSAFEDQUE_H__105CC161_2D01_4345_94A4_A4CA44A1FBB3__INCLUDED_)
#define AFX_THRADSAFEDQUE_H__105CC161_2D01_4345_94A4_A4CA44A1FBB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <queue>
#include <afxmt.h>

template <class T>
class CThreadSafedQue : public std::queue<T>
{
public:
	CThreadSafedQue()
	{
		m_maxCount=0;
	};

	CThreadSafedQue(int maxCount)  // 队列中允许的最大元素个数maxCount，0为不限制
	{
		m_maxCount=maxCount;
	};

	virtual ~CThreadSafedQue(){};

	void put(T t);   // 如果定义了最大元素个数maxCount，即maxCount不为0，那么达到maxCount时，会等待，直到队列不满
	void get(T *t);  // 如果队列为空，会等待直到队列不空为止，保证返回的t不为NULL，但不能事先知道是否会等待，也不能预计等待时间
	BOOL get_NoWaiting(T *t/*, int waitTimeMS=0*/);  // 如果队列为空，则等待waitTimeMS，如果在这期间等待到了，则返回TRUE和t，否则返回FALSE和NULL，如果waitTimeMS为0，则不等待，能取到就返回TRUE和t，否则返回FALSE和NULL

	int getMaxCount() const { return m_maxCount; }
// 	void setMaxCount(int val) { m_maxCount = val; }

private:
	void waitUntilNotFull();  // 等待，直到队列不满
	void notifyItsNotFull();  // 通知队列已经不满了
	void waitUntilNotEmpty(); // 等待，直到队列不空
	void notifyItsNotEmpty(); // 通知队列已经不空了

private:
	CMutex m_mutex;
	CEvent m_event4NotFull;
	CEvent m_event4NotEmpty;

	int m_maxCount;
};

template <class T>
void CThreadSafedQue<T>::put( T t )
{
	while(m_maxCount>0 && size()>=m_maxCount)
		waitUntilNotFull();

	m_mutex.Lock();
	push(t);
	m_mutex.Unlock();
	notifyItsNotEmpty();
}

template <class T>
void CThreadSafedQue<T>::get( T *t )
{
	if(size()<=0)
		waitUntilNotEmpty();

	m_mutex.Lock();
	*t=front();
	pop();
	m_mutex.Unlock();
	notifyItsNotFull();
}

template <class T>
BOOL CThreadSafedQue<T>::get_NoWaiting( T *t/*, int waitTimeMS*/ )
{
	if(size<=0)
		return FALSE;

	m_mutex.Lock();
	*t=front();
	pop();
	m_mutex.Unlock();
	notifyItsNotFull();
}

template <class T>
void CThreadSafedQue<T>::waitUntilNotFull()
{
	m_event4NotFull.Lock();
}

template <class T>
void CThreadSafedQue<T>::notifyItsNotFull()
{
	m_event4NotFull.PulseEvent();	
}

template <class T>
void CThreadSafedQue<T>::waitUntilNotEmpty()
{
	m_event4NotEmpty.Lock();
}

template <class T>
void CThreadSafedQue<T>::notifyItsNotEmpty()
{
	m_event4NotEmpty.PulseEvent();	
}

#endif // !defined(AFX_THRADSAFEDQUE_H__105CC161_2D01_4345_94A4_A4CA44A1FBB3__INCLUDED_)
