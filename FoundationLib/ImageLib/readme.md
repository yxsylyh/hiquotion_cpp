# 图像操作类库

## CImageLoader

加载指定目录的图像到 IPictureDisp 对象指针

## CImageConverter

图像转换类

支持 BMP、GIF、JPEG 、Exif 、PNG 、TIFF 、ICON、WMF 、EMF 格式互转
  
	用法：
	在 stdafx.h 中添加如下内容：
	// #include <afxdtctl.h>
	#define ULONG_PTR ULONG
	#include <GDIPlus/Includes/gdiplus.h>
	using namespace Gdiplus;
	#pragma comment(lib, "gdiplus.lib")
	注意：这些内容需要在 std 命名空间之前添加，否则会出现“类模板需要模板参数列表”的错误提示，不能编译通过。

支持如下图像格式之间的转换：

	image/bmp
	image/gif
	image/jpeg
	image/pjpeg
	image/png
	image/x-icon
	image/x-jg
	image/x-png
	image/x-wmf
