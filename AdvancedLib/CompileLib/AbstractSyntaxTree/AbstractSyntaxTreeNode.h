// AbstractSyntaxTreeNode.h: interface for the CAbstractSyntaxTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTSYNTAXTREENODE_H__18680A67_EEE8_4930_93CE_F0894BF49F99__INCLUDED_)
#define AFX_ABSTRACTSYNTAXTREENODE_H__18680A67_EEE8_4930_93CE_F0894BF49F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\SelfContainer\SelfTreeNode.h>
#include <C++\AdvancedLib\CompileLib\Lex\Lexer\Lexer.h>

// 抽象语法树节点
class CAbstractSyntaxTreeNode : public CSelfTreeNode<CAbstractSyntaxTreeNode *>  
{
public:
	CAbstractSyntaxTreeNode();
	CAbstractSyntaxTreeNode(MachineToken *machineToken);
	virtual ~CAbstractSyntaxTreeNode();

	std::string getNodeType() const { return m_nodeType; }
	void setNodeType(std::string val) { m_nodeType = val; }

	std::string getNodeValue() const { return m_nodeValue; }
	void setNodeValue(std::string val) { m_nodeValue = val; }

	MachineToken * getMachineToken() const { return m_machineToken; }
	void setMachineToken(MachineToken * val) { m_machineToken = val; }

	// 获取树节点信息（包括子节点），用于测试
	std::string getTreeNodeInfo();
	// 获取指定级别的树节点信息，level表示当前节点是在树的第几层，用于测试
	std::string getTreeNodeInfoByLevel(CAbstractSyntaxTreeNode *node, unsigned int level, int space=4);

protected:
	// 节点类型
	std::string m_nodeType;
	// 节点值
	std::string m_nodeValue;
	MachineToken *m_machineToken;
};

#endif // !defined(AFX_ABSTRACTSYNTAXTREENODE_H__18680A67_EEE8_4930_93CE_F0894BF49F99__INCLUDED_)
