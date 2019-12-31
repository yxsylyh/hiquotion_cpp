// Node.cpp: implementation of the CNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatusGraphNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatusGraphNode::CStatusGraphNode()
: m_final(FALSE), m_type(""), m_subtype(""), m_errMsg("")
{

}

CStatusGraphNode::CStatusGraphNode(BOOL isFinal)
: m_final(isFinal), m_type(""), m_subtype(""), m_errMsg("")
{

}

CStatusGraphNode::CStatusGraphNode(std::string errMsg)
: m_final(FALSE), m_type(""), m_subtype(""), m_errMsg(errMsg)
{

}

CStatusGraphNode::CStatusGraphNode(BOOL isFinal, std::string type)
: m_final(isFinal), m_type(type), m_subtype(""), m_errMsg("")
{

}

CStatusGraphNode::CStatusGraphNode( BOOL isFinal, std::string type, std::string subtype )
: m_final(isFinal), m_type(type), m_subtype(subtype), m_errMsg("")
{
	
}

CStatusGraphNode::~CStatusGraphNode()
{

}
