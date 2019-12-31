// StatusMachine.h: interface for the CStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSMACHINE_H__BEB72CE6_E022_4C9C_987C_D3863DC27EE0__INCLUDED_)
#define AFX_STATUSMACHINE_H__BEB72CE6_E022_4C9C_987C_D3863DC27EE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../LexStatusGraph/LexStatusGraph.h"
#include <string>
// #include "StatusGraphLoader.h"
#include "../LexStatusGraph/StatusGraphNode.h"

// 状态机
// 一个一个字符输入，从而判断状态机的状态
// 根据状态机的状态，获取其中的字符和字符类型，或者获得一个错误消息
// 注：该状态机一次只能获取一类字符，比如源码“int a=10;”，第一次状态机获得int，第二次获得a，以此类推
class CLexStatusMachine  
{
public:
	CLexStatusMachine();
	CLexStatusMachine(CLexStatusGraph *graphic);
	virtual ~CLexStatusMachine();

	// 恢复初始状态，即指向开始状态
	void init();

	// 是否接受给定的字符
	// 1，接受
	// 0，不接受
	// -1，当前结点指针为空
	int accept(char ch);

	// 当不接受某字符时，判断是否在结束状态
	// 1，是
	// 0，不是
	// -1，当前结点指针为空
	int isFinalStatus();

	// 获取状态机中的字符串
	std::string getString(){return m_string;};

	// 获取状态机中字符串的类型（该类型来自当前终态结点）
	std::string getStringType();

	// 获取状态机中字符串的子类型（该类型来自当前终态结点）
	std::string getStringSubType();

	// 获取状态机错误信息（该信息来自非终态结点）
	std::string getErrMsg();

	CLexStatusGraph *getGraphic() const { return m_graphic; }
	void setGraphic(CLexStatusGraph *val) { m_graphic = val; }

	int getInitStatus() const { return m_initStatus; }

private:
	CLexStatusGraph *m_graphic;
// 	CStatusGraphLoader m_statusGraphLoader;
	CStatusGraphNode *m_currentNode;

	std::string m_string;

	// 初始化状态变量，用于判断是否是刚刚初始化，即调用 init 之后为1，accept接受了字符串之后为0
	// 该类未调用init方法之前，为-1
	int m_initStatus;
};

#endif // !defined(AFX_STATUSMACHINE_H__BEB72CE6_E022_4C9C_987C_D3863DC27EE0__INCLUDED_)
