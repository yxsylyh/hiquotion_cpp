// ImageButton.cpp : implementation file
//

#include "stdafx.h"
#include "FVerifyShell.h"
#include "ImageButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageButton

CImageButton::CImageButton()
{
	m_isMouseDown=FALSE;
}

CImageButton::~CImageButton()
{
}


BEGIN_MESSAGE_MAP(CImageButton, CButton)
	//{{AFX_MSG_MAP(CImageButton)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageButton message handlers

BOOL CImageButton::setImage(HRSRC res, UINT imageType)
{
	if(m_btnImage.LoadResource(res, imageType)==true)
		return TRUE;
	else
		return FALSE;
}

BOOL CImageButton::setImage(CString imgFile, UINT imageType)
{
	if(m_btnImage.Load(imgFile, imageType)==true)
		return TRUE;
	else
		return FALSE;
}

void CImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC ButtonDC;   
	ButtonDC.Attach(lpDrawItemStruct->hDC); //得到用于绘制按钮的DC

	CRect rc=lpDrawItemStruct->rcItem; //获取按钮所占的矩形大小
	UINT state = lpDrawItemStruct->itemState; //获取按钮目前所处的状态，根据不同的状态绘制不同的按钮

	if(this->IsWindowVisible())
	{
		if(m_isMouseDown)
		{
			CSize size(1,1);
			rc.OffsetRect(size);
		}
		m_btnImage.Draw(lpDrawItemStruct->hDC, rc);
	}
}

BOOL CImageButton::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= BS_OWNERDRAW;

	return CButton::PreCreateWindow(cs);
}

void CImageButton::OnDestroy() 
{
	CButton::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_btnImage.IsValid())
		m_btnImage.Destroy();
}

void CImageButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_isMouseDown=TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CImageButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_isMouseDown=FALSE;

	CButton::OnLButtonUp(nFlags, point);
}
