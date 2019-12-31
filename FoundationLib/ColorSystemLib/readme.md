# 颜色系统转换类

主要方法：
<code>

	// YUY2 转 RGB
	static void YUY2ToRGB(BYTE *YUY2buff, BYTE *RGBbuff, DWORD dwYUVSize);
  
	// BMP 图像垂直翻转
	static void Vertical(BYTE *src, int width, int height, BYTE *dst);

	// YUV2 转 YUV420Planar，Planar是平面格式，H.264编码库需要使用 YUV420 平面格式
	static void YUV2ToYUV420Planar(BYTE *yuv2, int width, int height, BYTE *yuv420planar);

	// YUV420Planar 转 RGB
	static void YUV420PlanarToRGB(BYTE *yuv420planar, int width, int height, BYTE *rgb);

	// YUV420分量 转 RGB
	static void YUV420ToRGB(BYTE *y,BYTE *u, BYTE *v, int width, int height, BYTE *rgb);

	// RGB 转 YUV420Planar
	static void RGBToYUV420Planar(BYTE *rgb, int width, int height, BYTE *yuv420planar);
</code>
