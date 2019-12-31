// ShapeObj.h: interface for the CShapeObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPEOBJ_H__039D17D7_6AE3_46C9_B4F0_73CF6ADA4089__INCLUDED_)
#define AFX_SHAPEOBJ_H__039D17D7_6AE3_46C9_B4F0_73CF6ADA4089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "DrawnObj.h"

// 暂时不用
class CShapeObj : public CDrawnObj  
{
public:
	CShapeObj();
	CShapeObj(CRect rect);
	virtual ~CShapeObj();

	// 属性设置

	// 背景色
	COLORREF getBackColor() const { return m_backColor; }
	void setBackColor(COLORREF val) { m_backColor = val; }

	// 背景填充样式
	int getFillStyle() const { return m_fillStyle; }
	void setFillStyle(int val) { m_fillStyle = val; }

	// 边框颜色
	COLORREF getBorderColor() const { return m_borderColor; }
	void setBorderColor(COLORREF val) { m_borderColor = val; }

	// 边框样式
	int getBorderStyle() const { return m_borderStyle; }
	void setBorderStyle(int val) { m_borderStyle = val; }

	// 边框宽度
	virtual int getBorderWidth() const { return m_borderWidth; }
	virtual void setBorderWidth(int val) { m_borderWidth = val; }

	// 方法

	DECLARE_SERIAL(CShapeObj);

	virtual void Serialize(CArchive &ar);

protected:
	COLORREF m_backColor;
	int m_fillStyle;
	COLORREF m_borderColor;
	int m_borderStyle;
	int m_borderWidth;
};

#endif // !defined(AFX_SHAPEOBJ_H__039D17D7_6AE3_46C9_B4F0_73CF6ADA4089__INCLUDED_)
