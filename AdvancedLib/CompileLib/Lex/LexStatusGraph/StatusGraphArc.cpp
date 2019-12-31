// Arc.cpp: implementation of the CArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatusGraphArc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatusGraphArc::CStatusGraphArc()
{

}

CStatusGraphArc::CStatusGraphArc( CStatusGraphNode *from, CStatusGraphNode *to, IRegularExpression *re )
: CSelfGraphArc<CStatusGraphNode *, IRegularExpression *>(from, to, re)
{
	from->addOutArc(this);
	to->addInArc(this);
}

CStatusGraphArc::~CStatusGraphArc()
{

}
