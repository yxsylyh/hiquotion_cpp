// GridCellImage.cpp: implementation of the CGridCellImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCellImage.h"
#include "../GridCtrl_src/GridCell.h"
#include "../GridCtrl_src/GridCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGridCellImage, CGridCell)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCellImage::CGridCellImage()
: m_hicon(NULL)
{

}

CGridCellImage::~CGridCellImage()
{

}

void CGridCellImage::loadImage( CString path )
{
	m_picture.setPath((LPTSTR)(LPCSTR)path, CXIMAGE_SUPPORT_PNG);
}

void CGridCellImage::setIcon(HICON hicon)
{
	m_hicon=hicon;
}

void CGridCellImage::loadImageResouce( UINT res, DWORD iType, CString catalog )
{
	m_picture.setResource(res, iType, catalog);	
}

BOOL CGridCellImage::Draw( CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd /*= TRUE*/ )
{
	CRect rc;

	if(m_hicon)
	{
		rc.left=(rect.Width()-GetSystemMetrics(SM_CXICON))/2+rect.left;
		rc.top=(rect.Height()-GetSystemMetrics(SM_CYICON))/2+rect.top;

// 		pDC->DrawIcon(rc.left, rc.top, AfxGetApp()->LoadStandardIcon(IDI_APPLICATION));
		pDC->DrawIcon(rc.left, rc.top, m_hicon);
	}
	else
	{
		rc.left=(rect.Width()-m_picture.getImageWidth())/2+rect.left;
		rc.top=(rect.Height()-m_picture.getImageHeight())/2+rect.top;
		rc.right=rc.left+m_picture.getImageWidth();
		rc.bottom=rc.top+m_picture.getImageHeight();

		m_picture.setFillStyle(1);
// 		m_picture.setBackColor();
		m_picture.setRect(rc);
		m_picture.draw(pDC);
	}

	return TRUE;
}
