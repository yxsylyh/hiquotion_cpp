// LogBuilderBase.cpp: implementation of the CLogBuilderBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogLib.h"
#include "LogBuilderBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogBuilderBase::CLogBuilderBase()
: m_ignoreLogLevelinConfig(FALSE)
{

}

CLogBuilderBase::~CLogBuilderBase()
{

}

void CLogBuilderBase::ignoreLogLevelinConfig()
{
	m_ignoreLogLevelinConfig=TRUE;
}
