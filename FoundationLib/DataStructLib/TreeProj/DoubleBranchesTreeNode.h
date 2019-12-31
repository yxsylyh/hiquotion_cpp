// DoubleBranchesTreeNode.h: interface for the CDoubleBranchesTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOUBLEBRANCHESTREENODE_H__01A973A8_6011_4B2B_A02E_F9C775D65248__INCLUDED_)
#define AFX_DOUBLEBRANCHESTREENODE_H__01A973A8_6011_4B2B_A02E_F9C775D65248__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeNodeBase.h"

template <class T>
class CDoubleBranchesTreeNode : public CTreeNodeBase<T>
{
public:
	CDoubleBranchesTreeNode()
		: CTreeNodeBase()
	{
		m_parent=NULL;
		m_left=NULL;
		m_right=NULL;
	};

	CDoubleBranchesTreeNode(T t, CDoubleBranchesTreeNode<T> *parent, CDoubleBranchesTreeNode<T> *left, CDoubleBranchesTreeNode<T> *right)
		: CTreeNodeBase(t)
	{
		m_parent=parent;
		m_left=left;
		m_right=right;
	};

	virtual ~CDoubleBranchesTreeNode(){};

	CDoubleBranchesTreeNode<T> * getParent() const { return m_parent; }
	void setParent(CDoubleBranchesTreeNode<T> * val) { m_parent = val; }
	
	CDoubleBranchesTreeNode<T> * getLeft() const { return m_left; }
	void setLeft(CDoubleBranchesTreeNode<T> * val) { m_left = val; }

	CDoubleBranchesTreeNode<T> * getRight() const { return m_right; }
	void setRight(CDoubleBranchesTreeNode<T> * val) { m_right = val; }

	BOOL isLeaf()
	{
		if(m_left || m_right)
			return FALSE;
		else
			return TRUE;
	};

private:
	CDoubleBranchesTreeNode<T> *m_parent;
	CDoubleBranchesTreeNode<T> *m_left;
	CDoubleBranchesTreeNode<T> *m_right;
};

#endif // !defined(AFX_DOUBLEBRANCHESTREENODE_H__01A973A8_6011_4B2B_A02E_F9C775D65248__INCLUDED_)
