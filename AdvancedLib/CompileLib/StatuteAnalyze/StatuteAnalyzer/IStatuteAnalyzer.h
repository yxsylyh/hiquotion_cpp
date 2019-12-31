// IStatuteAnalyzer.h: interface for the IStatuteAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISTATUTEANALYZER_H__D91D30EB_03AA_4FD5_A2E1_4B0C1DE38091__INCLUDED_)
#define AFX_ISTATUTEANALYZER_H__D91D30EB_03AA_4FD5_A2E1_4B0C1DE38091__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>
#include "..\..\LEX\LEXER\ILexer.h"
#include "StatuteList.h"
#include "StatuteTreeNode.h"

class IStatuteAnalyzer  
{
public:
	IStatuteAnalyzer(){};
	virtual ~IStatuteAnalyzer(){};

	virtual int analyze(CPointerList<MachineToken *> &tokenList, /*CStatuteList &origStatuteList,*/ CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList)=0;
};

#endif // !defined(AFX_ISTATUTEANALYZER_H__D91D30EB_03AA_4FD5_A2E1_4B0C1DE38091__INCLUDED_)
