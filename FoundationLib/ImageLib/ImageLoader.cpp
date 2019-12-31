// ImageLoader.cpp: implementation of the CImageLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageLoader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageLoader::CImageLoader()
{

}

CImageLoader::~CImageLoader()
{

}

IPictureDisp *CImageLoader::loadPicture(CString path)
{
	if(path=="")
		return NULL;

	CFile file;
	LONG cb=0;

	if(!file.Open(path,CFile::modeRead | CFile::shareDenyWrite))
		return NULL;

	cb=file.GetLength();
	if(cb<=2)
	{
		file.Close();
		return NULL;
	}

	IStream *pStm=NULL;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);  
	LPVOID pvData = NULL;  
	if (hGlobal != NULL)  
	{  
		if ((pvData = GlobalLock(hGlobal)) != NULL)  
		{  
			file.Read(pvData, cb);  
			GlobalUnlock(hGlobal);  
			CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);  
		} 
	} 

	IPictureDisp *pPic;  
	HRESULT hr=OleLoadPicture(pStm,cb,TRUE,IID_IPictureDisp,(LPVOID*)&pPic); 
	if(SUCCEEDED(hr))
		return pPic;
	
	return NULL;

}
