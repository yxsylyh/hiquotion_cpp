// CycledBufferT.h: interface for the CCycledBufferT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYCLEDBUFFERT_H__1922F61B_9980_4535_86D0_03EED63DF755__INCLUDED_)
#define AFX_CYCLEDBUFFERT_H__1922F61B_9980_4535_86D0_03EED63DF755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <struct T>
class CCycledBufferT  
{
public:
	CCycledBufferT();
	virtual ~CCycledBufferT();

	int push(T t);
	int pop(T t);

};

#endif // !defined(AFX_CYCLEDBUFFERT_H__1922F61B_9980_4535_86D0_03EED63DF755__INCLUDED_)
