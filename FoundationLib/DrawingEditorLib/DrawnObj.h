#if !defined(AFX_DRAWNOBJ_H__600DF739_337D_454D_8B25_7874E53C9315__INCLUDED_)
#define AFX_DRAWNOBJ_H__600DF739_337D_454D_8B25_7874E53C9315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawnObj.h : header file
//

#include <string>
#include "Tracker.h"
#include <afxole.h>
#include "PropertyList.h"
using namespace std;

#pragma warning(disable : 4786)

/////////////////////////////////////////////////////////////////////////////
// CDrawnObj window

class CDrawnObj : public CWnd
{
// Construction
public:
	CDrawnObj();
	CDrawnObj(CRect rect);

// Attributes
public:
	// 属性
	
	virtual string getType();                             // 获取绘制对象的类型
	virtual string getName();      // 获取绘制对象的名字
	virtual void setName(string name);     // 设置绘制对象的名字
	virtual CTracker getTracker();     // 获取选中框

	CRect getRect();
	void setRect(CRect rc);
	
	BOOL getSelected();                // 获取该绘制对象是否被选择
	void setSelected(BOOL isSelected); // 设置该绘制对象是否被选择

// Operations
public:
	// 方法
	
	virtual void draw(CDC *pDC);                // 屏幕上绘制
	// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
	virtual void drawOnCreating(CDC *pDC);
	virtual BOOL isHitMe(CPoint hitPoint);      // 点鼠标左键后，是否点中了该绘制对象
	virtual void move(CSize moveShift);              // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
	virtual void moveHandle(int nHandle, CPoint point);  // 移动绘制对象Tracker的第nHandle号句柄到point点上
	BOOL intersection(CRect rc);      // 判断绘制对象是否与指定的矩形区域相交
	
	// 	virtual void setOrigPoint(POINT origPoint)=0;
	// 	virtual void setMovingPoint(POINT movingPoint)=0;
	
	virtual void Serialize(CArchive &ar);
	
	BOOL operator ==(CDrawnObj *drawnObj);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawnObj)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawnObj();

	DECLARE_SERIAL(CDrawnObj);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawnObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CRect m_rect;
	
	string m_name;
	
	BOOL m_selected;

	CPropertyList *m_properties;  // 该绘制对象所包含的属性列表

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWNOBJ_H__600DF739_337D_454D_8B25_7874E53C9315__INCLUDED_)
