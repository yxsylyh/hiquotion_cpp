#include "stdafx.h"
#include "VlcDisplayWndEx.h"

BEGIN_MESSAGE_MAP(CVlcDisplayWndEx, CVlcDisplayWnd)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

CVlcDisplayWndEx::CVlcDisplayWndEx(CWnd* parent)
	:CVlcDisplayWnd(parent)
{

}

void CVlcDisplayWndEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::PostMessage(m_parent->GetSafeHwnd(), WM_LBUTTONDOWN, 0, 0);

	CVlcDisplayWnd::OnLButtonDown(nFlags, point);
}
