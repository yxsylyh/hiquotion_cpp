// Arc.cpp: implementation of the CArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiGraphProj.h"
#include "Arc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArc::CArc()
: m_arcWeight(NULL)
{

}

CArc::CArc(IArcWeight *arcWeight)
: m_arcWeight(arcWeight)
{

}

CArc::CArc(CNode *nodeStart, CNode *nodeEnd)
: m_arcWeight(NULL), m_isWeightDestroy(FALSE), m_nodeStart(nodeStart), m_nodeToEnd(nodeEnd)
{
	
}

CArc::CArc(IArcWeight *arcWeight, CNode *nodeStart, CNode *nodeEnd)
: m_arcWeight(arcWeight), m_isWeightDestroy(FALSE), m_nodeStart(nodeStart), m_nodeToEnd(nodeEnd)
{

}

CArc::CArc(IArcWeight *arcWeight, BOOL isWeightDestroy, CNode *nodeStart, CNode *nodeEnd)
: m_arcWeight(arcWeight), m_isWeightDestroy(isWeightDestroy), m_nodeStart(nodeStart), m_nodeToEnd(nodeEnd)
{

}

CArc::~CArc()
{

}
