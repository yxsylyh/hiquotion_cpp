// IUIHandler.cpp: implementation of the IUIHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UIHandlerLib.h"
#include "IUIHandler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IUIHandler::IUIHandler()
: m_shape(NULL), m_wndForRefresh(NULL), m_handlerSelected(NULL), m_rect(0, 0, 10, 10),
  m_isMouseIn(FALSE), m_pointAtMouseDown(0, 0), m_altPressed(FALSE), m_eventEffected(SelfThenChild)
{

}

IUIHandler::IUIHandler( IShape *shape )
: m_shape(shape), m_wndForRefresh(NULL), m_handlerSelected(NULL)
{
	if(!m_shape)
		m_rect=m_shape->getRect();
}

IUIHandler::~IUIHandler()
{

}

// void IUIHandler::draw(CDC *pDC)
// {
// 	CContainer::draw(pDC);
// }

void IUIHandler::addUIHandler(IUIHandler *handler)
{
	CTreeNode<IUIHandler *>::addT(handler);
// 	CContainer::addFigure(handler);
}

// void IUIHandler::addFigure(IShape *figure, BOOL fullfill)
// {
// 	CContainer::addFigure(figure, fullfill);
// }

CTreeNode<IUIHandler *> *IUIHandler::getUIHandlerTreeNode(int index)
{
	return CTreeNode<IUIHandler *>::get(index);
}

CTreeNode<IUIHandler *> *IUIHandler::getUIHandlerTreeNode(IUIHandler *handler)
{
	return CTreeNode<IUIHandler *>::getByT(handler);
}

IUIHandler *IUIHandler::getUIHandler(int index)
{
	return CTreeNode<IUIHandler *>::getT(index);
}

BOOL IUIHandler::isContainUIHandler(IUIHandler *handler, BOOL isCheckChildren)
{
	CTreeNode<IUIHandler *> *node=CTreeNode<IUIHandler *>::getByT(handler);
	if(node)
		return TRUE;

	if(!isCheckChildren)
		return FALSE;

	for(int i=0;i<CTreeNode<IUIHandler *>::count();i++)
	{
		IUIHandler *child=getUIHandler(i);
		if(!child)
			continue;

		BOOL isContained=child->isContainUIHandler(handler);
		if(isContained)
			return TRUE;
	}

	return FALSE;
}

void IUIHandler::removeUIHandler(IUIHandler *handler)
{
	CTreeNode<IUIHandler *> *node=CTreeNode<IUIHandler *>::removeT(handler);
	if(node)
	{
		delete node;
// 		CTreeNode<IShape *> *shapeNode=CContainer::removeFigure(handler);
// 		if(shapeNode)
// 			delete shapeNode;
	}
}

// void IUIHandler::removeFigure(IShape *figure)
// {
// 	CTreeNode<IShape *> *shapeNode=CContainer::removeFigure(figure);
// 	if(shapeNode)
// 		delete shapeNode;
// }

void IUIHandler::draw( CDC *pDC, CPoint point/*=CPoint(0, 0)*/, CRgn *parentRgn/*=NULL*/ )
{
	if(!pDC)
		return;
	
	if(!pDC->GetSafeHdc())
		return;
	
	IShape *shape=getShape();
	if(!shape)
		return;

	shape->draw(pDC, point, parentRgn);

	for(int i=0;i<CTreeNode<IUIHandler *>::count();i++)
	{
		IUIHandler *handler=getUIHandler(i);
		if(!handler)
			continue;

		handler->draw(pDC, point, parentRgn);
	}
}

// 坐标变换
// 点
CPoint IUIHandler::pointToClient(IUIHandler *child, CPoint ptInParent)
{
	if(!child)
		return CPoint(0, 0);

	if(!child->getShape())
		return CPoint(0, 0);

	CPoint relativeOrig=child->getShape()->getRect().TopLeft();
	CPoint relativePoint=ptInParent;
	relativePoint.Offset(-relativeOrig.x, -relativeOrig.y);
	return relativePoint;
}

CPoint IUIHandler::pointToParent(CPoint ptInClient)
{
	if(!m_shape)
		return CPoint(0, 0);

	CPoint relativeOrig=m_shape->getRect().TopLeft();
	CPoint relativePoint=ptInClient;
	relativePoint.Offset(relativeOrig);
	return relativePoint;
}

// 矩形
CRect IUIHandler::rectToClient(IUIHandler *child, CRect rtInParent)
{
	if(!child)
		return CRect(0, 0, 10, 10);
	
	if(!child->getShape())
		return CRect(0, 0, 10, 10);
	
	CPoint relativeOrig=child->getShape()->getRect().TopLeft();
	CRect relativeRect=rtInParent;
	relativeRect.OffsetRect(-relativeOrig.x, -relativeOrig.y);
	return relativeRect;
}

CRect IUIHandler::rectToParent(CRect rtInClient)
{
	if(!m_shape)
		return CRect(0, 0, 10, 10);

	CPoint relativeOrig=m_shape->getRect().TopLeft();
	CRect relativeRect=rtInClient;
	relativeRect.OffsetRect(relativeOrig);
	return relativeRect;
}

