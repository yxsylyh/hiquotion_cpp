// StatusGraph.cpp: implementation of the CStatusGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LexStatusGraph.h"
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\IRegularExpression.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLexStatusGraph::CLexStatusGraph()
{

}

CLexStatusGraph::~CLexStatusGraph()
{

}

void CLexStatusGraph::genRelationship( CStatusGraphArc *arc, CStatusGraphNode *from/*=NULL*/, CStatusGraphNode *to/*=NULL*/ )
{
	if(!from)
	{
		from=arc->getNodeFrom();
		if(!from)
			return;

		from->addOutArc(arc);
	}
	else
	{
		arc->setNodeFrom(from);
		from->addOutArc(arc);
	}

	if(!to)
	{
		to=arc->getNodeTo();
		if(!to)
			return;

		to->addInArc(arc);
	}
	else
	{
		arc->setNodeTo(to);
		to->addInArc(arc);
	}
}
