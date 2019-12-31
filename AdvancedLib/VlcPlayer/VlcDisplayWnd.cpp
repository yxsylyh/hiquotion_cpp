// VlcDisplayWnd.cpp: 实现文件
//

#include "stdafx.h"
#include "VlcDisplayWnd.h"
#include <C++/FoundationLib/StringExtLib/StringConverter.h>

CString m_errMsg; // 播放器异常后抛出给外面的信息

// CVlcDisplayWnd

IMPLEMENT_DYNAMIC(CVlcDisplayWnd, CWnd)

CVlcDisplayWnd::CVlcDisplayWnd()
{
#ifdef _UNICODE
	m_msg = L"正在加载，请稍候……";
#else
	m_msg = "正在加载，请稍候……";
#endif
}

CVlcDisplayWnd::CVlcDisplayWnd(CWnd* parent)
	: m_bIsFullScreen(FALSE),
	m_strFilePath(""),
	m_url(""),
	m_srcType(0),
	m_parentHWND(NULL),
	m_parent(parent),
	m_volume(0)
{
#ifdef _UNICODE
	m_msg = L"";
#else
	m_msg = "";
#endif

	m_playWnd.getPlayer().SetFnData(this);
	m_playWnd.getPlayer().SetCallbackPlaying(onCallbackPlaying);
	m_playWnd.getPlayer().SetCallbackMediaStateChanged(onMediaStateChanged);
	m_playWnd.getPlayer().SetCallbackMediaPlayerEncounteredError(onMediaPlayerEncounteredError);
	m_playWnd.getPlayer().SetCallbackVlmMediaInstanceStatusError(onVlmMediaInstanceStatusError);
}

CVlcDisplayWnd::~CVlcDisplayWnd()
{
	stop();
}


BEGIN_MESSAGE_MAP(CVlcDisplayWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CVlcDisplayWnd 消息处理程序


BOOL CVlcDisplayWnd::playLocal(CString path)
{
	if (path.GetLength() <= 0)
		return FALSE;
#ifdef _UNICODE
	 	std::string spath = CStringConverter::UnicodeToUtf8(path.GetBuffer(path.GetLength()));
		m_msg = L"正在加载，请稍候……";
#else
	 	std::string spath = CStringConverter::MultibyteToUtf8(path.GetBuffer(path.GetLength()));
		m_msg = "正在加载，请稍候……";
#endif

	if (path == m_strFilePath)
	{
		if(!m_playWnd.getPlayer().IsPlaying())
			m_playWnd.getPlayer().Play(spath);
		
		return TRUE;
	}

	if (m_playWnd.getPlayer().IsPlaying())
		m_playWnd.getPlayer().Stop();

	bool ret = m_playWnd.getPlayer().Play(spath);
	if (ret == false)
	{
		m_msg = m_playWnd.getPlayer().getErrMsg().data();
		Invalidate(TRUE);
		return FALSE;
	}

	if (!m_playWnd.getPlayer().IsOpen())
		return FALSE;

	//禁用鼠标消息
	m_playWnd.EnableWindow(FALSE);

// 	m_playWnd.getPlayer().Play();

	m_srcType = 0;

	m_strFilePath = path;
	m_url = "";
	
	return TRUE;
}

BOOL CVlcDisplayWnd::playUrl(CString url)
{
	if (url.GetLength() <= 0)
		return FALSE;

#ifdef _UNICODE
	std::string surl = CStringConverter::UnicodeToUtf8(url.GetBuffer(url.GetLength()));
	m_msg = L"正在加载，请稍候……";
#else
	std::string surl = CStringConverter::MultibyteToUtf8(url.GetBuffer(url.GetLength()));
	m_msg = "正在加载，请稍候……";
#endif

// 	if (url == m_url)
// 	{
// 		if (!m_playWnd.getPlayer().IsPlaying())
// 			m_playWnd.getPlayer().PlayUrl(surl);
// 
// 		Invalidate(TRUE);
// 
// 		return TRUE;
// 	}

	if (m_playWnd.getPlayer().IsPlaying())
		m_playWnd.getPlayer().Stop();

	bool ret = m_playWnd.getPlayer().PlayUrl(surl);
	if (ret == false)
	{
		m_msg = m_playWnd.getPlayer().getErrMsg().data();
		Invalidate(TRUE);
		return FALSE;
	}

	//禁用鼠标消息
	m_playWnd.EnableWindow(FALSE);

	m_srcType = 1;

	m_strFilePath = "";
	m_url = url;

	Invalidate(TRUE);

	return TRUE;
}

void CVlcDisplayWnd::pause()  // 暂停
{
	m_playWnd.getPlayer().Pause();
}

void CVlcDisplayWnd::stop()   // 停止
{
	m_msg = TEXT("");
	m_playWnd.getPlayer().Stop();
}

void CVlcDisplayWnd::SetWatermarkString(CString str, int fontSize /*= 32*/, int x /*= 0*/, int y /*= 0*/, COLORREF color /*= RGB(255, 255, 255)*/, int transparent /*= 0*/, int timeout /*= 0*/)
{
	m_playWnd.getPlayer().SetWatermarkString(str, fontSize, x, y, color, transparent, timeout);
}

void onCallbackPlaying(void* data)
{
	CVlcDisplayWnd* wnd = (CVlcDisplayWnd*)data;
	wnd->getPlayer().Volume(wnd->getVolume());
}

void onMediaStateChanged(void* data)
{
	CVlcDisplayWnd* wnd = (CVlcDisplayWnd*)data;
	if (wnd->getPlayer().IsPlayingError())
	{
		m_errMsg = TEXT("MediaStateInError");
		::PostMessage(wnd->getParent()->GetSafeHwnd(), WM_USER_ERROR, (WPARAM)&m_errMsg, 0);
	}
}

void onMediaPlayerEncounteredError(void* data)
{
	CVlcDisplayWnd* wnd = (CVlcDisplayWnd*)data;
	m_errMsg = TEXT("MediaPlayerEncounteredError");
	::PostMessage(wnd->getParent()->GetSafeHwnd(), WM_USER_ERROR, (WPARAM)&m_errMsg, 0);
}

void onVlmMediaInstanceStatusError(void* data)
{
	CVlcDisplayWnd* wnd = (CVlcDisplayWnd*)data;
	m_errMsg = TEXT("VlmMediaInstanceStatusError");
	::PostMessage(wnd->getParent()->GetSafeHwnd(), WM_USER_ERROR, (WPARAM)&m_errMsg, 0);
}

void CVlcDisplayWnd::setFullScreen()
{
	SetFullScreen(TRUE);
}

void CVlcDisplayWnd::SetNormalScreen()
{
	SetFullScreen(FALSE);
}

void CVlcDisplayWnd::SetFullScreen(BOOL full)
{
	m_bIsFullScreen = full;

	if (full)
	{
		GetClientRect(&m_rc);
//		SetParent(GetDesktopWindow());  // 获取桌面窗口句柄
		SetParent(GetTopLevelFrame());  // 获取顶层窗口句柄
		//隐藏标题栏
		//SetWindowLong(GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) - WS_CAPTION);
		ShowWindow(SW_MAXIMIZE);
	}
	else
	{
		SetParent(m_parent);
		//SetWindowLong(this->GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) + WS_CAPTION);
		ShowWindow(SW_NORMAL);
		m_playWnd.MoveWindow(m_rc);
		m_playWnd.ShowWindow(SW_SHOW);
	}
}



int CVlcDisplayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	lpCreateStruct->style = WS_CHILD | -WS_OVERLAPPED | -WS_CAPTION;

	m_parentHWND = lpCreateStruct->hwndParent;

	return 0;
}


