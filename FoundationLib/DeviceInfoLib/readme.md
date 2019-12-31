# 设备信息类 CHardDiskOperation

主要是获取硬盘序列号。

示例代码

<code>

char * convertString( char *buffer, int size )
{
	int nSize=size;
	
	// 如果 nSize 为奇数，则最后一个字节不处理
	for(int i=0;i<nSize/2;i++)
	{
		char tmp=buffer[2*i];
		buffer[2*i]=buffer[2*i+1];
		buffer[2*i+1]=tmp;
	}
	
	return buffer;
}

int main()
{

	CString strResult;
	strResult=CHardDiskOperation::getFysicalSn(index).c_str();
	
	SystemVersion ver=CSystemVersion::getSystemVersion();  // CSystemVersion 类在 FoundationLib/VersionLib 目录中，需要用 #include 包含。
	if(ver==Win8 || ver==Win8_1)
	{
		int len=strResult.GetLength();
		char *ch=new char[len+1];
		memcpy(ch, strResult.GetBuffer(strResult.GetLength()), strResult.GetLength());
		ch[len]='\0';
		strResult=convertString(ch, len);
		delete ch;
	}
	
	strResult.TrimLeft();
	strResult.TrimRight();
	
	printf("硬盘序列号是：%s", (LPTSTR)(LPCSTR)strResult);

}

</code>
