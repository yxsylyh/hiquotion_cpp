// Pie.h: interface for the CPie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIE_H__7937B9A0_818D_4C62_BE4C_E4115CD32489__INCLUDED_)
#define AFX_PIE_H__7937B9A0_818D_4C62_BE4C_E4115CD32489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IShape.h"

class CPie : public IShape  
{
public:
	CPie();
	CPie(int left, int top, int right, int bottom, int startx, int starty, int endx, int endy);
	CPie(int left, int top, int right, int bottom, POINT start, POINT end);
	CPie(RECT rect, int startx, int starty, int endx, int endy);
	CPie(RECT rect, POINT start, POINT end);
	virtual ~CPie();

	// ·½·¨
	void setPoints(POINT start, POINT end);
	virtual void drawMe(CDC *pDC, CPoint point);

protected:
	POINT m_start, m_end;
};

#endif // !defined(AFX_PIE_H__7937B9A0_818D_4C62_BE4C_E4115CD32489__INCLUDED_)
