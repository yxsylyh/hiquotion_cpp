// SelfTreeNode.h: interface for the CSelfTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELFTREENODE_H__30EAA13B_77A8_4C35_A17F_0A65409B620B__INCLUDED_)
#define AFX_SELFTREENODE_H__30EAA13B_77A8_4C35_A17F_0A65409B620B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>

template <class T>
class CSelfTreeNode  
{
public:
	CSelfTreeNode()
	:m_parent(NULL), m_isDestroyChildren(FALSE)
	{

	};

	virtual ~CSelfTreeNode()
	{
		if(m_isDestroyChildren)
			m_children.destroyAll();
		m_children.clear();
	};

	void addChild(T t)
	{
		m_children.push_back(t);
	}

	T getChild(int index)
	{
		if(index<0 || index>=m_children.size())
			return NULL;

		return m_children.at(index);
	}

	T removeChild(int index)
	{
		if(index<0 || index>=m_children.size())
			return NULL;

		T t=m_children.at(index);
		m_children.remove(index);
		return t;
	}

	int getChildCount()
	{
		return m_children.size();
	}

	CPointerList<T> &getChildren()
	{
		return m_children;
	}

	T getParent() const { return m_parent; }
	void setParent(T val) { m_parent = val; }

	BOOL isDestroyChildren() const { return m_isDestroyChildren; }
	void setDestroyChildren(BOOL val) { m_isDestroyChildren = val; }

protected:
	CPointerList<T> m_children;
	T m_parent;
	BOOL m_isDestroyChildren;
};

#endif // !defined(AFX_SELFTREENODE_H__30EAA13B_77A8_4C35_A17F_0A65409B620B__INCLUDED_)
