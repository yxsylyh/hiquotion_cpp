// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_)
#define AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ILine.h"

class CLine : public ILine
{
public:
	CLine();
	CLine(CRect rect, COLORREF color=RGB(0,0,0), int lineStyle=PS_SOLID, int lineWitdh=0, int srcCap=PS_ENDCAP_SQUARE, int dstCap=PS_ENDCAP_SQUARE);
	CLine(CPoint src, CPoint dst, COLORREF color=RGB(0,0,0), int lineStyle=PS_SOLID, int lineWitdh=0, int srcCap=PS_ENDCAP_SQUARE, int dstCap=PS_ENDCAP_SQUARE);
	CLine(int srcx, int srcy, int dstx, int dsty, COLORREF color=RGB(0,0,0), int lineStyle=PS_SOLID, int lineWitdh=0, int srcCap=PS_ENDCAP_SQUARE, int dstCap=PS_ENDCAP_SQUARE);
	virtual ~CLine();
};

#endif // !defined(AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_)
