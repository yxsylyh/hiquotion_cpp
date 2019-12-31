// StatuteTreeNode.h: interface for the CStatuteTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTETREENODE_H__CBA7BC2A_7556_4633_B045_518917CD57AB__INCLUDED_)
#define AFX_STATUTETREENODE_H__CBA7BC2A_7556_4633_B045_518917CD57AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\SelfContainer\SelfTreeNode.h>
#include "../StatuteStatusGraph/StatuteStatusGraphNode.h"
#include "..\..\Lex\Lexer\Lexer.h"
#include <C++\FoundationLib\DataStructLib\PointerStack.h>

class CStatuteTreeNode : public CSelfTreeNode<CStatuteTreeNode *>
{
public:
	CStatuteTreeNode();
	CStatuteTreeNode(MachineToken *machineToken);
	// 将指定栈中的节点添加到自身的孩子结点中
	// 注：栈中节点顺序不需要调整，即依次弹出的节点直接添加到自身孩子结点列表中的
	CStatuteTreeNode(CPointerStack<CStatuteTreeNode *> *reversedMachineTokenStack);
	// 将指定栈中的指定个数个节点添加到自身孩子结点中
	// 注：栈中节点顺序是反的，即依次弹出的节点需要插入到自身孩子列表中的首端
	CStatuteTreeNode(CPointerStack<CStatuteTreeNode *> *machineTokenStack, int popoutCount);
	virtual ~CStatuteTreeNode();

	// 获取孩子结点中的token，组成列表
	void genTokenPosition();

	// 获取树节点信息（包括子节点），用于测试
	std::string getTreeNodeInfo();
	// 获取指定级别的树节点信息，level表示当前节点是在树的第几层，用于测试
	std::string getTreeNodeInfoByLevel(CStatuteTreeNode *node, unsigned int level, int space=4);

	// 打印树节点信息（包括子节点），用于测试
	void printTreeNodeInfo();
	// 打印指定级别的树节点信息，level表示当前节点是在树的第几层，用于测试
	void printTreeNodeInfoByLevel(CStatuteTreeNode *node, unsigned int level);

	MachineToken * getMachineToken() const { return m_machineToken; }
	void setMachineToken(MachineToken * val) { m_machineToken = val; }

private:
	MachineToken *m_machineToken;
};

#endif // !defined(AFX_STATUTETREENODE_H__CBA7BC2A_7556_4633_B045_518917CD57AB__INCLUDED_)
