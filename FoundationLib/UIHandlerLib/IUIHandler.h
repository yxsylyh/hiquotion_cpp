// IUIHandler.h: interface for the IUIHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IUIHANDLER_H__4DE9534E_53D4_4646_809B_169308CA8D62__INCLUDED_)
#define AFX_IUIHANDLER_H__4DE9534E_53D4_4646_809B_169308CA8D62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\TreeProj\TreeNode.h>
#include "IInteractiveEventHandler.h"
// #include <C++\FoundationLib\DrawingLib\ILocation.h>
// #include "EventHandlingContainer.h"
// #include <C++\FoundationLib\DrawingLib\Container.h>
#include <C++\FoundationLib\DrawingLib\IShape.h>

enum EventHandleOrder
{
	EventDisabled,
	SelfOnlyHandled,
	ChildOnlyHandled,
	SelfThenChild,
	ChildThenSelf
};

class IUIHandler : public CTreeNode<IUIHandler *>, public IInteractiveEventHandler/*, public ILocation*/
{
public:
	IUIHandler();
	IUIHandler(IShape *shape);
	virtual ~IUIHandler();

// 	void draw(CDC *pDC);

	// 添加子结点
	void addUIHandler(IUIHandler *handler);
// 	void addFigure(IShape *figure, BOOL fullfill=FALSE);

	// 取子结点
	CTreeNode<IUIHandler *> *getUIHandlerTreeNode(int index);
	CTreeNode<IUIHandler *> *getUIHandlerTreeNode(IUIHandler *handler);

	// 取结点节点中的 IUIHandler 对象
	IUIHandler *getUIHandler(int index);
	
	// 判断是否包含指定 IUIHandler 对象（isCheckChilren 表示是否检查子结点中的 IUIHandler 对象）
	BOOL isContainUIHandler(IUIHandler *handler, BOOL isCheckChilren=TRUE);

	// 移除 IUIHandler 对象（同时删除子结点）
	void removeUIHandler(IUIHandler *handler);
// 	void removeFigure(IShape *figure);

	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0), CRgn *parentRgn=NULL);

	// 坐标变换
	// 点
	CPoint pointToClient(IUIHandler *child, CPoint ptInParent);
	CPoint pointToParent(CPoint ptInClient);
	// 矩形
	CRect rectToClient(IUIHandler *child, CRect rtInParent);
	CRect rectToParent(CRect rtInClient);
	
	CWnd * getWndForRefresh() const { return m_wndForRefresh; }
	void setWndForRefresh(CWnd * val) { m_wndForRefresh = val; }

	void updateUI();

	IUIHandler * getHandlerSelected() const { return m_handlerSelected; }
	CPoint getLastDraggedPoint() const { return m_lastDraggedPoint; }

	IShape * getShape() const { return m_shape; }
	void setShape(IShape * val) { m_shape = val; if(!val) m_rect=val->getRect(); }

	CRect getRect() const { return m_rect; }

	// 外部点击事件
	void leftButtonDown(UINT nFlags, CPoint point);
	void leftButtonUp(UINT nFlags, CPoint point);
	void leftButtonDoubleClick(UINT nFlags, CPoint point);
	
	void rightButtonDown(UINT nFlags, CPoint point);
	void rightButtonUp(UINT nFlags, CPoint point);
	void rightButtonDblClick(UINT nFlags, CPoint point);
	
	void mouseMove(UINT nFlags, CPoint point);
	void mouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void keyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void keyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	EventHandleOrder getMovingEffected() const { return m_eventEffected; }
	void setMovingEffected(EventHandleOrder val) { m_eventEffected = val; }

protected:
	IUIHandler *isPointInChild(CPoint point);

	// 鼠标键盘直接的事件
	
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	// 	virtual void OnLButtonClick();
	virtual void OnLButtonDblClick(UINT nFlags, CPoint point);
	virtual void OnLButton3Click();
	
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonDblClick(UINT nFlags, CPoint point);
	
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnMouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint);
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// 鼠标和键盘的事件组合效果
	
	// 	virtual void OnMouseHove(UINT nFlags, CPoint point);   // OnMouseMove + 悬停多少毫秒，触发该事件
	// 	void OnMouseMoveIn(CDrawnObj *drawnObj); // OnMouseMove
	// 	void OnMouseMoveOut(CDrawnObj *drawnObj);// OnMouseMove，如果鼠标位置不在绘图对象的内部区域时，触发

protected:
	BOOL m_isMouseIn;
	CPoint m_pointAtMouseDown;
	BOOL m_altPressed;
	EventHandleOrder m_eventEffected;
	CPoint m_lastDraggedPoint;

	CRect m_rect;
	IShape *m_shape;

	CWnd *m_wndForRefresh;

	IUIHandler *m_handlerSelected;
};

#endif // !defined(AFX_IUIHANDLER_H__4DE9534E_53D4_4646_809B_169308CA8D62__INCLUDED_)
