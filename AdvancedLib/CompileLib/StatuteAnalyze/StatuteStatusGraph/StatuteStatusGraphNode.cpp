// MergenceStatusGraphNode.cpp: implementation of the CMergenceStatusGraphNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteStatusGraphNode.h"
#include "..\..\LEX\LEXER\ILexer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteStatusGraphNode::CStatuteStatusGraphNode()
: m_isOrigNode(FALSE), m_isFinal(FALSE), /*m_indexInStatuteList(-1)*/m_statuteOfFinal(NULL), m_tokenCount(-1), m_isAccepted(FALSE), m_errMsg(""), m_itemList(NULL)
{

}

CStatuteStatusGraphNode::CStatuteStatusGraphNode(CStatuteItemList *itemList)
: m_isOrigNode(FALSE), m_isFinal(FALSE), /*m_indexInStatuteList(-1)*/m_statuteOfFinal(NULL), m_tokenCount(-1), m_isAccepted(FALSE), m_errMsg("")
{
	m_itemList=itemList;
}

CStatuteStatusGraphNode::CStatuteStatusGraphNode( BOOL isFinal )
: m_isOrigNode(FALSE), m_isFinal(isFinal), /*m_indexInStatuteList(-1)*/m_statuteOfFinal(NULL), m_tokenCount(-1), m_isAccepted(FALSE), m_errMsg(""), m_itemList(NULL)
{
	
}

CStatuteStatusGraphNode::CStatuteStatusGraphNode(std::string errMsg)
: m_isOrigNode(FALSE), m_isFinal(FALSE), /*m_indexInStatuteList(-1)*/m_statuteOfFinal(NULL), m_tokenCount(-1), m_isAccepted(FALSE), m_errMsg(errMsg), m_itemList(NULL)
{

}

CStatuteStatusGraphNode::CStatuteStatusGraphNode(BOOL isFinal, std::string errMsg)
: m_isOrigNode(FALSE), m_isFinal(isFinal), /*m_indexInStatuteList(-1)*/m_statuteOfFinal(NULL), m_tokenCount(-1), m_isAccepted(FALSE), m_errMsg(errMsg), m_itemList(NULL)
{

}

CStatuteStatusGraphNode::~CStatuteStatusGraphNode()
{
	if(m_itemList)
	{
		m_itemList->clear();
		delete m_itemList;
		m_itemList=NULL;
	}
}

// 根据名称来获取出弧列表（因为出弧中可能有名字相同的）
void CStatuteStatusGraphNode::getOutArcsBy( MachineToken *token, CPointerList<CStatuteStatusGraphArc *> &arcs )
{
	if(!token)
		return;

	if(getOutArcCount()<=0)
		return;

	arcs.clear();

	for(int i=0;i<getOutArcCount();i++)
	{
		CStatuteStatusGraphArc *arc=getOutArc(i);
		if(!arc)
			continue;

		MachineToken *arcDatai=arc->getArcData();
		if(!arcDatai)
			continue;

		// 如果 arcData 的 type 是 var，则哪个弧的 type 与 arcData 的 token 一致，才添加
		// 如果 arcData 的 type 不是 var，则哪个弧的 token 与 arcData 的 token 一致，才添加
		if(isArcDataEquals(token, arcDatai))
//		if(token->type=="var" && arcDatai->type==token->token)
			arcs.push_back(arc);
// 		else if(arcDatai->token==token->token)
// 			arcs.push_back(arc);
	}
}

// 判断 token 和 弧数据arcData 是否相等
BOOL CStatuteStatusGraphNode::isArcDataEquals(MachineToken *token, MachineToken *arcData)
{
	// 是检查类型，则判断语法定义arcData的字面值token与源码token的类型是否相同
	if(arcData->check4Statute==CheckType4Statute)
	{
		if(arcData->token==token->type)
// 		if(arcData->isCheckSubtype)
// 		{
// 			if(arcData->subtype==token->subtype)
// 				return TRUE;
// 			else
// 				return FALSE;
// 		}
// 		else
			return TRUE;
	}
	else if(token->check4Statute==CheckToken4Statute && arcData->token==token->token)
		return TRUE;
// 	else if(arcData->token==token->token)
// 		return TRUE;

	return FALSE;
}

BOOL CStatuteStatusGraphNode::hasOutArcToNode(CStatuteStatusGraphNode *nodeTo)
{
	for(int i=0;i<getOutArcCount();i++)
	{
		CStatuteStatusGraphArc *arc=getOutArc(i);
		if(!arc)
			continue;

		CStatuteStatusGraphNode *to=arc->getNodeTo();
		if(!to)
			continue;

		if(to==nodeTo)
			return TRUE;
	}

	return FALSE;
}

// 节点是否包含指定名称的出弧
BOOL CStatuteStatusGraphNode::containOutArcBy( MachineToken *arcData )
{
	if(!arcData)
		return FALSE;
	
	if(getOutArcCount()<=0)
		return FALSE;
	
	for(int i=0;i<getOutArcCount();i++)
	{
		CStatuteStatusGraphArc *arc=getOutArc(i);
		if(!arc)
			continue;
		
		if(arc->getArcData()==arcData)
			return TRUE;
	}

	return FALSE;
}

void CStatuteStatusGraphNode::add( StatuteItem *item )
{
	if(!m_itemList)
		return;

	m_itemList->push_back(item);
}

void CStatuteStatusGraphNode::add( Statute *statute, int indexInStatuteList )
{
	if(!m_itemList)
		return;
	
	m_itemList->push_back(new StatuteItem(statute, indexInStatuteList));
}

void CStatuteStatusGraphNode::add( Statute *statute, int indexInStatuteList, int itemPosition )
{
	if(!m_itemList)
		return;
	
	m_itemList->push_back(new StatuteItem(statute, indexInStatuteList, itemPosition));
}

std::string CStatuteStatusGraphNode::printStatuteItemListInfo()
{
	if(!m_itemList)
		return "";

	return m_itemList->genStatuteKey();
}
