# 创建快捷方式的类


特别说明：调用前需要调用
	
CoInitialize(NULL);
	
调用之后需要调用
  
CoUninitialize();
  
这两个语句可以在程序加载和程序退出时分别调用。
  
**************

函数功能：对指定文件在指定的目录下创建其快捷方式
  
函数参数：<br>
	lpszFileFullPath    指定文件，为NULL表示当前进程的EXE文件。<br>
	lpszLnkFileDir  指定目录，不能为NULL。<br>
	lpszLnkFileName 快捷方式名称，为NULL表示EXE文件名（.EXE会用.LNK替换）。<br>
	wHotkey         为0表示不设置快捷键<br>
	pszDescription  备注<br>
	iShowCmd        运行方式，默认为常规窗口<br>
  
快捷键说明：
  
低位上是virtual key code，高位上可以是ALT,CTRL等组合键。可以用MAKEWORD(low, high)来生成一个WORD，如Ctrl+F12可以用MAKEWORD(VK_F12, HOTKEYF_CONTROL)表示、
  
ALT,CTRL等组合键：

  HOTKEYF_ALT       ALT key <br>
  HOTKEYF_CONTROL   CTRL key <br>
  HOTKEYF_EXT       Extended key <br>
  HOTKEYF_SHIFT     SHIFT key <br>
