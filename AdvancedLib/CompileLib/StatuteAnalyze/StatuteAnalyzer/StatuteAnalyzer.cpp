// MergenceAnalyzer.cpp: implementation of the CMergenceAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteAnalyzer.h"
#include <sstream>
#include <C++\FoundationLib\StringExtLib\StringExt.h>
//#include "../StatuteAnalyzer/StatuteStatusMachineBuilder.h"
#include "../../KernelLex/KernelLexer/KernelLexer.h"
#include "StatuteTreeNode.h"
#include <C++\FoundationLib\DataStructLib\PointerStack.h>
#include <sstream>
#include "../MemManager/MemManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// static CStatuteItemList g_statuteItemList;
static CPointerList<CStatuteTreeNode *> g_statuteTreeNodeList;
static CPointerList<MachineToken *> g_tokenList;

extern CLog log;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteAnalyzer::CStatuteAnalyzer()
{
	g_statuteTreeNodeList.setSelfDestroy(TRUE);
	g_tokenList.setSelfDestroy(TRUE);

#ifdef _DEBUG
	log.setProjectName("StatuteAnalyzer");
#endif

}

CStatuteAnalyzer::~CStatuteAnalyzer()
{
	// 分析程序退出之前，要删除所有规约条目
	CMemManager::destroyAllStatuteItems();
}

// int CStatuteAnalyzer::analyzeFromSrcText( std::string text, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList )
// {
// 	CPointerList<MachineToken *> tokenList;
// 	tokenList.setSelfDestroy(TRUE);
// 	
// // 	CKernelLexer lex;
// 	CValueList<string> errlst;
// 	int ret=lexer->analyze(text, tokenList, errlst);
// 	if(ret!=0)
// 	{
// 		stringstream ss;
// 		ss<<"源代码有词法错误！错误码是 " << ret;
// 		printf(ss.str().c_str());
// 		printf("\n");
// 		return -1;
// 	}
// 	
// // 	CStatuteTreeNode root;
// // 	CPointerList<MachineToken *> grammer_errList;
// 	return analyze(tokenList, root, errorTokenList);
// 
// // 	ret=m_kernelAnalyzer.analyze(tokenList, &root, grammer_errList);
// // 	if(ret!=0)
// // 	{
// // 		stringstream ss;
// // 		ss<<"源代码有语法错误！错误码是 " << ret;
// // 		printf(ss.str().c_str());
// // 		printf("\n");
// // 		system("pause");
// // 		return -2;
// // 	}
// // 	
// // 	printf("源码分析成功！");
// // 	return 0;
// }
// 
// int CStatuteAnalyzer::analyzeFromSrcFile( std::string filePath, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList )
// {
// 	CFile fileLang;
// 	fileLang.Open(filePath.c_str(), CFile::shareDenyWrite);
// 	//	char lang[10240];
// 	int len=fileLang.GetLength();
// 	char *lang=new char[len+1];
// 	fileLang.Read(lang, len);
// 	lang[len]='\0';
// 	fileLang.Close();
// 	
// 	std::string text=lang;
// 
// 	return analyzeFromSrcText(text, lexer, root, errorTokenList);
// }



