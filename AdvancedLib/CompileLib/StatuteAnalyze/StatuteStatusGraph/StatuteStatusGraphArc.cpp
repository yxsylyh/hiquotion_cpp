// MergenceStatusGraphArc.cpp: implementation of the CMergenceStatusGraphArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteStatusGraphArc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteStatusGraphArc::CStatuteStatusGraphArc()
{

}

CStatuteStatusGraphArc::CStatuteStatusGraphArc( CStatuteStatusGraphNode *from, CStatuteStatusGraphNode *to, MachineToken *data/*, BOOL isGotoAnotherStatute*/ )
: CSelfGraphArc<CStatuteStatusGraphNode *, MachineToken *>(from, to, data)/*, m_isGotoAnotherStatute(isGotoAnotherStatute)*/
{
	from->addOutArc(this);
	to->addInArc(this);
}

CStatuteStatusGraphArc::~CStatuteStatusGraphArc()
{
	m_from->removeOutArc(this);
	m_to->removeInArc(this);
}
