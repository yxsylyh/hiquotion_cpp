// StatuteStatusGraphBuilder.cpp: implementation of the CStatuteStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteStatusGraphBuilder.h"
#include "..\MemManager\MemManager.h"
#include <C++\FoundationLib\StringExtLib\StringExt.h>
#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteStatusGraphBuilder::CStatuteStatusGraphBuilder()
{
	m_graph=new CStatuteStatusGraph();
}

CStatuteStatusGraphBuilder::~CStatuteStatusGraphBuilder()
{
	// 分析程序退出之前，要删除所有规约条目
	CMemManager::destroyAllStatuteItems();

	delete m_graph;
}

int CStatuteStatusGraphBuilder::buildStatuteStatusGraph( CStatuteList *statuteList/*, CStatuteStatusGraph *m_graph*/ )
{
	if(statuteList->size()<=0)
		return -1;
	
	if(!m_graph)
		return -2;

	// 清空状态图
	m_graph->removeAllNodes();
	m_graph->removeAllArcs();
	
	// 清空上次执行该方法而存储的数据内容
	CMemManager::destroyAllStatuteItems();
	
	CStatuteItemList statuteItemList;
	// 转换规约式列表为规约式条目列表（就是带小点的那种）
	statuteList2StatuteItemList(statuteList, &statuteItemList);
	
#ifdef _DEBUG
	int count1=statuteItemList.size();
#endif
	
	CPointerList<CStatuteStatusGraphNode *> origNodeList;
	
	// 构建规约式状态图中的初始节点，通常是第一个大节点
	int ret=buildOrigNodeList(statuteItemList, origNodeList);
	if(ret!=0)
		return -3;
	
	// 把初始节点添加到规约式状态图中
	int i=0;
	for(i=0;i<origNodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=origNodeList.at(i);
		if(!node)
			continue;
		
		m_graph->addNode(node);
	}
	
	// #ifdef _DEBUG
	// 	printf("1st graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// 构造规约式状态图中的其他节点
	ret=buildOtherNodes(origNodeList, statuteItemList, m_graph);
	if(ret!=0)
		return -4;
	
	// #ifdef _DEBUG
	// 	printf("last graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// 构建成功，将第一个非初始节点设置为接受节点
	if(!m_graph->setAcceptNode())
		return -5;
	
	// #ifdef _DEBUG
	// 	int count2=statuteItemList.size();
	// 
	// 	printf("pre-statuteItemList element count is %d\n", count1);
	// 	printf("post-statuteItemList element count is %d\n", count2);
	// 	printf("MemManager statuteItem count is %d\n", CMemManager::getStatuteItemCount());
	// #endif
	
	statuteItemList.clear();
	
	// CMemManager中的规约条目在这里就不删除了，以备语法分析出现错误的时候查找信息之用
	// 但在程序运行结束之前要删除
	// 	CMemManager::destroyAllStatuteItems();
	
	return 0;
}

int CStatuteStatusGraphBuilder::buildStatuteStatusGraphFromDefText( std::string text, ILexer *lexer/*, CStatuteStatusGraph *m_graph*/, string statuteSymbol/*="=>"*/, string lineSplitter/*="\r\n"*/ )
{
	if(text.length()<=0)
	{
		m_errMsg="文本为空！";
		return -1;
	}
	
	CString txt=text.c_str();
	CStringArray txtArray;
	CStringExt::Split(txt, txtArray, lineSplitter.c_str());
	
	int ret=0;
	CStatuteList statuteList;
	
	for(int i=0;i<txtArray.GetSize();i++)
	{
		CString line=txtArray.GetAt(i);
		if(line.GetLength()<=0)
			continue;
		
		// 如果第一个字符不是a-z 或 A-Z，则认为该行是注释，并且跳过该行
		char first=line.GetAt(0);
		if(first<'A' || (first>'Z' && first<'a') || first>'z')
			continue;
		
		if(line.Find(statuteSymbol.c_str())<=0)
		{
			m_errMsg="规约式语法错误！不存在规约符号（" + statuteSymbol + "）";
			return -2;
		}
		
		CStringArray statuteStringArray;
		CStringExt::Split(line, statuteStringArray, statuteSymbol.c_str());
		
		std::string name=(LPTSTR)(LPCSTR)statuteStringArray.GetAt(0);
		std::string statuteString=(LPTSTR)(LPCSTR)statuteStringArray.GetAt(1);
		
		Statute *statute=new Statute;
		statute->tokenList.setSelfDestroy(TRUE);
		statute->statuteName=name;
		CValueList<string> errs;
		
// 		CKernelLexer lexer;
		ret=lexer->analyze(statuteString, statute->tokenList, errs);
		if(ret<0)
		{
			m_errMsg="词法分析失败！";
			if(errs.size()>0)
			{
				m_errMsg+="第一条错误信息是：";
				m_errMsg+=errs.at(0).c_str();
			}
			
			delete statute;
			
			return -3;
		}
		
		if(statute->tokenList.size()<=0)
		{
			m_errMsg="token列表为空！请检查规约式是否书写正确。";
			delete statute;
			return -4;
		}
		
		if(i==0 && statute->tokenList.size()!=1)
		{
			m_errMsg="请使用扩展文法，即保证第一个规约式中只含有一个token。";
			delete statute;
			return -5;
		}
		
		statuteList.push_back(statute);
	}
	
// 	m_builder.setStatuteList(&m_statuteList);
	
	return buildStatuteStatusGraph(&statuteList/*, m_graph*/);
}

