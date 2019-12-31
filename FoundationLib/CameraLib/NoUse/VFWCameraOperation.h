#if !defined(AFX_VFWCAMERAOPERATION_H__FF245693_222A_4D91_9C89_479F4A17E36D__INCLUDED_)
#define AFX_VFWCAMERAOPERATION_H__FF245693_222A_4D91_9C89_479F4A17E36D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VFWCameraOperation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVFWCameraOperation window

#include "ivfwcallback.h"
#include <vfw.h>

#define MAX_VFW_DIRVER_COUNT 10
#define MAX_VFW_DEVICE_COUNT 100

enum PreviewMode
{
	Overlay,
	Preview,
};

LRESULT CALLBACK OnCaptureVideoData(HWND hWnd, LPVIDEOHDR lpVHdr);

class CVFWCameraOperation //: public CStatic
{
// 	typedef LRESULT (CALLBACK *VideoDataCallback)(CVFWCameraOperation *opr, LPVIDEOHDR lpVHdr);
// 	typedef LRESULT (CALLBACK *AudioDataCallback)(CVFWCameraOperation *opr, LPWAVEHDR lpWHdr);
// 	typedef LRESULT (CALLBACK *StatusCallback)(CVFWCameraOperation *opr, int nID, LPCSTR lpsz);
// 	typedef LRESULT (CALLBACK *ErrorCallback)(CVFWCameraOperation *opr, int nID, LPCSTR lpsz);
// 	typedef LRESULT (CALLBACK *CaptureControlCallback)(CVFWCameraOperation *opr, int nState);


	// biCompression的值
	// 844715353   YUV2
	// 1498831189  UYVY,biBitCount=16(2 bytes)

	
// Construction
public:
	CVFWCameraOperation();
// 	CVFWCameraOperation(IVFWCallback *vfwCallback);

// Attributes
public:

// Operations
public:
// 	初始化
// 		创建vfw视频捕获窗口
// 		将捕获窗口关联到自身，并设置为自身的子窗口
	BOOL create(CWnd *pWnd, CRect *rect, BOOL visible=FALSE);

	// 获取用户window
	CWnd * getUserWnd() const { return m_pWnd; }

	// 获取用户Rect
	CRect *getUserRect();

	// 获取用户DC
	HDC getUserDC();

	// 获取摄像头的窗口
	HWND getCamaraWnd();

	BOOL getVisible() const { return m_visible; }

	// 获取截图保存路径
	CString getImageSavePath() const { return m_path; }

	// 获取和设置用户数据
	void setUserData(void *userData) { m_userData=userData; }
	void *getUserData() { return m_userData; }

	// 获取视频帧 BitmapInfo 结构
	BITMAPINFO *getBitmapInfo() { return &m_videoInfo; }
	// 获取音频格式信息
	WAVEFORMATEX getAudioFormat() const { return m_audioInfo; }

	// 设置回调函数的接口
	IVFWCallback * getVfwCallback() const;
	void setVfwCallback(IVFWCallback * val);

	// 	获取摄像头驱动个数
	// 		如果设备列表为空，则获取设备
	// 		返回设备列表个数
	int getCameraDriverCount();

	// 获取驱动个数
	int getCameraDeviceCount();

	// 	获取设备列表
	// 		如果设备列表为空，则枚举设备
	// 		返回设备列表
	void getCameraDeviceList(CStringArray &cameraList);

	// 刷新摄像头列表
	void refreshCameraList();

	// 	连接和断开指定摄像头
	BOOL connectCamera(unsigned int index=0);
	BOOL disconnectCamera();

	// 	打开指定摄像头
	BOOL openCamera(unsigned int index=0);

// 	获取和设置窗口参数，包括是否捕获声音等等
	BOOL getCameraParameter(PCAPTUREPARMS para);
	BOOL setCameraparameter(PCAPTUREPARMS para);

//	获取和设置视频格式
	BOOL getVideoFormat(PBITMAPINFO pInfo);
	BOOL setVideoFormat(PBITMAPINFO pInfo);