void IUIHandler::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_eventEffected==EventDisabled)
		return;

	IInteractiveEventHandler::OnLButtonDown(nFlags, point);

	m_lastDraggedPoint=point;

	if(m_eventEffected==ChildOnlyHandled || m_eventEffected==SelfThenChild)
	{
		m_handlerSelected=isPointInChild(point);
		if(m_handlerSelected)
		{
			CPoint relativePoint=pointToClient(m_handlerSelected, point);
			m_handlerSelected->leftButtonDown(nFlags, relativePoint);
			return;
		}
	}

	updateUI();
}

void IUIHandler::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_eventEffected==EventDisabled)
		return;
	
	IInteractiveEventHandler::OnLButtonUp(nFlags, point);
	
	if(m_eventEffected==ChildOnlyHandled || m_eventEffected==SelfThenChild)
	{
		if(m_handlerSelected)
		{
			CPoint relativePoint=pointToClient(m_handlerSelected, point);
			m_handlerSelected->OnLButtonUp(nFlags, relativePoint);
		}
		m_handlerSelected=NULL;
	}

	updateUI();
}

void IUIHandler::OnMouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint)
{
	if(nFlags & MK_LBUTTON<=0)
		return;

	if(m_eventEffected==EventDisabled)
		return;
	
	if(m_eventEffected==ChildOnlyHandled || m_eventEffected==SelfThenChild)
	{
		if(m_handlerSelected)
		{
			CPoint ralativeCurrPoint=pointToClient(m_handlerSelected, currPoint);
			CPoint relativeOrigPoint=pointToClient(m_handlerSelected, origPoint);
			m_handlerSelected->OnMouseDrag(nFlags, ralativeCurrPoint, relativeOrigPoint);
			updateUI();
			return;
		}
	}
	else if(m_eventEffected==SelfOnlyHandled || m_eventEffected==SelfThenChild)
	{
		m_rect.OffsetRect(currPoint.x-origPoint.x, currPoint.y-origPoint.y);
		updateUI();
	}
}

IUIHandler *IUIHandler::isPointInChild(CPoint point)
{
	CPoint shiftedPoint=point;
	shiftedPoint.x-=m_rect.left;
	shiftedPoint.y-=m_rect.top;
	for(int i=CTreeNode<IUIHandler *>::count()-1;i>=0;i--)
	{
		IUIHandler *handler=CTreeNode<IUIHandler *>::getT(i);
		if(handler)
		{
			CRect rect=handler->getRect();
			if(rect.PtInRect(shiftedPoint))
				return handler;
			
			IUIHandler *handlerChild=handler->isPointInChild(shiftedPoint);
			if(handlerChild)
				return handlerChild;
		}
	}

	return NULL;
}

void IUIHandler::updateUI()
{
	if(m_wndForRefresh)
		if(m_wndForRefresh->GetSafeHwnd())
			m_wndForRefresh->Invalidate(TRUE);
}

void IUIHandler::leftButtonDown(UINT nFlags, CPoint point)
{
	if(!m_rect.PtInRect(point))
		return;

	m_isMouseIn=TRUE;
	m_pointAtMouseDown=point;
	
	OnLButtonDown(nFlags, point);
}

void IUIHandler::leftButtonUp(UINT nFlags, CPoint point)
{
	m_isMouseIn=FALSE;
	OnLButtonUp(nFlags, point);
	m_pointAtMouseDown=CPoint(0, 0);
	m_lastDraggedPoint=CPoint(0, 0);
}

void IUIHandler::leftButtonDoubleClick(UINT nFlags, CPoint point)
{
	OnLButtonDblClick(nFlags, point);
}

void IUIHandler::rightButtonDown(UINT nFlags, CPoint point)
{
	OnRButtonDown(nFlags, point);
}

void IUIHandler::rightButtonUp(UINT nFlags, CPoint point)
{
	OnRButtonUp(nFlags, point);
}

void IUIHandler::rightButtonDblClick(UINT nFlags, CPoint point)
{
	OnRButtonDblClick(nFlags, point);
}

void IUIHandler::mouseMove(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
	
	if(!m_isMouseIn)
		return;

	if(nFlags & MK_LBUTTON)
	{
		if(m_lastDraggedPoint==CPoint(0, 0))
			m_lastDraggedPoint=m_pointAtMouseDown;
		OnMouseDrag(nFlags, point, m_lastDraggedPoint);
		m_lastDraggedPoint=point;
	}
}

void IUIHandler::mouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	OnMouseWheel(nFlags, zDelta, pt);
}

void IUIHandler::keyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	OnKeyDown(nChar, nRepCnt, nFlags);
}

void IUIHandler::keyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	OnKeyUp(nChar, nRepCnt, nFlags);
}

// 鼠标键盘直接的事件

// void CInteractiveEventHandler::OnLButtonClick()
// {
// 
// }

void IUIHandler::OnLButtonDblClick(UINT nFlags, CPoint point)
{

}

void IUIHandler::OnLButton3Click()
{

}

void IUIHandler::OnRButtonDown(UINT nFlags, CPoint point)
{

}

void IUIHandler::OnRButtonUp(UINT nFlags, CPoint point)
{

}

void IUIHandler::OnRButtonDblClick(UINT nFlags, CPoint point)
{

}

void IUIHandler::OnMouseMove(UINT nFlags, CPoint point)
{

}

void IUIHandler::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

}

void IUIHandler::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void IUIHandler::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

// 鼠标和键盘的事件组合效果

// void IUIHandler::OnMouseHove(UINT nFlags, CPoint point)   // OnMouseMove + 悬停多少毫秒，触发该事件
// {
// 
// }
