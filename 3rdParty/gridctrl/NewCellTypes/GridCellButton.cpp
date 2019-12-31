#include "stdafx.h"
#include "../GridCtrl_src/GridCell.h"
#include "../GridCtrl_src/GridCtrl.h"
#include "GridCellButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGridCellButton, CGridCell)

CGridCellButton::CGridCellButton(void)
{
	m_bPushing = FALSE;
}
CGridCellButton::~CGridCellButton(void)
{
}
BOOL CGridCellButton::Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd /* = TRUE */)
{ 
         m_rect = rect;
	 pDC->SetBkMode(TRANSPARENT);
	 rect.DeflateRect( GetMargin(), 0);
	 CFont* pOldFont = pDC->SelectObject(GetFontObject());
	 pDC->DrawFrameControl(rect, DFC_BUTTON, m_bPushing?DFCS_BUTTONPUSH | DFCS_PUSHED:DFCS_BUTTONPUSH);
	 COLORREF ColorCurrent = pDC->GetTextColor();
	 pDC->SetTextColor(::GetSysColor(COLOR_BTNTEXT));
	 pDC->DrawText(GetText(), -1, rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	 pDC->SetTextColor( ColorCurrent);
	 return TRUE;
}
void CGridCellButton::OnClick(CPoint PointCellRelative)
{
	m_bPushing = FALSE;
	m_nState=GVIS_SELECTED;
	GetGrid()->InvalidateRect(m_rect);

	// 限制一下点击位置所在矩形为按钮矩形，如果点击位置不在该矩形内，则返回
	CRect rect(0, 0, m_rect.Width(), m_rect.Height());
	if(!rect.PtInRect(PointCellRelative))
		return;

	CCellID cellId=GetGrid()->GetFocusCell();
	CWnd *wnd=GetGrid()->GetParent();
	if(wnd)
		if(wnd->GetSafeHwnd())
		{
			wnd->SendMessage(MSG_BUTTON_CLICK, cellId.row, cellId.col);
		}
}

void CGridCellButton::OnClickDown( CPoint PointCellRelative )
{
	m_bPushing = TRUE;
	m_nState=GVIS_SELECTED;
	GetGrid()->InvalidateRect(m_rect);
}

void CGridCellButton::OnDblClick( CPoint PointCellRelative )
{
	m_bPushing = FALSE;
	m_nState=GVIS_FOCUSED;
	GetGrid()->InvalidateRect(m_rect);
}
