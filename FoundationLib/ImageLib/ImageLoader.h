// ImageLoader.h: interface for the CImageLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGELOADER_H__E604C6F7_E893_48E7_B295_FFFDC02DC2A0__INCLUDED_)
#define AFX_IMAGELOADER_H__E604C6F7_E893_48E7_B295_FFFDC02DC2A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "include.h"

class CImageLoader  
{
public:
	CImageLoader();
	virtual ~CImageLoader();

	static IPictureDisp *loadPicture(CString path);
};

#endif // !defined(AFX_IMAGELOADER_H__E604C6F7_E893_48E7_B295_FFFDC02DC2A0__INCLUDED_)
