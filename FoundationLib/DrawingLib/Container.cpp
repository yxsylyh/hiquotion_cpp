// Container.cpp: implementation of the CContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Container.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContainer::CContainer()
: IShape(), m_childRgn(NULL)
{
// 	m_children.clear();
}

CContainer::CContainer(int left, int top, int right, int bottom)
: IShape(left, top, right, bottom), m_childRgn(NULL)
{
	
}

CContainer::CContainer(CRect rect)
: IShape(rect), m_childRgn(NULL)
{
	
}

CContainer::~CContainer()
{

}

BOOL CContainer::addFigure(IShape *figure, BOOL fullfill)
{
	if(!figure)
		return FALSE;

 	m_subShapeList.push_back(figure);
	figure->setFullfill(fullfill);
	
	return TRUE;
}

// CTreeNode<IShape *> *CContainer::removeFigure(IShape *figure)
IShape *CContainer::removeFigure(IShape *figure)
{
	if(!figure)
		return NULL;
	
	return m_subShapeList.remove(figure);
// 	return CTreeNode<IShape *>::removeT(figure);
}

void CContainer::drawChildren(CDC *pDC, CPoint point, CRgn *parentRgn)
{
	if(!pDC)
		return;
	
	if(!pDC->GetSafeHdc())
		return;
	
	for(int i=0;i<(int)m_subShapeList.size();i++)
	{
		IShape *shape=m_subShapeList.at(i);
		if(!shape)
			continue;

		CPoint p=m_rect.TopLeft();
		p.Offset(point);
		shape->draw(pDC, p, parentRgn);
	}
}

void CContainer::draw(CDC *pDC, CPoint point, CRgn *parentRgn)
{
	if(!pDC)
		return;
	
	if(!pDC->GetSafeHdc())
		return;

	IShape::draw(pDC, point, parentRgn);

	preparePenAndBrush(pDC);
	
	drawMe(pDC, point);
	
	restorePenAndBrush(pDC);
	
	prepareRgn(pDC, point, parentRgn);
	
	drawChildren(pDC, point, &m_rgn);
	
	restoreRgn(pDC);
}
