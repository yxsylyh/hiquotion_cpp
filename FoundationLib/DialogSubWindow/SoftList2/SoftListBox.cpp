// SoftListBox.cpp : implementation file
//

#include "stdafx.h"
#include "SoftList.h"
#include "SoftListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoftListBox

CSoftListBox::CSoftListBox()
{
}

CSoftListBox::~CSoftListBox()
{
}


BEGIN_MESSAGE_MAP(CSoftListBox, CCheckListBox)
	//{{AFX_MSG_MAP(CSoftListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoftListBox message handlers

void CSoftListBox::setSoftwareList(vector<CSoftware *> softwares)
{
	if(softwares.size()<=0)
		return;

	clearItems();

	for(int i=0;i<softwares.size();i++)
	{
		AddString("");
		CListItemDlg *dlg=new CListItemDlg(this);
		if(!dlg->Create(IDD_DIALOG_LIST_ITEM, this))
		{
			clearItems();
			return;
		}

		dlg->setSoftware(softwares.at(i));
		dlg->setBackColor(RGB(0, 255, 255));
		dlg->setForeColor(RGB(0,0,0));
		dlg->setSelectedBackColor(RGB(0, 0, 255));
		dlg->setSelectedForeColor(RGB(255,255,255));
		dlg->setBgTransparent(TRUE);

		if(i==0)
			dlg->setSelected(TRUE);

		m_items.push_back(dlg);
	}
}



void CSoftListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);

	int i=lpDrawItemStruct->itemID;
	SetItemHeight(i,LIST_ITEM_HIGHT);
	CListItemDlg *dlg=m_items.at(i);
	dlg->MoveWindow(&lpDrawItemStruct->rcItem);
	dlg->ShowWindow(TRUE);

//	CListItemDlg *dlg=new CListItemDlg();
// 	CListItemDlg dlg;
// 	if(!dlg.Create(IDD_DIALOG_LIST_ITEM,this))
// 		return;
// 
// 	dlg.MoveWindow(&lpDrawItemStruct->rcItem);
// 	dlg.ShowWindow(TRUE);

// 	CButton *item=new CButton();
// 	if(!item->Create("", WS_CHILD | WS_VISIBLE, lpDrawItemStruct->rcItem, this, 500))
// 		return;
// 
// 	item->MoveWindow(&lpDrawItemStruct->rcItem);
// 	item->ShowWindow(TRUE);


// 	LPCTSTR lpszText = (LPCTSTR) lpDrawItemStruct->itemData;
// 	ASSERT(lpszText != NULL);
// 
// 	if(m_softwares.size()<=0)
// 		return;
// 
// 	if(i>=m_softwares.size())
// 		return;
// 
// 	CSoftware *soft=m_softwares[i];
// 	string name="【软件名称】"+soft->getName();
// 	string version="【版本】"+soft->getVersion();
// 	string desc="【软件简介】"+soft->getDescription();
// // 	string text="【软件名称】"+name+"\t【版本】"+version;
// // 	text=text+"\n\n【软件简介】"+desc;
// 
// // 	lpszText=text.c_str();
// 
// 	CRect rect=lpDrawItemStruct->rcItem;
// 	rect.DeflateRect(CSize(2,2));
// 	CRect nameRect(rect.left,rect.top,rect.left+rect.Width()*0.6,rect.bottom);
// 	CRect verRect(rect.left+rect.Width()*0.7,rect.top,rect.right-2,rect.bottom);
// 	CRect descRect(rect.left,rect.top+rect.Height()*0.25,rect.right-2,rect.bottom);
// 	
// 	CDC dc;
// 	
// 	dc.Attach(lpDrawItemStruct->hDC);
// 	
// 	// Save these value to restore them when done drawing.
// 	COLORREF crOldTextColor = dc.GetTextColor();
// 	COLORREF crOldBkColor = dc.GetBkColor();
// 	
// 	// If this item is selected, set the background color 
// 	// and the text color to appropriate values. Also, erase
// 	// rect by filling it with the background color.
// 	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
// 		(lpDrawItemStruct->itemState & ODS_SELECTED))
// 	{
// 		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
// 		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
// 		dc.FillSolidRect(&lpDrawItemStruct->rcItem, 
// 			::GetSysColor(COLOR_HIGHLIGHT));
// 	}
// 	else
// 		dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
// 	
// 	// If this item has the focus, draw a red frame around the
// 	// item's rect.
// // 	if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
// // 		(lpDrawItemStruct->itemState & ODS_FOCUS))
// // 	{
// // 		CBrush br(RGB(255, 0, 0));
// // 		dc.FrameRect(&lpDrawItemStruct->rcItem, &br);
// // 	}
// 	
// 	// Draw the text.
// // 	dc.DrawText(
// // 		lpszText,
// // 		strlen(lpszText),
// // 		&lpDrawItemStruct->rcItem,
// // 		DT_CENTER|DT_SINGLELINE|DT_VCENTER);
// 
// 	// 绘制文本
// 	// 绘制软件名称
// 	dc.MoveTo(nameRect.TopLeft());
// 	dc.DrawText(
// 		name.c_str(),
// 		strlen(name.c_str()),
// 		&nameRect,
// // 		DT_CENTER|DT_SINGLELINE|DT_VCENTER);
// 		DT_EXPANDTABS | DT_VCENTER);
// 
// 	// 绘制版本
// 	dc.MoveTo(CPoint(verRect.TopLeft()));
// 	dc.DrawText(
// 		version.c_str(),
// 		strlen(version.c_str()),
// 		// 		&lpDrawItemStruct->rcItem,
// 		&verRect,
// 		// 		DT_CENTER|DT_SINGLELINE|DT_VCENTER);
// 		DT_EXPANDTABS | DT_VCENTER | DT_RIGHT);
// 
// 	// 绘制描述
// 	dc.MoveTo(CPoint(descRect.TopLeft()));
// 	dc.DrawText(
// 		desc.c_str(),
// 		strlen(desc.c_str()),
// 		// 		&lpDrawItemStruct->rcItem,
// 		&descRect,
// 		// 		DT_CENTER|DT_SINGLELINE|DT_VCENTER);
// 		DT_EXPANDTABS | DT_VCENTER);
// 	
// 	// 绘制底线
// 	CPen pen(PS_SOLID,1,RGB(180,180,180));
// 	CPen *oldPen=dc.SelectObject(&pen);
// 	dc.MoveTo(CPoint(rect.left,rect.bottom));
// 	dc.LineTo(CPoint(rect.right,rect.bottom));
// 	dc.SelectObject(oldPen);
// 	
// 	// Reset the background color and the text color back to their
// 	// original values.
// 	dc.SetTextColor(crOldTextColor);
// 	dc.SetBkColor(crOldBkColor);
// 	
// 	dc.Detach();
}

void CSoftListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	lpMeasureItemStruct->itemHeight=LIST_ITEM_HIGHT;
}

void CSoftListBox::clearItems()
{
	for(int i=0;i<m_items.size();i++)
	{
		delete m_items.at(i);
	}
	m_items.clear();
	
	ResetContent();
}