int CStatuteStatusGraphBuilder::buildStatuteStatusGraphFromDefFile( std::string filePath, ILexer *lexer/*, CStatuteStatusGraph *m_graph*/, string statuteSymbol/*="=>"*/, string lineSplitter/*="\r\n"*/ )
{
	CFile fileLang;
// 	fileLang.Open("RegularDef.txt", CFile::shareDenyWrite);
	fileLang.Open(filePath.c_str(), CFile::shareDenyWrite);
//	char lang[10240];
	int len=fileLang.GetLength();
	char *lang=new char[len+1];
	fileLang.Read(lang, len);
	lang[len]='\0';
	fileLang.Close();
	
	std::string text=lang;

	return buildStatuteStatusGraphFromDefText(text, lexer/*, m_graph*/, statuteSymbol, lineSplitter);
}

int CStatuteStatusGraphBuilder::build()
{
	if(m_statuteList->size()<=0)
		return -1;
	
	if(!m_graph)
		return -2;
	
	// 清空上次执行该方法而存储的数据内容
	CMemManager::destroyAllStatuteItems();
	
	CStatuteItemList statuteItemList;
	// 转换规约式列表为规约式条目列表（就是带小点的那种）
	statuteList2StatuteItemList(m_statuteList, &statuteItemList);
	
#ifdef _DEBUG
	int count1=statuteItemList.size();
#endif
	
	CPointerList<CStatuteStatusGraphNode *> origNodeList;
	
	// 构建规约式状态图中的初始节点，通常是第一个大节点
	int ret=buildOrigNodeList(statuteItemList, origNodeList);
	if(ret!=0)
		return -3;
	
	// 把初始节点添加到规约式状态图中
	int i=0;
	for(i=0;i<origNodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=origNodeList.at(i);
		if(!node)
			continue;
		
		m_graph->addNode(node);
	}
	
	// #ifdef _DEBUG
	// 	printf("1st graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// 构造规约式状态图中的其他节点
	ret=buildOtherNodes(origNodeList, statuteItemList, m_graph);
	if(ret!=0)
		return -4;
	
	// #ifdef _DEBUG
	// 	printf("last graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// 构建成功，将第一个非初始节点设置为接受节点
	if(!m_graph->setAcceptNode())
		return -5;
	
	// #ifdef _DEBUG
	// 	int count2=statuteItemList.size();
	// 
	// 	printf("pre-statuteItemList element count is %d\n", count1);
	// 	printf("post-statuteItemList element count is %d\n", count2);
	// 	printf("MemManager statuteItem count is %d\n", CMemManager::getStatuteItemCount());
	// #endif
	
	statuteItemList.clear();
	
	// CMemManager中的规约条目在这里就不删除了，以备语法分析出现错误的时候查找信息之用
	// 但在程序运行结束之前要删除
	// 	CMemManager::destroyAllStatuteItems();
	
	return 0;
}

