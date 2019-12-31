# 数字生成条码类库说明

类名|类说明|备注
----|----|----
CCode39|code39编码类，将一串数字转换成code39编码|源码来源于网络
CCode128|code128编码类，将一串数字转换成code128编码|源码来源于网络
CBarCodePrint|打印条码和条码下面的文字的类|源码一部分来源于网络

示例代码

```java
BOOL CZzspbcDlg::print(CString id, CString name)
{
	CDC dc;
	int printQuality;
	LPSTR partial=NULL,text;

	text=id.GetBuffer(50);

	//分配空间
	partial=new char[(strlen(text)+3)*6+2];
	partial[0]='\0';
	
	if(code128.Code128CEncode (text,partial)==-1)
	{
		MessageBox("编码错误", "系统错误", MB_ICONERROR);
		delete partial;
		return FALSE;
	}

	PRINTDLG printInfo;
	ZeroMemory(&printInfo,sizeof(printInfo));  //清空该结构
	printInfo.lStructSize = sizeof(printInfo);   
	printInfo.hwndOwner = 0;   
	printInfo.hDevMode = 0;
	printInfo.hDevNames = 0;
	//这个是关键，PD_RETURNDC 如果不设这个标志，就拿不到hDC了
	//            PD_RETURNDEFAULT 这个就是得到默认打印机，不需要弹设置对话框
	printInfo.Flags = PD_RETURNDC | PD_RETURNDEFAULT | PD_ALLPAGES;  

	PrintDlg(&printInfo);//调用API拿出默认打印机
	DWORD rst = CommDlgExtendedError();//看看出错没有
	if(rst != 0)
	{//出错了，清空标志再次调用API，此时就会弹出打印设置对话框供用户选择了
		printInfo.Flags = 0;
		PrintDlg(&printInfo);
	}

	rst = CommDlgExtendedError();
	if(rst != 0)
	{
		delete partial;
		return FALSE;
	}
	
	//获取打印机的打印质量
// 	DEVMODE *dm = printDlg.GetDevMode(); 
// 	printQuality=dm->dmPrintQuality;
	printQuality=600;

	dc.Attach(printInfo.hDC);

	dc.m_bPrinting=TRUE;

	CString strTitle="打印条形码";

	DOCINFO di; // DOCINFO中有相关的打印信息
	::ZeroMemory (&di, sizeof (DOCINFO));
	di.cbSize = sizeof (DOCINFO);
	di.lpszDocName = strTitle;//设置标题
	
	int ret=dc.StartDoc(&di);
	if(ret<=0)// 开始打印
	{
		MessageBox("打印机没有被初始化！", "系统错误", MB_ICONERROR);
		delete partial;
		return FALSE;
	}

	int horze=dc.GetDeviceCaps (HORZRES);
	int vertical=dc.GetDeviceCaps (VERTRES);
	
	dc.StartPage();

	//每毫米打印的像素数
	float rato=float(printQuality/25.4);
	CBarCodePrint::printBarCode(partial, &dc, (float)0.2, (float)4.9, rato, 20, -10);

	RECT rect;
	rect.left=20;
	rect.top=110;//90;//130
	rect.right=210;
	rect.bottom=300;

	LOGFONT m_font;
	memset(&m_font,0x00,sizeof(m_font));
	strcpy(m_font.lfFaceName,"宋体");
	m_font.lfHeight=GetDeviceCaps(dc.m_hDC, LOGPIXELSY)*10/72; //160;
	m_font.lfWidth=GetDeviceCaps(dc.m_hDC, LOGPIXELSX)*5/72; //80;
	m_font.lfUnderline=0;
	m_font.lfStrikeOut=0;
	m_font.lfWeight=700;

	//	CBarCodePrint::printText(m_name, &dc, 0, 90);
	CBarCodePrint::printText(m_name, &dc, &rect, 0, &m_font);

	rect.left=210;
	rect.top=110;//90;//130
	rect.right=380;
	rect.bottom=300;

// 	CBarCodePrint::printText(m_id, &dc, 195, 90);
	CBarCodePrint::printText(m_id, &dc, &rect, 2, &m_font);

	dc.EndPage();
	dc.EndDoc();
	id.ReleaseBuffer();
	delete partial;

	return TRUE;
}
```
