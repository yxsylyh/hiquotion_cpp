// Rectangle1.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle()
: CContainer()
{

}

CRectangle::CRectangle(int left, int top, int right, int bottom)
: CContainer(left, top, right, bottom)
{

}

CRectangle::CRectangle(CRect rect)
: CContainer(rect)
{

}

CRectangle::~CRectangle()
{

}