// 根据规约式列表，构造初始节点列表
// 返回值：
// 0，成功
// -1，规约式列表为空
int CStatuteStatusGraphBuilder::buildOrigNodeList( CStatuteItemList &statuteItemList, CPointerList<CStatuteStatusGraphNode *> &origNodeList )
{
	if(statuteItemList.size()<=0)
		return -1;

	origNodeList.destroyAll();
	origNodeList.clear();

	CStatuteItemList *currentList=new CStatuteItemList(statuteItemList);

	while(currentList->size()>0)
	{
		// 根据第一个规约式的规约名称来获取规约条目列表
		CStatuteItemList *lst=new CStatuteItemList();
		currentList->getStatuteItemListby1stStatuteName(lst);
		if(lst->size()<=0)
		{
			delete currentList;
			return -2;
		}
		
		// 对获取到的规约式条目列表做闭包运算
		lst->closure(statuteItemList);
		
		// 闭包运算后，将该规约式条目列表添加到状态图节点中
		CStatuteStatusGraphNode *node=new CStatuteStatusGraphNode(lst);
		node->setOrigNode(TRUE);
		origNodeList.push_back(node);

		CStatuteItemList *rest=new CStatuteItemList();
		
		// 从初始规约条目列表中把已经添加的条目去掉，剩下的如果还有，则重复循环
		CPointerList<StatuteItem *>::findDifferent((CPointerList<StatuteItem *> *)currentList, (CPointerList<StatuteItem *> *)lst, (CPointerList<StatuteItem *> *)rest);

		delete currentList;
		currentList=rest;
	}

	delete currentList;

	return 0;
}

// 从初始节点列表中的节点，构造后续节点
// 返回值：
// 0，成功
// -1，初始节点列表为空
// -2，初始规约条目列表为空
// -3，图指针为空
int CStatuteStatusGraphBuilder::buildOtherNodes( CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph )
{
	if(origNodeList.size()<=0)
		return -1;

	if(origStatuteItemList.size()<=0)
		return -2;

	if(!graph)
		return -3;
	
	// 针对初始节点列表中的每一个节点，构建后续节点（所构建的后续节点也会添加到初始节点列表中，以形成递归处理）
	for(int i=0;i<origNodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=origNodeList.at(i);
		if(!node)
			continue;
		
		buildPostNodes(node, origNodeList, origStatuteItemList, graph);
	}

	return 0;
}

