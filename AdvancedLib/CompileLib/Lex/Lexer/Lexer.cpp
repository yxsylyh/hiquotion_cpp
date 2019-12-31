// Lexer.cpp: implementation of the CLexer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lexer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLexer::CLexer()
{

}

CLexer::~CLexer()
{

}

// 返回值：
// -1：参数为空
// -2：状态机内部错误（当前结点为空）
int CLexer::analyze(string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList)
{
	if(text.size()<=0)
		return -1;
	
	tokenList.destroyAll();
	tokenList.clear();
	errList.clear();
	
	m_machine.init();
	for(int i=0;i<text.size();i++)
	{
		char ch=text[i];
		int ret=m_machine.accept(ch);
		switch(ret)
		{
		case -1:
			return -2;
			break;
		case 1:
			continue;
			break;
		case 0:
			if(m_machine.isFinalStatus())
			{
				MachineToken *token=new MachineToken;
				token->token=m_machine.getString();
				token->type=m_machine.getStringType();
				token->subtype=m_machine.getStringSubType();
				token->endPosition=i-1;
				token->startPosition=i-token->token.size();
				tokenList.push_back(token);
			}
			else
			{
				errList.push_back(m_machine.getErrMsg());
			}
			
			m_machine.init();
			i--;
		}
	}
	
	if(m_machine.isFinalStatus())
	{
		MachineToken *token=new MachineToken;
		token->token=m_machine.getString();
		token->type=m_machine.getStringType();
		token->subtype=m_machine.getStringSubType();
		token->endPosition=i-1;
		token->startPosition=i-token->token.size();
		tokenList.push_back(token);
	}
	else
	{
		errList.push_back(m_machine.getErrMsg());
	}
	
	m_machine.init();
	i--;
	
	return 0;
}

void CLexer::setLexStatusGraph(CLexStatusGraph *graph)
{
	m_machine.setGraphic(graph);
}
