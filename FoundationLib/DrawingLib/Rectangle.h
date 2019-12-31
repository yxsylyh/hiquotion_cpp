// Rectangle1.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE1_H__E1CE7653_DD06_40DD_8837_9AC8C67A67A6__INCLUDED_)
#define AFX_RECTANGLE1_H__E1CE7653_DD06_40DD_8837_9AC8C67A67A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Container.h"

class CRectangle : public CContainer
{
public:
	CRectangle();
	CRectangle(int left, int top, int right, int bottom);
	CRectangle(CRect rect);
	virtual ~CRectangle();
};

#endif // !defined(AFX_RECTANGLE1_H__E1CE7653_DD06_40DD_8837_9AC8C67A67A6__INCLUDED_)
