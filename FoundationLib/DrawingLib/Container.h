// Container.h: interface for the CContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTAINER_H__CD49B79F_053D_4363_8933_A6BD4DA4C781__INCLUDED_)
#define AFX_CONTAINER_H__CD49B79F_053D_4363_8933_A6BD4DA4C781__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IShape.h"
#include <C++/FoudationLib/DataStructLib/TreeProj/TreeNode.h>
// #include "IDrawing.h"

class CContainer : public IShape//, public CTreeNode<IShape *> 
{
public:
	CContainer();
	CContainer(int left, int top, int right, int bottom);
	CContainer(CRect rect);
	virtual ~CContainer();

	BOOL addFigure(IShape *figure, BOOL fullfill=FALSE);
	IShape *removeFigure(IShape *figure);
	void drawChildren(CDC *pDC, CPoint point=CPoint(0, 0), CRgn *parentRgn=NULL);
	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0), CRgn *parentRgn=NULL);

protected:
	CPointerList<IShape *> m_subShapeList;
	CRgn *m_childRgn;
};

#endif // !defined(AFX_CONTAINER_H__CD49B79F_053D_4363_8933_A6BD4DA4C781__INCLUDED_)
