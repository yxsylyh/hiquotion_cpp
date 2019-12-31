/*
  KeePass Password Safe - The Open-Source Password Manager
  Copyright (C) 2003-2006 Dominik Reichl <dominik.reichl@t-online.de>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "StdAfx.h"
#include "Base64.h"

// static char * base64=(unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";  

static const char *g_pCodes =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char g_pMap[256] =
{
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
	 52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
	255, 254, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,
	  7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
	 19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
	255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
	 37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
	 49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255
};

CBase64::CBase64()
{
}

CBase64::~CBase64()
{
}

bool CBase64::Encode(const unsigned char *pIn, long uInLen, char *pOut, long *uOutLen)
{
	long i, /*len2,*/ leven;

	int outLen=0;
	leven = 3 * (uInLen / 3);
	for(i = 0; i < leven; i += 3)
	{
		pOut[outLen] = g_pCodes[pIn[i] >> 2];
		pOut[outLen+1] = g_pCodes[((pIn[i] & 3) << 4) + (pIn[i+1] >> 4)];
		pOut[outLen+2] = g_pCodes[((pIn[i+1] & 0xf) << 2) + (pIn[i+2] >> 6)];
		pOut[outLen+3] = g_pCodes[pIn[i+2] & 0x3f];
		outLen+=4;
	}

	if(uInLen % 3==1)
	{
		pOut[outLen] = g_pCodes[pIn[i] >> 2];
		pOut[outLen+1] = g_pCodes[((pIn[i] & 3) << 4) + (pIn[i+1] >> 4)];
		pOut[outLen+2] = '=';
		pOut[outLen+3] = '=';
		outLen+=4;
	}
	else if(uInLen % 3==2)
	{
		pOut[outLen] = g_pCodes[pIn[i] >> 2];
		pOut[outLen+1] = g_pCodes[((pIn[i] & 3) << 4) + (pIn[i+1] >> 4)];
		pOut[outLen+2] = g_pCodes[((pIn[i+1] & 0xf) << 2) + (pIn[i+2] >> 6)];
		pOut[outLen+3] = '=';
		outLen+=4;
	}

	pOut[outLen]='\0';

	*uOutLen=outLen;

	return true;
}

bool CBase64::Decode(const char *pIn, long uInLen, unsigned char *pOut, long *uOutLen)
{
	int i,j,pad;
	long n=uInLen;
	long len=0;
	pad=0;

	i=0;
	while(n>0&&pIn[n-1-i]=='=') {
		pad++;
		i++;
	}

	char src[4];

	for(i=0,j=0;i<n-4;i+=4,j+=3) {
		src[0]=getCharIndex(pIn[i]);
		src[1]=getCharIndex(pIn[i+1]);
		src[2]=getCharIndex(pIn[i+2]);
		src[3]=getCharIndex(pIn[i+3]);
		
		if(src[0]==-1 || src[1]==-1 || src[2]==-1 || src[3]==-1)
			return false;

		pOut[j]=(src[0]<<2) + ((src[1]&0x30)>>4);
		pOut[j+1]=((src[1]&0x0F)<<4) + ((src[2]&0x3C)>>2);
		pOut[j+2]=((src[2]&0x03)<<6) + src[3];
		len+=3;
	}

	src[0]=getCharIndex(pIn[n-4]);
	src[1]=getCharIndex(pIn[n-3]);
	src[2]=pIn[n-2]=='=' ? 0 : getCharIndex(pIn[n-2]);
	src[3]=pIn[n-1]=='=' ? 0 : getCharIndex(pIn[n-1]);

	pOut[len]=(src[0]<<2) + ((src[1]&0x30)>>4);
	pOut[len+1]=((src[1]&0x0F)<<4) + ((src[2]&0x3C)>>2);
	pOut[len+2]=((src[2]&0x03)<<6) + src[3];

	len=len+3-pad;
	*uOutLen=len;
	return true;
}

int CBase64::getCharIndex( char ch )
{
	unsigned char *p;
	p=(unsigned char *)strchr((const char *)g_pCodes,(int)ch);
	if(!p)
		return -1;
	return p-(unsigned char *)g_pCodes;
}