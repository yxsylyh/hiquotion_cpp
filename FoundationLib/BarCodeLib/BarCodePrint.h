// BarCodePrint.h: interface for the CBarCodePrint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BARCODEPRINT_H__E7D81E0B_3B60_489B_9A4C_FC9A2BD1FD1C__INCLUDED_)
#define AFX_BARCODEPRINT_H__E7D81E0B_3B60_489B_9A4C_FC9A2BD1FD1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBarCodePrint  
{
public:
	CBarCodePrint();
	virtual ~CBarCodePrint();

	static int printBarCode(LPSTR text, CDC *pDC, float m_CodeWidth, float m_CodeHigh, float ratox, float ratoy, int x, int y);
	static BOOL printText(CString text, CDC *pDC, LPRECT rect, int textAlign, LOGFONT *m_font=NULL);
};

#endif // !defined(AFX_BARCODEPRINT_H__E7D81E0B_3B60_489B_9A4C_FC9A2BD1FD1C__INCLUDED_)
