# 摄像头操作类 CCaptureVideo

包括如下方法：

```java	
	int EnumDevices(CStringArray& listCamera);  // 只获取设备名称列表
	
	int EnumDevices(std::vector<TDeviceInfo>& deviceVec, REFGUID guidValue);  // 获取设备信息列表，包括名称、支持的分辨率数组等等
	
	HRESULT StartCapture(int iDeviceID);  // 捕获指定id的摄像头
	
	HRESULT StartCapture(int iDeviceID, int width, int height, int avgTimePerFrame);  // 以指定宽高捕获指定id的摄像头
	
	void StopCapture(); // 停止捕获
	
	void setSnapshotAction(int action){ m_action=action; };
	
	void setCallback(ICameraCallback *callback){ m_CB.setCallback(callback); }  // 设置回调函数
```