// 生成规约树
// 参数：
// tokenList：源码的token列表
// origStatuteList：初始规约列表
// root：返回的规约树的根
// errorTokenList：出错时返回的错误Token列表
// 返回值：
//  1，分析成功
//  0，分析完成，但有错误，需要查看并处理errorTokenList
// -1，token列表为空
// -2，规约状态图中没有节点
// -3，初始化当前节点失败
// -4，扫描完所有的字符串后，当前节点是可规约时，执行规约出现错误
// -5，没有走到可接受节点，分析失败
// -11，规约时，当前节点中记录的规约列表索引超出列表范围
// -12，规约时，当前节点中记录的当前索引的规约式为空
// -13，规约式的token个数非正，或超出了当前token栈中元素的个数
// -14，规约后，graph走规约后的规约名称路径不成功，说明graph的构建有问题（按理应该是一定成功的）
int CStatuteAnalyzer::analyze(CPointerList<MachineToken *> &tokenList, /*CStatuteList &origStatuteList,*/ CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList)
{
#ifdef _DEBUG
	log.writeDebug("语法分析函数入口！");
#endif
				
	if(tokenList.size()<=0)
		return -1;

	CPointerStack<CStatuteStatusGraphNode *> statuteStatusGraphNodeStack;
	CPointerStack<CStatuteTreeNode *> statuteTreeNodeStack;

// 	statuteTreeNodeStack.setSelfDestroy(TRUE);

	errorTokenList.destroyAll();
	errorTokenList.clear();

  /*
	1. graph初始化当前节点
	2. 读取tokenList的当前token
	3. 如果从graph的当前节点能够经过token走到下一节点，则
		1) 将token打包成规约树节点，并入规约树节点栈
		2) 将graph的当前节点入规约状态图节点栈
		3) 将下一节点作为当前节点
	否则
		1) 如果当前节点是可接受节点，则
			a 弹出规约树节点栈中的一个节点，将该节点添加到规约树根root节点成为其中一个孩子节点
			b 清空规约树节点栈，清空规约状态图节点栈
			c graph初始化当前节点
		2) 否则，如果当前节点是终结点，则
			a 根据该规约式中token的个数n，弹出规约树节点栈中的n个节点
			b 从n个节点中获取n个token
			c 新建一个tokenParent，两个position属性分别设置为第一个token和最后一个token的position值
			d 新建一个规约树节点nodeParent，并包装了tokenParent
			e 将n个节点添加到nodeParent作为其孩子结点
			f 根据该规约式中token的个数n，弹出规约状态图节点栈中的n个节点
			g 将规约状态图节点栈的栈顶节点，作为当前节点
			h graph经过规约式名称所在弧，走入下一节点
			i 将这下一节点标记为当前节点
			j 将nodeParent节点添加到规约树节点栈中
			k 回退tokenList中的一个token
		3) 否则
			a 将该token添加到errTokenList中
x			b 如果当前token是tokenList中的最后一个，则返回0（分析完成，但有错误，需要查看并处理errorTokenList）
x			  否则
x				1> 建立一个token stack
x				2> 将graph中获取到的下一token(nextToken)
x				3> 将graph中所有弧作为arcList
x				4> 在arcList中获取下一token的所有弧列表arcList
x				5> 只要arcList中的弧多于一个，就添加该token到token stack中，并重复4
x				6> 如果tokenList中没有下一token了，则将当前token之后的所有token添加到错误列表中
x				7> 如果arcList中只有一个弧，说明找到了唯一的规约式，但可能规约式前面的信息有丢失（因为错误的token引起）
x					根据规约式token的个数m来创建m个规约树节点，其中后面几个是

	*/

	if(m_machine.getNodeCount()<=0)
		return -2;

	// 1. graph初始化当前节点
	if(!m_machine.initCurrentNode())
		return -3;

	// 清空上次执行该方法而存储的数据内容
	g_tokenList.destroyAll();
	g_tokenList.clear();
	g_statuteTreeNodeList.destroyAll();
	g_statuteTreeNodeList.clear();

	// 将当前节点入栈
	statuteStatusGraphNodeStack.push(m_machine.getCurrentNode());

#ifdef _DEBUG
	CString str;
	str.Format("token个数：%d", tokenList.size());
	log.writeDebug((LPTSTR)(LPCSTR)str);
#endif
	
	//////////////////////////////////////////////////////////////////////////
	// DEBUG
	int i=0;
	int sz=tokenList.size();
	for (i=0;i<tokenList.size();i++)
	{
#ifdef _DEBUG
		log.writeDebug("当前节点信息：");
		log.writeDebug(m_machine.getCurrentNode()->printStatuteItemListInfo());
#endif
		
 		// 3. 读取tokenList的当前token
 		MachineToken *token=tokenList.at(i);
 		if(!token)
 			continue;

#ifdef _DEBUG
		str.Format("当前token：%s", token->toString().c_str());
		log.writeDebug((LPTSTR)(LPCSTR)str);
#endif

// #if _DEBUG
// 	printf("%s", token->token.c_str());
// #endif

		CStatuteTreeNode *node=NULL;
		int ret=m_machine.goThrough(token);
		switch(ret)
		{
		case 1: // 成功

#ifdef _DEBUG
			log.writeDebug("从当前节点走当前token成功！");
#endif

// 			3. 如果从graph的当前节点能够经过token走到下一节点，则
// 			1) 将token打包成规约树节点，并入规约树节点栈
// 			2) 将graph的当前节点入规约状态图节点栈
// 			3) 将下一节点作为当前节点
			node=new CStatuteTreeNode(token);
			g_statuteTreeNodeList.push_back(node);

			statuteTreeNodeStack.push(node);
			statuteStatusGraphNodeStack.push(m_machine.getCurrentNode());

// #if _DEBUG
// 			printf("\n", token->token.c_str());
// #endif
			
			break;
		case 0: // 不存在名称为token的出弧

#ifdef _DEBUG
			log.writeDebug("从当前节点不存在走当前token的出弧！");
#endif

// #if _DEBUG
// 			printf("\b", token->token.c_str());
// #endif

// 			1) 如果当前节点是可接受节点，则
// 			a 弹出规约树节点栈中的一个节点，将该节点添加到规约树根root节点成为其中一个孩子节点
// 			b 清空规约树节点栈，清空规约状态图节点栈
// 			c graph初始化当前节点
			if(m_machine.isCurrentNodeAccepted())
			{
#ifdef _DEBUG
				log.writeDebug("当前结点是可接受结点！");
#endif

				CStatuteTreeNode *nodeAccepted=statuteTreeNodeStack.popout();
				root->addChild(nodeAccepted);
				statuteStatusGraphNodeStack.clear();
				statuteTreeNodeStack.clear();
				m_machine.initCurrentNode();

// #if _DEBUG
// 	printf("Statute tree node stack size is %d", (int)statuteTreeNodeStack.size());
// #endif

				continue;
			}
// 			2) 否则，如果当前节点是终结点，则
// 			a 根据该规约式中token的个数n，弹出规约树节点栈中的n个节点
// 			b 从n个节点中获取n个token
// 			c 新建一个statuteTreeNodeParent，两个position属性分别设置为第一个token和最后一个token的position值
// 			d 新建一个规约树节点statuteTreeNodeParent，并包装了tokenParent
// 			e 将n个节点添加到statuteTreeNodeParent作为其孩子结点
// 			f 根据该规约式中token的个数n，弹出规约状态图节点栈中的n个节点
// 			g 将规约状态图节点栈的栈顶节点，作为当前节点
// 			h graph经过规约式名称所在弧，走入下一节点
// 			i 将这下一节点标记为当前节点
// 			j 将statuteTreeNodeParent节点添加到规约树节点栈中
// 			k 回退tokenList中的一个token
			else if(m_machine.isCurrentNodeFinal())
			{
#ifdef _DEBUG
				log.writeDebug("当前结点是终结点！执行规约操作。");
#endif
				
				int ret=statute(m_machine.getStatuteStatusGraph(), /*origStatuteList,*/ statuteStatusGraphNodeStack, statuteTreeNodeStack);
				if(ret!=0)
					return ret-10;

				// 			k 回退tokenList中的一个token
				i--;
			}
			else
			{
#ifdef _DEBUG
				log.writeDebug("存在语法错误！");
#endif

				errorTokenList.push_back(token);
				break;
			}
			break;
		default: // 出错
// 			3) 否则，将该token添加到errTokenList中
#ifdef _DEBUG
			log.writeDebug("出错，将当前结点放入错误列表！");
#endif
			
			errorTokenList.push_back(token);
			break;
		}

	}

	if(i==(int)tokenList.size())  // 说明扫描完源字符串
	{
#ifdef _DEBUG
		log.writeDebug("所有结点都处理完毕！");
#endif
		
		while(!m_machine.isCurrentNodeAccepted() && m_machine.isCurrentNodeFinal())
		{
#ifdef _DEBUG
			log.writeDebug("当前结点不是可接受节点，但是终结点，则执行规约操作。");
#endif
			
			int ret=statute(m_machine.getStatuteStatusGraph(), /*origStatuteList,*/ statuteStatusGraphNodeStack, statuteTreeNodeStack);
			if(ret!=0)
				return -4;

#ifdef _DEBUG
			log.writeDebug("当前节点信息：");
			log.writeDebug(m_machine.getCurrentNode()->printStatuteItemListInfo());
#endif
		}

		if(!m_machine.isCurrentNodeAccepted()/* && !m_graph->isCurrentNodeFinal()*/)
		{
#ifdef _DEBUG
			log.writeDebug("当前结点仍不是可接受结点！报错。");
#endif
			
			return -5;
		}

		CStatuteTreeNode *nodeAccepted=statuteTreeNodeStack.popout();
		root->addChild(nodeAccepted);
		statuteStatusGraphNodeStack.clear();
		statuteTreeNodeStack.clear();
		m_machine.initCurrentNode();
			
// #if _DEBUG
// 		printf("At the end, statute tree node stack size is %d\n", (int)statuteTreeNodeStack.size());
// #endif
	}
	else
	{
#ifdef _DEBUG
		log.writeDebug("存在语法错误，分析终止。");
#endif
		
		return -6;
	}
	
// #if _DEBUG
// 	printf("Global statute tree node list size is %d\n", (int)g_statuteTreeNodeList.size());
// 	printf("Global machine token list size is %d\n", (int)g_tokenList.size());
// #endif

#ifdef _DEBUG
	log.writeDebug("分析成功！");
	log.writeDebug("规约树信息：");
	log.writeDebug(root->getTreeNodeInfo());
#endif

	return 0;
}

