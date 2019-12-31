/********************************************************************
	created:	2009/09/27
	created:	27:9:2009   9:14
	filename: 	/GridCtrl/NewCellTypes/GridCellButton.h
	file path:	/GridCtrl/NewCellTypes
	file base:	GridCellButton
	file ext:	h
	author:		Li JianGong
	
	purpose:	Create button cell
*********************************************************************/
#include "../GridCtrl_src/GridCell.h"

#define MSG_BUTTON_CLICK WM_USER+10

class CGridCellButton : public CGridCell
{
	friend class CGridCtrl;
	DECLARE_DYNCREATE(CGridCellButton)
public:
	CGridCellButton(void);
	~CGridCellButton(void);
public:
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
protected:
	virtual void OnClick( CPoint PointCellRelative);
	virtual void OnClickDown( CPoint PointCellRelative);
    virtual void OnDblClick( CPoint PointCellRelative);

protected:
        CRect m_rect;
	BOOL m_bPushing; 
};
