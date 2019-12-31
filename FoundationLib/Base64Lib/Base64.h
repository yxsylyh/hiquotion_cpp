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

#ifndef ___BASE64_H___
#define ___BASE64_H___

//#include <Windows.h>

class CBase64
{
public:
	CBase64();
	~CBase64();

	static bool Encode(const unsigned char *pIn, long uInLen, char *pOut, long *uOutLen);
	static bool Decode(const char *pIn, long uInLen, unsigned char *pOut, long *uOutLen);
	static int getCharIndex(char ch);
};

#endif // ___BASE64_H___
