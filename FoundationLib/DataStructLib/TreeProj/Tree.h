// Tree.h: interface for the CTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE_H__65CD8FA8_CACC_4EE1_B3D2_ED40FEB91EBE__INCLUDED_)
#define AFX_TREE_H__65CD8FA8_CACC_4EE1_B3D2_ED40FEB91EBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeBase.h"
#include "TreeNode.h"

template <class T>
class CTree : public CTreeBase<CTreeNode<T> *>
{
public:
	CTree()
	{
	};
	virtual ~CTree(){};

};

#endif // !defined(AFX_TREE_H__65CD8FA8_CACC_4EE1_B3D2_ED40FEB91EBE__INCLUDED_)
