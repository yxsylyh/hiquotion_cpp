// Layout.h: interface for the CLayout class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUT_H__77D133D3_5D31_419A_AAE7_83B508D474E3__INCLUDED_)
#define AFX_LAYOUT_H__77D133D3_5D31_419A_AAE7_83B508D474E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLayout  
{
public:
	CLayout();
	CLayout(CRect rect);
	CLayout(RECT rc);
	CLayout(int left, int top, int width, int height);
	virtual ~CLayout();

	void setRect(CRect rect);
	void setSize(SIZE size);
	void setSize(int cx, int cy);
	virtual void getRect(int index, CRect &rect){};

protected:
	CRect m_rect;
};

#endif // !defined(AFX_LAYOUT_H__77D133D3_5D31_419A_AAE7_83B508D474E3__INCLUDED_)
