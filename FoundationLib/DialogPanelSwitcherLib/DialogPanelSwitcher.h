// DialogPanelSwitcher.h: interface for the CDialogPanelSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGPANELSWITCHER_H__359A8142_8F31_49F2_8D6A_7BD09E510083__INCLUDED_)
#define AFX_DIALOGPANELSWITCHER_H__359A8142_8F31_49F2_8D6A_7BD09E510083__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerList.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>

class CDialogPanelSwitcher : public IEventRaisable
{
public:
	CDialogPanelSwitcher();
	virtual ~CDialogPanelSwitcher();

	void insert(CDialog *dlg);
	void remove(CDialog *dlg);
	void removeAt(unsigned int index);
	int getCount();

	unsigned int getCurrentSelected();
	void setCurrentSelected(unsigned int index);

	unsigned int getOldSelected() const { return m_oldSelected; }
// 	void OldSelected(unsigned int val) { m_oldSelected = val; }

	// 注意：需要判断 oldSelected 是否为 -1
	CDelegate SelectChanged;
	CDelegate SelectChanging;

private:
	CPointerList<CDialog *> m_panelList;

	unsigned int m_currentSelected;
	unsigned int m_oldSelected;
};

class CDialogPanelSwitcherEvent : public IEvent
{
public:
	CDialogPanelSwitcherEvent(IEventRaisable *sender, std::string eventId, unsigned int currentSelected, unsigned int oldSelected);
	virtual ~CDialogPanelSwitcherEvent();

	unsigned int getCurrentSelected() const { return m_currentSelected; }
	unsigned int getOldSelected() const { return m_oldSelected; }

private:
	unsigned int m_currentSelected;
	unsigned int m_oldSelected;
};

#endif // !defined(AFX_DIALOGPANELSWITCHER_H__359A8142_8F31_49F2_8D6A_7BD09E510083__INCLUDED_)
