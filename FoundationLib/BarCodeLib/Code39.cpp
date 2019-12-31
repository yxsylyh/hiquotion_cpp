// Code39.cpp: implementation of the CCode39 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Code39.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCode39::CCode39()
{

}

CCode39::~CCode39()
{

}

int CCode39::Code39Verify(LPCSTR text)
{
	if(text[0]=='\0')
		return -1;
	while(*text&&((*text>='A'&&*text<='z')||
		(*text>='0'&&*text<='9')||
		(*text=='-')||
		(*text=='.')||
		(*text=='$')||
		(*text==' ')||
		(*text=='/')||
		(*text=='+')||
		(*text=='%')||
		(*text=='*')))
		text++;
	if(*text)
		return -1;
	return 0;//OK
}


int CCode39::Code39Encode(LPSTR text, LPSTR partial)
{
	unsigned i;
	//char *str=text;

	if(!partial)
	{
		return -1;
	}
	
	//首字符为*
	strcpy(partial,code39set[43]);
	strcat(partial,"2");

	//如果字符串为空，则返回
	if(!(*text))
	{
		delete partial;
		return -1;
	}
	unsigned kk;
	kk=strlen(text);
	for(i=0;i<kk;i++)
	{

		if(*text>='A'&&*text<='z')
			strcat(partial,code39set[*text-'A'+10]);
		else if(*text>='0'&&*text<='9')
			strcat(partial,code39set[*text-'0']);
		else if(*text=='-')
			strcat(partial,code39set[36]);
		else if(*text=='.')
			strcat(partial,code39set[37]);
		else if(*text==' ')
			strcat(partial,code39set[38]);
		else if(*text=='$')
			strcat(partial,code39set[39]);
		else if(*text=='/')
			strcat(partial,code39set[40]);
		else if(*text=='+')
			strcat(partial,code39set[41]);
		else if(*text=='%')
			strcat(partial,code39set[42]);
		else if(*text=='*')
			strcat(partial,code39set[43]);
		else
		{
			delete partial;
			return -1;
		}

		text++;
		//每两个字符之间加一个白线
		strcat(partial,"2");
	}
	//结束符为*
	strcat(partial,code39set[43]);

	return 0;
}
