// TreeNode.h: interface for the CTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREENODE_H__55B154D1_FE12_4818_8BDD_B18C7229400E__INCLUDED_)
#define AFX_TREENODE_H__55B154D1_FE12_4818_8BDD_B18C7229400E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeNodeBase.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

template <class T>
class CTreeNode : public CTreeNodeBase<T>
{
public:
	CTreeNode()
	{
		m_children=new CPointerList<CTreeNode<T> *>();
		m_children->setSelfDestroy(TRUE);
		m_isDestroyeChildrenList=TRUE;
		m_parent=NULL;
		m_currentChild=NULL;
	};

	CTreeNode(T t, CPointerList<CTreeNode<T> *> *children, CTreeNode<T> *parent=NULL)
	{
		m_children=children;
		m_isDestroyeChildrenList=FALSE;
		m_parent=parent;
		m_currentChild=NULL;
	};

	virtual ~CTreeNode()
	{
		if(m_isDestroyeChildrenList)
			delete m_children;
	};

	CPointerList<CTreeNode<T> *> *getChildren() const { return m_children; }
	void setChildren(CPointerList<CTreeNode<T> *> *val) { m_children = val; }

	CTreeNode<T> * getParent() const { return m_parent; }
	void setParent(CTreeNode<T> * val) { m_parent = val; }

	BOOL isDestroyeChildrenList() const { return m_isDestroyeChildrenList; }
	void setDestroyeChildrenList(BOOL val) { m_isDestroyeChildrenList = val; }

	CTreeNode<T> * getCurrentChild() const { return m_currentChild; }
	void setCurrentChild(CTreeNode<T> * val) { m_currentChild = val; }
	
	void add(CTreeNode<T> *node)
	{
		if(!m_children)
			return;

		m_children->push_back(node);
		node->setParent(this);
	}

	void addT(T t)
	{
		if(!m_children)
			return;

		CTreeNode<T> *node=new CTreeNode<T>();
		node->setData(t);

		m_children->push_back(node);
		node->setParent(this);
	}

	CTreeNode<T> *get(int index)
	{
		if(!m_children)
			return NULL;

		if(index<0 || index>=m_children->size())
			return NULL;

		return m_children->at(index);
	}

	T getT(int index)
	{
		if(!m_children)
			return NULL;
		
		if(index<0 || index>=m_children->size())
			return NULL;
		
		return m_children->at(index)->getData();
	}

	CTreeNode<T> *getByT(T t)
	{
		if(!m_children)
			return NULL;
		
		for(int i=0;i<m_children->size();i++)
		{
			CTreeNode<IUIHandler *> *node=m_children->at(i);
			if(!node)
				continue;

			if(t==node->getData())
				return node;
		}

		return NULL;
	}

	CTreeNode<T> *remove(int index)
	{
		if(!m_children)
			return NULL;
		
		if(index<0 || index>=m_children->size())
			return NULL;

		CTreeNode<T> *node=m_children->remove(index);
		return node;
	}

	CTreeNode<T> *remove(CTreeNode<T> *child)
	{
		if(!child)
			return NULL;

		if(!m_children)
			return NULL;

		if(m_children->contain(child))
		{
			m_children->remove(child);
			return child;
		}

		return NULL;
	}

	CTreeNode<T> *removeT(T t)
	{
		if(!m_children)
			return NULL;

		if(m_children->size()<=0)
			return NULL;

		for(int i=0;i<m_children->size();i++)
		{
			if(t==getT(i))
			{
				CTreeNode<T> *node=remove(i);
				return node;
			}
		}

		return NULL;
	}

	int count()
	{
		if(!m_children)
			return -1;

		return m_children->size();
	}
	
	BOOL isLeaf()
	{
		if(!m_children)
			return TRUE;

		if(m_children->size()>0)
			return FALSE;
		else
			return TRUE;
	}

protected:
	CPointerList<CTreeNode<T> *> *m_children;
	CTreeNode<T> *m_parent;
	CTreeNode<T> *m_currentChild;
	BOOL m_isDestroyeChildrenList;
};

#endif // !defined(AFX_TREENODE_H__55B154D1_FE12_4818_8BDD_B18C7229400E__INCLUDED_)
