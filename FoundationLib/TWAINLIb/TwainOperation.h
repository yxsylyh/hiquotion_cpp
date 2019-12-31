#pragma once
#include "TWAINDSM/include/TwainApp.h"

#ifdef _DEBUG
#pragma comment(lib, "C++/FoundationLib/TWAINLIb/TWAINDSM/lib/debug/TWAINDSM.lib")
#else
#pragma comment(lib, "C++/FoundationLib/TWAINLIb/TWAINDSM/lib/release/TWAINDSM.lib")
#endif

// #pragma comment(lib, "C++/FoundationLib/TWAINLIb/TWAINDSM/lib/FreeImage.lib")

// 去掉了对 FreeImage 的引用，因此无需再包含 FreeImage.h
// 同时 TiffWriter 类也无法再使用

#include <C++/FoundationLib/EventLib/EventEmu-仿MFC的事件处理/IEventRaisable.h>
#include <C++/FoundationLib/EventLib/EventEmu-仿MFC的事件处理/Delegate.h>

// TWAIN 协议包装类
// 可以操作支持 TWAIN 协议的设备（比如高拍仪、扫描仪等）
// 该类会通过 TWAIN 协议，打开设备自己的扫描界面扫描并提交扫描到的图片
// 该类会在设备提交图片的时候，抛出 DataGot 事件，上层应用程序即可获取到图片的缓冲区
// 每张图片抛出一次 DataGot 事件
// DataGot 事件中提供的图片是 BMP 格式的无损图片，需要上层程序自行决定图片下一步的处理，比如压缩、上传等
class CTwainOperation : public TwainApp, public IEventRaisable
{
public:
	CTwainOperation(HWND hwnd = NULL);
	virtual ~CTwainOperation();

	int getDataSourceCount();
	int getDataSourceNames(CStringArray &dataSourceNames);
	BOOL showUI(HWND parent, int dsIndex = 0);

	CString getSavePath() { return m_strSavePath.c_str(); }
	void setSavePath(CString savePath) { m_strSavePath = savePath.GetBuffer(savePath.GetLength()); }

protected:
	void StartScan();
	void Transfer();

protected:
	BOOL        m_bKeepEnabled;         /**< Keep the DS GUI displayed after a scan - User press cancel to finish scanning */
	bool        m_bBusy;                /**< The application is waiting for a responce from TWAIN messages*/

public:
	CDelegate DataGot;
};

