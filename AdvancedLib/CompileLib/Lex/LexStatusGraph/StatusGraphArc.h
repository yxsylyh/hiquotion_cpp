// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__D470FC6E_B41A_4F64_BC8B_C9B10E801720__INCLUDED_)
#define AFX_ARC_H__D470FC6E_B41A_4F64_BC8B_C9B10E801720__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StatusGraphNode.h"
#include <C++\FoundationLib\DataStructLib\SelfContainer\SelfGraphArc.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\IRegularExpression.h>

class CStatusGraphNode;

class CStatusGraphArc : public CSelfGraphArc<CStatusGraphNode *, IRegularExpression *>
{
public:
	CStatusGraphArc();
	CStatusGraphArc(CStatusGraphNode *from, CStatusGraphNode *to, IRegularExpression *re);
	virtual ~CStatusGraphArc();

// 	IRegularExpression * getRe() const { return m_re; }
// 	void setRe(IRegularExpression * val) { m_re = val; }
// 
// private:
// 	IRegularExpression *m_re;
};

#endif // !defined(AFX_ARC_H__D470FC6E_B41A_4F64_BC8B_C9B10E801720__INCLUDED_)
