// Node.h: interface for the CNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__29248788_11AA_44CD_B1C1_76F88FF9725A__INCLUDED_)
#define AFX_NODE_H__29248788_11AA_44CD_B1C1_76F88FF9725A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\SelfContainer\SelfGraphNode.h>

class CStatusGraphArc;

class CStatusGraphNode : public CSelfGraphNode<CStatusGraphArc *, int>  
{
public:
	CStatusGraphNode();
	CStatusGraphNode(BOOL isFinal);
	CStatusGraphNode(std::string errMsg);
	CStatusGraphNode(BOOL isFinal, std::string type);
	CStatusGraphNode(BOOL isFinal, std::string type, std::string subtype);
	virtual ~CStatusGraphNode();

	BOOL isFinal() const { return m_final; }
	void setFinal(BOOL val) { m_final = val; }
	
	std::string getType() const { return m_type; }
	void setType(std::string val) { m_type = val; }
	
	std::string getSubtype() const { return m_subtype; }
	void setSubtype(std::string val) { m_subtype = val; }
	
	std::string getErrMsg() const { return m_errMsg; }
	void setErrMsg(std::string val) { m_errMsg = val; }

private:
	BOOL m_final;
	std::string m_type;
	std::string m_subtype;
	std::string m_errMsg;
};

#endif // !defined(AFX_NODE_H__29248788_11AA_44CD_B1C1_76F88FF9725A__INCLUDED_)
