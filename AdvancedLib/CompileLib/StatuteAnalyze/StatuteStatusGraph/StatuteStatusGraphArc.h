// MergenceStatusGraphArc.h: interface for the CMergenceStatusGraphArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGENCESTATUSGRAPHARC_H__3D53ACD0_ED0C_4743_A813_1BA760074A9F__INCLUDED_)
#define AFX_MERGENCESTATUSGRAPHARC_H__3D53ACD0_ED0C_4743_A813_1BA760074A9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StatuteStatusGraphNode.h"
#include <C++\FoundationLib\DataStructLib\SelfContainer\SelfGraphArc.h>
#include <string>
#include "..\..\LEX\LEXER\ILexer.h"

class CStatuteStatusGraphNode;

class CStatuteStatusGraphArc : public CSelfGraphArc<CStatuteStatusGraphNode *, MachineToken *>
{
public:
	CStatuteStatusGraphArc();
	CStatuteStatusGraphArc(CStatuteStatusGraphNode *from, CStatuteStatusGraphNode *to, MachineToken *data/*, BOOL isGotoAnotherStatute*/);

	virtual ~CStatuteStatusGraphArc();
};

#endif // !defined(AFX_MERGENCESTATUSGRAPHARC_H__3D53ACD0_ED0C_4743_A813_1BA760074A9F__INCLUDED_)
