// StatusMachine.cpp: implementation of the CStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LexStatusMachine.h"
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\IRegularExpression.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLexStatusMachine::CLexStatusMachine()
: m_initStatus(-1)
{
}

CLexStatusMachine::CLexStatusMachine(CLexStatusGraph *graphic)
: m_initStatus(-1)
{
	m_graphic=graphic;
}

CLexStatusMachine::~CLexStatusMachine()
{

}

// 恢复初始状态，即指向开始状态
void CLexStatusMachine::init()
{
	m_string="";

	if(!m_graphic)
	{
		m_currentNode=NULL;
		return;
	}

	m_currentNode=m_graphic->getStartNode();
	m_initStatus=1;
}

// 是否接受给定的字符
// 1，接受
// 0，不接受
// -1，当前结点指针为空
int CLexStatusMachine::accept(char ch)
{
	if(!m_currentNode)
		return -1;

	for(int i=0;i<m_currentNode->getOutArcCount();i++)
	{
		CStatusGraphArc *arc=m_currentNode->getOutArc(i);
		if(!arc)
			continue;

		IRegularExpression *re=arc->getArcData();
		if(!re)
			continue;

		// 如果接受，则保存当前字符，将状态移动到下一个结点，返回TRUE（接受）
		if(re->accept(&ch))
		{
			m_string+=ch;
			m_currentNode=arc->getNodeTo();

			m_initStatus=0;

			return 1;
		}
	}

	return 0;
}

// 当不接受某字符时，判断是否在结束状态
// 1，是
// 0，不是
// -1，当前结点指针为空
int CLexStatusMachine::isFinalStatus()
{
	if(!m_currentNode)
		return -1;

	if(m_currentNode->isFinal())
		return 1;
	else
		return 0;
}

// 获取状态机中字符串的类型（该类型来自当前终态结点）
std::string CLexStatusMachine::getStringType()
{
	if(!m_currentNode)
		return "";

	if(!m_currentNode->isFinal())
		return "";

	return m_currentNode->getType();
}

// 获取状态机中字符串的子类型（该类型来自当前终态结点）
std::string CLexStatusMachine::getStringSubType()
{
	if(!m_currentNode)
		return "";
	
	if(!m_currentNode->isFinal())
		return "";
	
	return m_currentNode->getSubtype();
}

// 获取状态机错误信息（该信息来自非终态结点）
std::string CLexStatusMachine::getErrMsg()
{
	if(!m_currentNode)
		return "";

	if(m_currentNode->isFinal())
		return "";

	return m_currentNode->getErrMsg();
}
