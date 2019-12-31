// IInteractiveEventHandler.h: interface for the IInteractiveEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IINTERACTIVEEVENTHANDLER_H__0DD1496E_843A_413E_8ED3_BA72D5F09E1D__INCLUDED_)
#define AFX_IINTERACTIVEEVENTHANDLER_H__0DD1496E_843A_413E_8ED3_BA72D5F09E1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IInteractiveEventHandler  
{
public:
	IInteractiveEventHandler();
	virtual ~IInteractiveEventHandler();

// 	nFlags 的含义（遗憾的是没有 MK_ALT 的定义）
/*
 * Key State Masks for Mouse Messages
 */
// #define MK_LBUTTON          0x0001
// #define MK_RBUTTON          0x0002
// #define MK_SHIFT            0x0004
// #define MK_CONTROL          0x0008
// #define MK_MBUTTON          0x0010
// #define MK_ALT 0x0020   // 在别的vc6头文件里有

	void leftButtonDown(UINT nFlags, CPoint point) { OnLButtonDown(nFlags, point); }
	void leftButtonUp(UINT nFlags, CPoint point) { OnLButtonUp(nFlags, point); }
	void leftButtonDoubleClick(UINT nFlags, CPoint point) { OnLButtonDblClick(nFlags, point); }
	
	void rightButtonDown(UINT nFlags, CPoint point) { OnRButtonDown(nFlags, point); }
	void rightButtonUp(UINT nFlags, CPoint point) { OnRButtonUp(nFlags, point); }
	void rightButtonDblClick(UINT nFlags, CPoint point) { OnRButtonDblClick(nFlags, point); }
	
	void mouseMove(UINT nFlags, CPoint point) { OnMouseMove(nFlags, point); }
	void mouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint){ OnMouseDrag(nFlags, currPoint, origPoint); }
	void mouseWheel(UINT nFlags, short zDelta, CPoint pt) { OnMouseWheel(nFlags, zDelta, pt); }
	void keyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { OnKeyDown(nChar, nRepCnt, nFlags); }
	void keyUp(UINT nChar, UINT nRepCnt, UINT nFlags) { OnKeyUp(nChar, nRepCnt, nFlags); }

protected:
	// 鼠标键盘直接的事件
	
	virtual void OnLButtonDown(UINT nFlags, CPoint point){};
	virtual void OnLButtonUp(UINT nFlags, CPoint point){};
// 	virtual void OnLButtonClick(){};
	virtual void OnLButtonDblClick(UINT nFlags, CPoint point){};
	virtual void OnLButton3Click(){};
	
	virtual void OnRButtonDown(UINT nFlags, CPoint point){};
	virtual void OnRButtonUp(UINT nFlags, CPoint point){};
	virtual void OnRButtonDblClick(UINT nFlags, CPoint point){};
	
	virtual void OnMouseMove(UINT nFlags, CPoint point){};
	virtual void OnMouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint){};
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){};
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){};
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){};
	
	// 鼠标和键盘的事件组合效果
	
// 	virtual void OnMouseHove(UINT nFlags, CPoint point){};   // OnMouseMove + 悬停多少毫秒，触发该事件
// 	void OnMouseMoveIn(CDrawnObj *drawnObj){}; // OnMouseMove
// 	void OnMouseMoveOut(CDrawnObj *drawnObj){};// OnMouseMove，如果鼠标位置不在绘图对象的内部区域时，触发
	
// protected:
// 	CPoint m_pointAtMouseDown;
// 	BOOL m_altPressed;
};

#endif // !defined(AFX_IINTERACTIVEEVENTHANDLER_H__0DD1496E_843A_413E_8ED3_BA72D5F09E1D__INCLUDED_)