// 返回值：
//  0，成功
//xx -1，规约时，当前节点中记录的规约列表索引超出列表范围
// -2，规约时，当前节点中记录的当前索引的规约式为空
// -3，规约式的token个数非正，或超出了当前token栈中元素的个数
// -4，规约后，graph走规约后的规约名称路径不成功，说明graph的构建有问题（按理应该是一定成功的）
int CStatuteAnalyzer::statute(CStatuteStatusGraph *graph, /*CStatuteList &origStatuteList,*/ CPointerStack<CStatuteStatusGraphNode *> &statuteStatusGraphNodeStack, CPointerStack<CStatuteTreeNode *> &statuteTreeNodeStack)
{
#ifdef _DEBUG
	log.writeDebug("规约函数入口！");
#endif
				
	// 			a 根据该规约式中token的个数n，弹出规约树节点栈中的n个节点
	// 			b 从n个节点中获取n个token
	// 			c 新建一个statuteTreeNodeParent，两个position属性分别设置为第一个token和最后一个token的position值
	// 			d 新建一个规约树节点statuteTreeNodeParent，并包装了tokenParent
	// 			e 将n个节点添加到statuteTreeNodeParent作为其孩子结点
// 	int index=graph->getIndexInStatuteItemList();
// 	if(index<0 || index>=origStatuteList.size())
// 		return -1;
	
//	Statute *statute=origStatuteList.at(index);
	Statute *statute=graph->getStatuteOfFinal();
	if(!statute)
		return -2;
	
	int n=statute->tokenList.size();
	if(n<=0 || n>statuteTreeNodeStack.size())
		return -3;
	
	CStatuteTreeNode *statuteTreeNodeParent=new CStatuteTreeNode(&statuteTreeNodeStack, n);
	g_statuteTreeNodeList.push_back(statuteTreeNodeParent);
	
	MachineToken *tokenParent=new MachineToken();
#ifdef _DEBUG
	CString str;
	str.Format("父token：", tokenParent->toString().c_str());
	log.writeDebug((LPTSTR)(LPCSTR)str);
#endif
				
	g_tokenList.push_back(tokenParent);
	tokenParent->token=statute->statuteName;
	tokenParent->type="statute";
	
	statuteTreeNodeParent->setMachineToken(tokenParent);
	statuteTreeNodeParent->genTokenPosition();
	
	// 			f 根据该规约式中token的个数n，弹出规约状态图节点栈中的n个节点
	// 			g 将规约状态图节点栈的栈顶节点，作为当前节点
	for(int p=0;p<n;p++)
	{
		statuteStatusGraphNodeStack.popout();
	}
	
	m_machine.setCurrentNode(statuteStatusGraphNodeStack.top());
#ifdef _DEBUG
	str.Format("当前结点是：", m_machine.getCurrentNode()->printStatuteItemListInfo());
	log.writeDebug((LPTSTR)(LPCSTR)str);
#endif
	
	// 			h graph经过规约式名称所在弧，走入下一节点
	// 			i 将这下一节点标记为当前节点
	// 			j 将statuteTreeNodeParent节点添加到规约树节点栈中
	int ret=m_machine.goThrough(tokenParent);
	if(ret!=1)
	{
#ifdef _DEBUG
		log.writeDebug("走当前结点失败！");
#endif

		return -4;
	}
	
#ifdef _DEBUG
	log.writeDebug("走当前结点成功！");
#endif
	
	statuteTreeNodeStack.push(statuteTreeNodeParent);
	statuteStatusGraphNodeStack.push(m_machine.getCurrentNode());

#ifdef _DEBUG
	log.writeDebug("正常退出的规约函数出口！");
#endif
	return 0;
}
