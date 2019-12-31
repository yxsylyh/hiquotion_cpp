#pragma once
#include "VlcDisplayWnd.h"
class CVlcDisplayWndEx :
	public CVlcDisplayWnd
{
public:
	CVlcDisplayWndEx(CWnd* parent);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

