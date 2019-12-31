// Tree.h: interface for the CTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE_H__C3FF54A0_38B1_4651_8903_11E458B353E9__INCLUDED_)
#define AFX_TREE_H__C3FF54A0_38B1_4651_8903_11E458B353E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class TreeNode>
class CTreeBase  
{
public:
	CTreeBase(){};
	virtual ~CTreeBase(){};

	TreeNode getRoot() const { return m_root; }
	void setRoot(TreeNode val) { root = val; }

private:
	static TreeNode m_root;
};

#endif // !defined(AFX_TREE_H__C3FF54A0_38B1_4651_8903_11E458B353E9__INCLUDED_)
