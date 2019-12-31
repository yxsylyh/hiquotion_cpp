// DoubleBranchesTree.h: interface for the CDoubleBranchesTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOUBLEBRANCHESTREE_H__D26467B7_9B03_43B9_A5C5_74A7175E4173__INCLUDED_)
#define AFX_DOUBLEBRANCHESTREE_H__D26467B7_9B03_43B9_A5C5_74A7175E4173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeBase.h"
#include "DoubleBranchesTreeNode.h"

template <class T>
class CDoubleBranchesTree : public CTreeBase<CDoubleBranchesTreeNode<T> *>  
{
public:
	CDoubleBranchesTree()
	{
	};
	virtual ~CDoubleBranchesTree(){};

};

#endif // !defined(AFX_DOUBLEBRANCHESTREE_H__D26467B7_9B03_43B9_A5C5_74A7175E4173__INCLUDED_)
