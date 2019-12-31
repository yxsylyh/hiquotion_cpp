// GridCellImage.h: interface for the CGridCellImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLIMAGE_H__065274B0_C282_4622_9C78_D20EC954B896__INCLUDED_)
#define AFX_GRIDCELLIMAGE_H__065274B0_C282_4622_9C78_D20EC954B896__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../GridCtrl_src/GridCell.h"
#include <C++\FoudationLib\DrawingLib\Picture.h>

class CGridCellImage : public CGridCell  
{
	friend class CGridCtrl;
	DECLARE_DYNCREATE(CGridCellImage)
public:
	void setIcon(HICON hicon);

	void loadImageResouce(UINT res, DWORD iType, CString catalog="Bitmap");
	void loadImage(CString path);
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
public:
	CGridCellImage();
	virtual ~CGridCellImage();

private:
	HICON m_hicon;
	CPicture m_picture;
};

#endif // !defined(AFX_GRIDCELLIMAGE_H__065274B0_C282_4622_9C78_D20EC954B896__INCLUDED_)
