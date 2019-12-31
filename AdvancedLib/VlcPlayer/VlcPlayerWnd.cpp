// CVlcPlayerWnd.cpp: 实现文件
//

#include "stdafx.h"
#include "VlcPlayerWnd.h"


// CVlcPlayerWnd

IMPLEMENT_DYNAMIC(CVlcPlayerWnd, CStatic)

CVlcPlayerWnd::CVlcPlayerWnd()
{
}

CVlcPlayerWnd::~CVlcPlayerWnd()
{
}


BEGIN_MESSAGE_MAP(CVlcPlayerWnd, CStatic)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CVlcPlayerWnd 消息处理程序


void CVlcPlayerWnd::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(this->GetSafeHwnd())
		MoveWindow(0, 0, cx, cy);
}


void CVlcPlayerWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CStatic::OnPaint()
	
					   // 使用黑色背景
// 	CRect rc;
// 	GetClientRect(&rc);
// 	dc.FillSolidRect(rc, RGB(0, 0, 255));
}
