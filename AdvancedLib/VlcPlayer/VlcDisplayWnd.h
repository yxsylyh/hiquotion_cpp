#pragma once

#include "VlcPlayerWnd.h"
#include <C++/FoundationLib/cxImageLib/ximage.h>

void onCallbackPlaying(void* data);  // 用来设置音量
void onMediaStateChanged(void* data);
void onMediaPlayerEncounteredError(void* data);
void onVlmMediaInstanceStatusError(void* data);

#define WM_USER_ERROR WM_USER+128

// CVlcDisplayWnd
class CVlcDisplayWnd : public CWnd
{
	DECLARE_DYNAMIC(CVlcDisplayWnd)

public:
	CVlcDisplayWnd();
	CVlcDisplayWnd(CWnd* parent);
	virtual ~CVlcDisplayWnd();

	void setFullScreen();
	void SetNormalScreen();

	BOOL playLocal(CString path);  // 打开并播放打开的文件
	BOOL playUrl(CString url);     // 直接播放地址所表示的媒体流

	void pause();  // 暂停
	void stop();   // 停止

	CString getFilePath() { return m_strFilePath; };
	CString getUrl() { return m_url; };

	void setParent(CWnd* parent) { m_parent = parent; };
	CWnd* getParent() { return m_parent; };

	void SetWatermarkString(CString str, int fontSize = 32, int x = 0, int y = 0, COLORREF color = RGB(255, 255, 255), int transparent = 0, int timeout = 0);

	int getSrcType() const { return m_srcType; }

	CAVPlayer& getPlayer() { return m_playWnd.getPlayer(); }

	void setPath(CString path) { m_path = path; }

	void setVolume(int volume) { m_volume = volume; }
	int getVolume() { return m_volume; }

protected:
	DECLARE_MESSAGE_MAP()

	void SetFullScreen(BOOL full);

protected:
	BOOL	m_bIsFullScreen;
	CVlcPlayerWnd m_playWnd;
	CString m_strFilePath;
	CString m_url;
	int m_srcType; // 播放源类型（0-文件，1-url）
	HWND m_parentHWND;
	CWnd* m_parent;
	CRect m_rc;

	CString m_msg; // 界面显示的信息

	CString m_path;

	CxImage m_picture;

	int m_volume;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
};
