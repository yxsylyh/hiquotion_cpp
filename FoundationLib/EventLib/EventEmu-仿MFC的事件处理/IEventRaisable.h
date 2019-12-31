// IEventRaisable.h: interface for the IEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IEVENTRAISABLE_H__565A105E_D4FF_4A9E_BFDF_67F190785403__INCLUDED_)
#define AFX_IEVENTRAISABLE_H__565A105E_D4FF_4A9E_BFDF_67F190785403__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 可抛出事件的类，需要继承该接口
class IEventRaisable  
{
public:
	IEventRaisable();
	virtual ~IEventRaisable();

};

#endif // !defined(AFX_IEVENTRAISABLE_H__565A105E_D4FF_4A9E_BFDF_67F190785403__INCLUDED_)
