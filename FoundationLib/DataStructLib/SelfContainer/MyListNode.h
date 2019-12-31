// MyListNode.h: interface for the CMyListNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLISTNODE_H__51C60070_FD16_40CF_A343_D68135AD6856__INCLUDED_)
#define AFX_MYLISTNODE_H__51C60070_FD16_40CF_A343_D68135AD6856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SelfListNode.h"

class CMyListNode : public CSelfListNode<CMyListNode *>
{
public:
	CMyListNode();
	virtual ~CMyListNode();

};

#endif // !defined(AFX_MYLISTNODE_H__51C60070_FD16_40CF_A343_D68135AD6856__INCLUDED_)
