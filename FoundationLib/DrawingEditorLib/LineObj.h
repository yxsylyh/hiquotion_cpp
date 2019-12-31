// LineObj.h: interface for the CLineObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEOBJ_H__328EEA23_80C7_4213_8259_5D23C41EF19A__INCLUDED_)
#define AFX_LINEOBJ_H__328EEA23_80C7_4213_8259_5D23C41EF19A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "DrawnObj.h"
#include "Property.h"

// 暂时不用
class CLineObj : public CDrawnObj  
{
public:
	CLineObj();
	virtual ~CLineObj();

	CLineObj(CRect rect);

	DECLARE_SERIAL(CLineObj);

	virtual void Serialize(CArchive &ar);

public:
	// 属性
	virtual int getLineStyle();   // 获取线条样式
	virtual void setLineStyle(int lineStyle);   // 设置线条样式
	virtual int getLineColor();   // 获取线条颜色
	virtual void setLineColor(int lineColor);   // 设置线条颜色
	virtual int getLineWidth();   // 获取线条宽度
	virtual void setLineWidth(int lineWidth);   // 设置线条宽度

protected:
	int m_lineColor;
	int m_lineStyle;
	int m_lineWidth;

};

#endif // !defined(AFX_LINEOBJ_H__328EEA23_80C7_4213_8259_5D23C41EF19A__INCLUDED_)
