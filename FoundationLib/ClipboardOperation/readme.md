# 剪切板操作类 CClipboardOperation

目前只实现了复制文本的方法。<br>

包括如下方法：
<code>

	static BOOL open(HWND hwnd=NULL);  // 打开剪切板
	static void close();   // 关闭剪切板
	static void clear();   // 清空剪切板

	static void copyText(CString txt);  // 复制文本

</code>
