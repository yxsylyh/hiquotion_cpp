#pragma once

#include <vfw.h>

class IVFWCallback
{
public:
	IVFWCallback(void);
	~IVFWCallback(void);

	virtual LRESULT OnVideoDataReceived(LPVIDEOHDR lpVHdr){return 0;};
	virtual LRESULT OnAudioDataReceived(LPWAVEHDR lpWHdr){return 0;};
	virtual LRESULT OnStatus(int nID, LPCSTR lpsz){return 0;};
	virtual LRESULT OnError(int nID, LPCSTR lpsz){return 0;};
// 	virtual LRESULT OnCaptureControl(int nState){return 0;};
};