	// 获取和设置音频格式
	BOOL getAudioFormat(PWAVEFORMATEX pWaveInfo);
	BOOL setAudioFormat(PWAVEFORMATEX pWaveInfo);

// 	获取和设置视频大小（设置视频大小时，自身窗口也要跟着变化）
	BOOL getVideoSize(int &width, int &height);
	BOOL setVideoSize(int width, int height);

// 	捕获预览（Overlay或Preview，默认Preview）
	BOOL startPreview(PreviewMode mode=Preview, int rate=25);

//	停止预览
	BOOL stopPreview();

// 	截取视频图像
	BOOL isCaptureImage() const { return m_isCaptureImage; }
	// 使用 preview 模式
	BOOL captureImage(CString path);
	// 使用 capture 模式
	BOOL saveImage(unsigned char *data, int dataLen);

	// 开始捕获
	BOOL startCapture(HDC hdc, int width=-1, int height=-1);

	// 显示捕获的帧数据（每获取一次数据，就要调用一次）
	BOOL captureShow(unsigned char *data, int dstx, int dsty, int dstWidth=-1, int dstHeight=-1, int srcWidth=-1, int srcHeight=-1);

	// 停止捕获
	void stopCapture();

// 	显示摄像头设备自身的属性
	BOOL showCameraProperty();

// 	capDlgVideoSource
// 	capDlgVideoFormat
	int showVideoSource();
	BOOL showVideoFormat();

// 	关闭指定摄像头
	BOOL closeCamera();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVFWCameraOperation)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVFWCameraOperation();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVFWCameraOperation)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// 	DECLARE_MESSAGE_MAP()

protected:
	// 枚举摄像头驱动到摄像头驱动列表
	void enumCameraDrivers();
	// 枚举摄像头设备到摄像头列表
	void enumCameraDevices();

private:
	// 	设置视频回调函数
	// 	typedef LRESULT (CALLBACK* CAPVIDEOCALLBACK)  (HWND hWnd, LPVIDEOHDR lpVHdr);
	BOOL setVideoCallback();

	// 	设置音频回调函数
	// 	typedef LRESULT (CALLBACK* CAPWAVECALLBACK)   (HWND hWnd, LPWAVEHDR lpWHdr);
	BOOL setAudioCallback();

	//	设置控制回调函数
	// 	typedef LRESULT (CALLBACK* CAPCONTROLCALLBACK)(HWND hWnd, int nState);
	BOOL setControlCallback();

	//	设置设备状态回调函数
	//	LRESULT CALLBACK capStatusCallback(HWND hWnd, int nID, LPCSTR lpsz);
	BOOL setStatusCallback();

	//	设置异常回调函数
	//	LRESULT CALLBACK capErrorCallback(HWND hWnd, int nID, LPCSTR lpsz);
	BOOL setErrorCallback();

public:
// 	VideoDataCallback OnVideoDataCallback;
// 	AudioDataCallback OnAudioDataCallback;
// 	CaptureControlCallback OnCaptureControlCallback;
// 	StatusCallback OnStatusCallback;
// 	ErrorCallback OnErrorCallback;

private:
	HWND m_hWndVideo;

	int m_vfwDevices[MAX_VFW_DEVICE_COUNT];
	int m_vfwDeviceCount;

	HDRAWDIB m_hDib;
	BITMAPINFO m_videoInfo;
	WAVEFORMATEX m_audioInfo;
	CStringArray m_cameraDriverList;
	CStringArray m_cameraList;

	CWnd *m_pWnd;
	HDC m_hdc;
	CRect m_rect;
	BOOL m_visible;
	BOOL m_isCaptureImage;
	CString m_path;

	void *m_userData;

	IVFWCallback *m_vfwCallback;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VFWCAMERAOPERATION_H__FF245693_222A_4D91_9C89_479F4A17E36D__INCLUDED_)
