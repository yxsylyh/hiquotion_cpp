// Polygram.h: interface for the CPolygram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGRAM_H__DB352AEB_F352_4CB1_BE06_64E734E2E04C__INCLUDED_)
#define AFX_POLYGRAM_H__DB352AEB_F352_4CB1_BE06_64E734E2E04C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "DrawnObj.h"

class CPolygram : public CDrawnObj  
{
public:
	CPolygram();
	virtual ~CPolygram();

protected:
	DECLARE_SERIAL(CPolygram);
};

#endif // !defined(AFX_POLYGRAM_H__DB352AEB_F352_4CB1_BE06_64E734E2E04C__INCLUDED_)
