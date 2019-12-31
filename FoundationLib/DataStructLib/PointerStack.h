// PointerStack.h: interface for the CPointerStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTERSTACK_H__A443B684_D01B_4077_B8D6_395A7E23C748__INCLUDED_)
#define AFX_POINTERSTACK_H__A443B684_D01B_4077_B8D6_395A7E23C748__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
using namespace std;

template<class T>
class CPointerStack : public stack<T>
{
public:
	CPointerStack()
	: m_isSelfDestroy(FALSE)
	{
		
	};

	virtual ~CPointerStack()
	{
		if(m_isSelfDestroy)
		{
			destroyAll();
		}
		clear();
	};

	T popout()
	{
		T t= top();
		pop();
		return t;
	}

	void clear()
	{
		for(int i=0;i<size();i++)
		{
			popout();
		}
	}

	void destroyAll()
	{
		for(int i=0;i<size();i++)
		{
			T t=popout();
			delete t;
		}
	};

	BOOL isSelfDestroy() const { return m_isSelfDestroy; }
	void setSelfDestroy(BOOL val) { m_isSelfDestroy = val; }

private:
	BOOL m_isSelfDestroy;
};

#endif // !defined(AFX_POINTERSTACK_H__A443B684_D01B_4077_B8D6_395A7E23C748__INCLUDED_)