// 从初始节点列表中的节点，构造后续节点
// 返回值：
// 0，成功
// -1，待处理节点指针为空
// -2，初始节点列表为空
// -3，初始规约条目列表为空
// -4，图指针为空
// -5，待处理节点中的规约条目列表为空
// -6，带处理节点中的规约条目列表中的元素个数为0
// -7，非终结规约条目列表的第一个规约条目为空
// -8，非终结规约条目列表的第一个规约条目中的规约式为空
// -9，非终结规约条目列表的第一个规约条目中的规约式中的当前条目token为空
// -10，非终结规约条目列表的第一个规约条目中的规约式中的当前条目token的token名称为空
// -11，走token名称的当前规约条目列表中的元素个数为0
// -12，当前节点中，在最终位置的规约条目多于一个，将导致语法二义性
// -13，节点包含的规约式条目列表中的第一个规约式条目为空
// -14，节点包含的规约式条目列表中的第一个规约式条目中的规约式为空
int CStatuteStatusGraphBuilder::buildPostNodes(CStatuteStatusGraphNode *node, CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph)
{
	if(!node)
		return -1;

	if(origNodeList.size()<=0)
		return -2;

	if(origStatuteItemList.size()<=0)
		return -3;

	if(!graph)
		return -4;
	
	// 从节点中获取到规约式条目列表
	CStatuteItemList *statuteItemList4Node=node->getStatuteItemList();
	if(!statuteItemList4Node)
		return -5;

	if(statuteItemList4Node->size()<=0)
		return -6;

	// 如果规约条目中存在最终位置的条目，说明该节点是终结点
	if(statuteItemList4Node->isContainItemInFinalPosition())
	{
		node->setFinal(TRUE);

		CStatuteItemList *finalList=new CStatuteItemList();
		finalList->setSelfDestroy(FALSE);
		statuteItemList4Node->getStatuteItemListInFinalPosition(finalList);
		if(finalList->size()>1)
		{
			delete finalList;
			return -12;
		}

		StatuteItem *statuteItem=statuteItemList4Node->at(0);
		if(!statuteItem)
		{
			delete finalList;
			return -13;
		}
		
		Statute *statute=statuteItem->statute;
		if(!statute)
		{
			delete finalList;
			return -14;
		}		
		
//		node->setIndexInStatuteList(statuteItem->indexInStatuteList);
		node->setStatuteOfFinal(statuteItem->statute);
		node->setTokenCount(statute->tokenList.size());

		delete finalList;
	}

	// 从规约式条目列表中获取那些小点位置不是在最后的规约式条目列表
	CStatuteItemList *currentList=new CStatuteItemList();
	statuteItemList4Node->getStatuteItemListNotinFinalPosition(currentList);
	if(currentList->size()<=0)
	{
		// 说明是最终节点。前面已经处理了针对最终节点要做的事，这里直接返回

		delete currentList;

		return 0;
	}

	while(currentList->size()>0)
	{
		StatuteItem *statuteItem=currentList->at(0);
		if(!statuteItem)
		{
			delete currentList;
			return -7;
		}
		
		statuteItem->checkPosition();
		
		Statute *statute=statuteItem->statute;
		if(!statute)
		{
			delete currentList;
			return -8;
		}
		
		MachineToken *token=statute->tokenList.at(statuteItem->itemPosition);
		if(!token)
		{
			delete currentList;
			return -9;
		}
		
		if(token->token=="")
		{
			delete currentList;
			return -10;
		}

		// 在当前规约式条目列表中，从当前条目位置走token的规约式（可能有多个，所以返回列表）
		CStatuteItemList *lst=new CStatuteItemList();
		currentList->getCurrentStatuteItemListbyTokenName(token->token, lst);
		if(lst->size()<=0)
		{
			delete lst;
			delete currentList;
			return -11;
		}

		// 从走token的规约式条目列表中，获取走过token后的规约式条目列表
		CStatuteItemList *nextList=new CStatuteItemList();
		lst->genNextStatuteItemList(nextList);
		
		// 针对走过token后的规约式条目列表做闭包运算
		nextList->closure(origStatuteItemList);
		
		// 如果走过token后的规约式条目列表已经构造规约状态图中的某个节点，则直接获取该节点
		// 否则，创建新节点
		CStatuteStatusGraphNode *postNode=NULL;
		string key=nextList->genStatuteKey();
		if(graph->containNodeby(key))
		{
			// 不能 DestroyAll() 列表中的所有元素，因为有些是在 CMemManager 里的，有些是从别的列表中引用过来的
			// DestroyAll() 会导致其他列表中获取元素内容失败！
			nextList->clear();
			delete nextList;

			postNode=graph->getNodeby(key);
		}
		else
		{
			postNode=new CStatuteStatusGraphNode(nextList);
			graph->addNode(postNode);
			origNodeList.push_back(postNode);
		}
		
		// 创建当前节点到该节点的弧
		CStatuteStatusGraphArc *arcToPostNode=new CStatuteStatusGraphArc(node, postNode, token);
		graph->addArc(arcToPostNode);
		
		// 从当前规约条目列表中把已经添加的条目去掉，剩下的如果还有，则重复循环
		CStatuteItemList *rest=new CStatuteItemList();
		CPointerList<StatuteItem *>::findDifferent((CPointerList<StatuteItem *> *)currentList, (CPointerList<StatuteItem *> *)lst, (CPointerList<StatuteItem *> *)rest);

// #ifdef _DEBUG
// 		printf("/*******************\n");
// 		printf("currentList size = %d\n lst size = %d\n rest size = %d\n\n", currentList->size(), lst->size(), rest->size());
// 		printf("ist graph info:\n\n");
// 		graph->printGraphInfo();
// 		printf("*******************/\n\n");
// #endif
		
		delete lst;
		delete currentList;
		currentList=rest;
	}

	delete currentList;

	return 0;
}

// 将规约式列表转换成规约式条目列表
void CStatuteStatusGraphBuilder::statuteList2StatuteItemList( CStatuteList *statuteList, CStatuteItemList *statuteItemList )
{
	if(!statuteList || !statuteItemList)
		return;

	statuteItemList->destroyAll();
	statuteItemList->clear();

	for(int i=0;i<statuteList->size();i++)
	{
		Statute *statute=statuteList->at(i);
		if(!statute)
			continue;

		StatuteItem *item=new StatuteItem(statute, i);
		CMemManager::addStatuteItem(item);
		statuteItemList->push_back(item);
	}
}
