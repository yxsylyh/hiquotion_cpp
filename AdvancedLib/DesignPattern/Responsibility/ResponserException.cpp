// ResponserException.cpp: implementation of the CResponserException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Responsibility.h"
#include "ResponserException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResponserException::CResponserException(CString errMessage)
: m_errMessage(errMessage)
{

}

CResponserException::~CResponserException()
{

}