BOOL CVlcDisplayWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CString strWndClass = AfxRegisterWndClass(CS_DBLCLKS, AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)(COLOR_DESKTOP + 1), AfxGetApp()->LoadStandardIcon(IDI_WINLOGO));
	if (!CreateEx(0, strWndClass, _T("VlcPlayerWnd"), WS_POPUP /*WS_CHILD*/ /*WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX*/, rect, pParentWnd, NULL))
		return FALSE;

	if (!m_playWnd.Create(L"", WS_CHILD, { 0, 0, rect.right - rect.left, rect.bottom - rect.top }, this))
		return FALSE;

	m_playWnd.SetParent(this);

	m_parent = pParentWnd;
// 	m_playWnd.getPlayer().SetHWND(m_playWnd.GetSafeHwnd());

	return TRUE;

	//return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CVlcDisplayWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (m_playWnd.GetSafeHwnd())
	{
		m_playWnd.getPlayer().SetHWND(m_playWnd.GetSafeHwnd());

		m_playWnd.ShowWindow(bShow);
	}
}


void CVlcDisplayWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_playWnd.GetSafeHwnd())
		m_playWnd.MoveWindow(0, 0, cx, cy);

	Invalidate();
}


void CVlcDisplayWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bIsFullScreen)
		SetNormalScreen();
	else if(m_playWnd.getPlayer().IsPlaying())
		SetFullScreen(!m_bIsFullScreen);

	//CWnd::OnLButtonDblClk(nFlags, point);
}


void CVlcDisplayWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 收不到键盘按下的消息。。。
	if (nChar == VK_ESCAPE)
		SetNormalScreen();

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CVlcDisplayWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()

	CRect rect;
	GetClientRect(&rect);

	bool bret = m_picture.Load(CStringConverter::UnicodeToAnsi(m_path).c_str(), CXIMAGE_FORMAT_PNG);
	if (bret)
	{
		m_picture.Draw2(dc.GetSafeHdc(), rect);
	}
	
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);    // 设置文字背景透明，等于使用矩形的背景色
	CRect rc(rect.right - 160, 8, rect.right, 32);
	dc.DrawText(m_msg, &rc, DT_WORDBREAK);

// 	// 使用黑色背景
// 	CRect rc;
// 	GetClientRect(&rc);
// 	dc.FillSolidRect(rc, RGB(0, 0, 0));
}
