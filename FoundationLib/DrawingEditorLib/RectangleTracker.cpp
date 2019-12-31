// RectangleTracker.cpp: implementation of the CRectangleTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "RectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangleTracker::CRectangleTracker(CRect rect) : CTracker(rect)
{
// 	m_rect=rect;

	// ×óÉÏ¾ä±ú
	CPoint point=rect.TopLeft();
	CHandle handle(point.x-Default_Handle_Sizex,point.y-Default_Handle_Sizey);
	m_handles.push_back(handle);

	// ÖÐÉÏ¾ä±ú
	handle.setHandlePosition(rect.CenterPoint().x-Default_Handle_Sizex/2,point.y-Default_Handle_Sizey);
	m_handles.push_back(handle);

	// ÓÒÉÏ¾ä±ú
	handle.setHandlePosition(point.x+rect.Width(),point.y-Default_Handle_Sizey);
	m_handles.push_back(handle);

	// ×ó¾ä±ú
	handle.setHandlePosition(point.x-Default_Handle_Sizex,rect.CenterPoint().y-Default_Handle_Sizey/2);
	m_handles.push_back(handle);

	// ÓÒ¾ä±ú
	handle.setHandlePosition(point.x+rect.Width(),rect.CenterPoint().y-Default_Handle_Sizey/2);
	m_handles.push_back(handle);

	// ×óÏÂ¾ä±ú
	handle.setHandlePosition(point.x-Default_Handle_Sizex,point.y+rect.Height());
	m_handles.push_back(handle);

	// ÖÐÏÂ¾ä±ú
	handle.setHandlePosition(rect.CenterPoint().x-Default_Handle_Sizex/2,point.y+rect.Height());
	m_handles.push_back(handle);

	// ÓÒÏÂ¾ä±ú
	point=rect.BottomRight();
	handle.setHandlePosition(point.x,point.y);
	m_handles.push_back(handle);
}

CRectangleTracker::~CRectangleTracker()
{

}
