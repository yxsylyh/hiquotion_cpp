// TreeNodeBase.h: interface for the CTreeNodeBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREENODEBASE_H__EB513814_CE8B_4ABB_9331_83C90F0EC84D__INCLUDED_)
#define AFX_TREENODEBASE_H__EB513814_CE8B_4ABB_9331_83C90F0EC84D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T>
class CTreeNodeBase  
{
public:
	CTreeNodeBase()
	{
	};
	CTreeNodeBase(T t)
	{
		m_t=t;
	};
	virtual ~CTreeNodeBase(){};

	T getData() const { return m_t; }
	void setData(T val) { m_t = val; }
	
	virtual BOOL isLeaf(){ return TRUE;};

protected:
	T m_t;
};

#endif // !defined(AFX_TREENODEBASE_H__EB513814_CE8B_4ABB_9331_83C90F0EC84D__INCLUDED_)
