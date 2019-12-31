// Code128.cpp: implementation of the CCode128 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Code128.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCode128::CCode128()
{

}

CCode128::~CCode128()
{

}

int CCode128::Code128BVerify(LPCSTR text)
{
   if (text[0] == '\0')
		return -1;

   while (*text && *text>=32 && !(*text&0x80))
		text++;

   if (*text)
		return -1; // 不是合法的字符

   return 0; 
}

int CCode128::Code128BEncode(LPSTR text, LPSTR partial)
{
	unsigned i;
	int code,checksum=0;
	char *str=text;


	if(!partial)
	{
		return -1;
	}
	
	//首字符为START_B(HEAD)
	strcat(partial,code128set[START_B]);
	//首字符也要加到校验和中去
	checksum+=START_B;

	//如果字符串为空，则返回
	if(!str)
	{
		delete partial;
		return -1;
	}

	for(i=0;i<strlen(str);i++)
	{
		if ( str[i] < 32 || (str[i] & 0x80))
		{
			//如为非法字符，则返回
			free(partial);
			return -1;
		}
		
		code = str[i]-32;
		strcat(partial, code128set[code]);
		//校验和为：first * 1 + second * 2 + third * 3... 
		checksum += code * (i+1); 
	}

	//最终校验和为除以103所得的余数
	checksum%=103;
	//将校验和加入partial
	strcat(partial,code128set[checksum]);
	//加入STOP结尾字符
	strcat(partial,code128set[STOP]);

	return 0;
}

int CCode128::Code128CVerify(LPCSTR text)
{
	if (text[0] == '\0')
		return -1;

	//字符数目必须为偶数个
	if (strlen(text)%2)
		return -1;

	//所有字符必须都是数字
	for (; *text; text++)
		if (!isdigit(*text))
			return -1;

	return 0;
}

int CCode128::Code128CEncode(LPSTR text, LPSTR partial)
{
	int i,code,checksum=0;
	char *str=text;


	if(!partial)
	{
		return -1;
	}

	//首字符为START_C(HEAD)
	strcat(partial,code128set[START_C]);
	//首字符也要加到校验和中去
	checksum+=START_C;

	//如果字符串为空，则返回
	if(!str)
	{
		delete partial;
		return -1;
	}

	for(i=0;str[i];i+=2)
	{
		if(!isdigit(str[i])||!isdigit(str[i+1]))
		{
			free(partial);
			return -1;
		}
		code=(str[i]-'0')*10+str[i+1]-'0';
		strcat(partial,code128set[code]);
		//校验和为：first * 1 + second * 2 + third * 3... 
		checksum+=code*(i/2+1);
	}

	//最终校验和为除以103所得的余数
	checksum%=103;
	//将校验和加入partial
	strcat(partial,code128set[checksum]);
	//加入STOP结尾字符
	strcat(partial,code128set[STOP]);

	return 0;
}

int CCode128::Code128AEncode(LPSTR text, LPSTR partial)
{
	unsigned i;
	int code,checksum=0;
	char *str=text;


	//分配空间
	if(!partial)
	{
		return -1;
	}

	//首字符为START_A(HEAD)
	strcat(partial,code128set[START_A]);
	//首字符也要加到校验和中去
	checksum+=START_A;

	//如果字符串为空，则返回
	if(!str)
	{
		delete partial;
		return -1;
	}
	for(i=0;i<strlen(str);i++)
	{
		if ( str[i] > 95 && !(str[i] & 0x80))
		{
			//如为非法字符，则返回
			free(partial);
			return -1;
		}
		
		if (str[i]<32)
		{
			code=str[i]+64;
		}
		else if((str[i]>=32)&&(str[i]<=95))
		{
			code=str[i]-32;
		}
		else if(str[i]==0xc1)
		{
			code=FUNC_1;
		}
		else if(str[i]==0xc2)
		{
			code=FUNC_2;
		}
		else if(str[i]==0xc3)
		{
			code=FUNC_3;
		}
		else if(str[i]==0xc4)
		{
			code=CODE_A;
		}
		else if(str[i]==0x80)
		{
			code=64;
		}

		strcat(partial, code128set[code]);
		//校验和为：first * 1 + second * 2 + third * 3... 
		checksum += code * (i+1); 
	}

	//最终校验和为除以103所得的余数
	checksum%=103;
	//将校验和加入partial
	strcat(partial,code128set[checksum]);
	//加入STOP结尾字符
	strcat(partial,code128set[STOP]);



	return 0;
}

int CCode128::Code128AVerify(LPCSTR text)
{
	while (*text&&(*text<=95 ||(*text&0x80)))
		text++;

	if (*text)
		return -1; // 不是合法的字符

	return 0;
}