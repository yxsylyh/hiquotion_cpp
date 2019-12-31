#pragma once

#include "AVPlayer.h"

// CVlcPlayerWnd
// VLC播放器的窗口，一旦设置给VLC播放器，则窗口消息会被播放器接管
class CVlcPlayerWnd : public CStatic
{
	DECLARE_DYNAMIC(CVlcPlayerWnd)

public:
	CVlcPlayerWnd();
	virtual ~CVlcPlayerWnd();

	CAVPlayer& getPlayer() { return m_myPlayer; };

protected:
	DECLARE_MESSAGE_MAP()

private:
	CAVPlayer m_myPlayer;		//	VLC Player

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};
