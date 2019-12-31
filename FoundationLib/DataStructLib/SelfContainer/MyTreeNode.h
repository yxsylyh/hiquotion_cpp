// MyTreeNode.h: interface for the CMyTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTREENODE_H__D6CAC98A_8BDB_47AD_9F83_E99A1A62FBA7__INCLUDED_)
#define AFX_MYTREENODE_H__D6CAC98A_8BDB_47AD_9F83_E99A1A62FBA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SelfTreeNode.h"

class CMyTreeNode : public CSelfTreeNode<CMyTreeNode *>
{
public:
	CMyTreeNode();
	virtual ~CMyTreeNode();

};

#endif // !defined(AFX_MYTREENODE_H__D6CAC98A_8BDB_47AD_9F83_E99A1A62FBA7__INCLUDED_)
