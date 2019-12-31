#include "pch.h"
#include "AutoResize.h"

CAutoResize::CAutoResize()
	: m_wnd(NULL),
	m_leftDistance(0), m_topDistance(0), m_rightDistance(0), m_bottomDistance(0),
	m_width(0), m_height(0)
{
	m_leftResizeType = Anchor;
	m_topResizeType = Anchor;
	m_rightResizeType = Original;
	m_bottomResizeType = Original;
}

CAutoResize::CAutoResize(ResizeType leftResizeType, ResizeType topResizeType, ResizeType rightResizeType, ResizeType bottomResizeType)
	: m_wnd(NULL), 
	m_leftDistance(0), m_topDistance(0), m_rightDistance(0), m_bottomDistance(0),
	m_width(0), m_height(0)
{
	m_leftResizeType = leftResizeType;
	m_topResizeType = topResizeType;
	m_rightResizeType = rightResizeType;
	m_bottomResizeType = bottomResizeType;
}

void CAutoResize::init(CWnd* wnd, CWnd* parent, BOOL considerTitleHeight)
{
	if (!checkWnd(wnd))
		return;

	m_wnd = wnd;

	if (!checkWnd(parent))
		return;

	WINDOWPLACEMENT wp;
	wnd->GetWindowPlacement(&wp);

	CRect rcParent;
	if (considerTitleHeight)
		parent->GetClientRect(&rcParent);
	else
		parent->GetWindowRect(&rcParent);

	init(&wp.rcNormalPosition, &rcParent);
}

void CAutoResize::init(RECT* rc, RECT* rcParent)
{
	init(rc->left, rc->top, rcParent->right - rc->right, rcParent->bottom - rc->bottom, rc->right - rc->left, rc->bottom - rc->top);
}

void CAutoResize::init(int leftDistance, int topDistance, int rightDistance, int bottomDistance, int width, int height)
{
	m_leftDistance = leftDistance;
	m_topDistance = topDistance;
	m_rightDistance = rightDistance;
	m_bottomDistance = bottomDistance;

	m_width = width;
	m_height = height;
}

void CAutoResize::initFill(CWnd* wnd, CWnd* parent, BOOL considerTitleHeight)
{
	if (!checkWnd(wnd))
		return;

	if (!checkWnd(parent))
		return;

	m_wnd = wnd;

	CRect rcParent;
	if (considerTitleHeight)
		parent->GetClientRect(&rcParent);
	else
		parent->GetWindowRect(&rcParent);

	init(&rcParent, &rcParent);
}


void CAutoResize::autoResize(int cx, int cy)
{
	if (!checkWnd(m_wnd))
		return;

	int left = 0, top = 0, right = 0, bottom = 0;

	// handle left and right
	if (m_leftResizeType == Anchor)
	{
		left = m_leftDistance;

		if (m_rightResizeType == Anchor)
			right = cx - m_rightDistance;
		else if (m_rightResizeType == Original)
			right = left + m_width;
	}
	else if (m_leftResizeType == Original)
	{
		if (m_rightResizeType == Anchor)
		{
			left = cx - m_rightDistance - m_width;
			right = cx - m_rightDistance;
		}
		else if (m_rightResizeType == Original)
		{
			m_leftResizeType = Anchor;

			left = m_leftDistance;
			right = left + m_width;
		}
	}

	// handle top and bottom
	if (m_topResizeType == Anchor)
	{
		top = m_topDistance;

		if (m_bottomResizeType == Anchor)
			bottom = cy - m_bottomDistance;
		else if (m_bottomResizeType == Original)
			bottom = top + m_height;
	}
	else if (m_topResizeType == Original)
	{
		if (m_bottomResizeType == Anchor)
		{
			top = cy - m_bottomDistance - m_height;
			bottom = cy - m_bottomDistance;
		}
		else if (m_bottomResizeType == Original)
		{
			m_topResizeType = Anchor;

			top = m_topDistance;
			bottom = top + m_height;
		}
	}

	// do resize
	m_wnd->MoveWindow(left, top, right - left, bottom - top);
	m_wnd->Invalidate();

	// update all member vars
	m_leftDistance = left;
	m_topDistance = top;
	m_rightDistance = cx - right;
	m_bottomDistance = cy - bottom;

	m_width = right - left;
	m_height = bottom - top;
}

BOOL CAutoResize::checkWnd(CWnd* wnd)
{
	if (!wnd)
		return FALSE;

	if (!wnd->GetSafeHwnd())
		return FALSE;

	if (!IsWindow(wnd->GetSafeHwnd()))
		return FALSE;

	return TRUE;
}
