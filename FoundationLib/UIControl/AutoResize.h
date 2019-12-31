#pragma once

/****************************************
*
* 自动改变父窗口内子窗口的大小和位置
*
* 使用方法：
*
* 1、在 .h 文件中引用
*         #include "AutoResize.h"
*
* 2、在 .h 文件中声明
*         Declare_AutoResize
*
* 3、在 .cpp 文件中设置子窗口四个边的类型（原始类型 Original 或锚点类型 Anchor）
*    可以使用以下三个宏定义
*         Init_AutoResize_Normal(子窗口id, 父窗口类指针）
*         Init_AutoResize(子窗口id, 父窗口类指针, 左边类型, 上边类型, 右边类型, 下边类型）
*         Init_AutoResize_Fill(子窗口id, 父窗口类指针）
*   第一种是Windows默认类型，即左和上的位置是固定的（即锚点类型），
*         右和下是原始类型（即宽和高保持不变）
*   第二种需要手动设置四个边的类型
*   第三种表示子窗口在父窗口中平铺占满父窗口的整个空间
*
* 4、在父窗口的OnSize事件中添加如下宏定义
*         Do_Resize(cx, cy);
*
*****************************************/

#include <FoundationLib/DataStructLib/PointerList.h>

#define Declare_AutoResize \
	CAutoResizeManager m_auto;

// Maybe no use of Init_AutoResize_Normal definition...
#define Init_AutoResize_Normal(id, parent) \
{ \
	CAutoResize* ar=new CAutoResize(); \
	ar->setWnd(GetDlgItem(id));        \
	ar->init(GetDlgItem(id), parent);  \
	ar->setLeftResizeType(Anchor); \
	ar->setTopResizeType(Anchor);  \
	ar->setRightResizeType(Original);  \
	ar->setBottomResizeType(Original); \
	m_auto.push_back(ar); \
}

#define Init_AutoResize(id, parent, leftResizeType, topResizeType, rightResizeType, bottomResizeType) \
{ \
	CAutoResize* ar=new CAutoResize(); \
	ar->setWnd(GetDlgItem(id));        \
	ar->init(GetDlgItem(id), parent);  \
	ar->setLeftResizeType(leftResizeType); \
	ar->setTopResizeType(topResizeType);   \
	ar->setRightResizeType(rightResizeType);   \
	ar->setBottomResizeType(bottomResizeType); \
	m_auto.push_back(ar); \
}

#define Init_AutoResize_Fill(id, parent) \
{ \
	CAutoResize* ar=new CAutoResize();  \
	ar->setWnd(GetDlgItem(id));      \
	ar->initFill(GetDlgItem(id), parent);   \
	ar->setLeftResizeType(Anchor);   \
	ar->setTopResizeType(Anchor);    \
	ar->setRightResizeType(Anchor);  \
	ar->setBottomResizeType(Anchor); \
	ar->setLeftDistance(0);   \
	ar->setTopDistance(0);    \
	ar->setRightDistance(0);  \
	ar->setBottomDistance(0); \
	m_auto.push_back(ar);     \
}

#define Do_Resize(cx, cy) \
	m_auto.autoResize(cx, cy);

enum ResizeType
{
	Original,    // 保持原样
	Anchor,      // 边距固定
};

class CAutoResize
{
public:
	CAutoResize();
	CAutoResize(ResizeType leftResizeType, ResizeType topResizeType, ResizeType rightResizeType, ResizeType bottomResizeType);

	void init(CWnd* wnd, CWnd* parent, BOOL considerTitleHeight=TRUE);
	void init(RECT* rc, RECT* rcParent);
	void init(int leftDisatnce, int topDistance, int rightDistance, int bottomDistance, int width, int height);
	void initFill(CWnd* wnd, CWnd* parent, BOOL considerTitleHeight = TRUE);

	void autoResize(int cx, int cy);

	void setLeftDistance(int leftDistance) { m_leftDistance = leftDistance; }
	void setTopDistance(int topDistance) { m_topDistance = topDistance; }
	void setRightDistance(int rightDistance) { m_rightDistance = rightDistance; }
	void setBottomDistance(int bottomDistance) { m_bottomDistance = bottomDistance; }

	void setLeftResizeType(ResizeType leftResizeType) { m_leftResizeType = leftResizeType; }
	void setTopResizeType(ResizeType topResizeType) { m_topResizeType = topResizeType; }
	void setRightResizeType(ResizeType rightResizeType) { m_rightResizeType = rightResizeType; }
	void setBottomResizeType(ResizeType bottomResizeType) { m_bottomResizeType = bottomResizeType; }

	void setWnd(CWnd* wnd) { m_wnd = wnd; }

protected:
	BOOL checkWnd(CWnd* wnd);

private:
	CWnd* m_wnd;

	int m_leftDistance;  // 窗口在父窗口的左边距
	int m_topDistance;   // 窗口在父窗口的上边距
	int m_rightDistance; // 窗口在父窗口的右边距
	int m_bottomDistance;// 窗口在父窗口的下边距

	int m_width;    // 窗口宽度
	int m_height;   // 窗口高度

	ResizeType m_leftResizeType;
	ResizeType m_topResizeType;
	ResizeType m_rightResizeType;
	ResizeType m_bottomResizeType;
};

class CAutoResizeManager : public CPointerList<CAutoResize*>
{
public:
	CAutoResizeManager()
	{
		setSelfDestroy(TRUE);
	}

	void autoResize(int cx, int cy)
	{
		for (int i = 0; i < (int)size(); i++)
		{
			CAutoResize* ar = at(i);
			if (!ar)
				continue;

			ar->autoResize(cx, cy);
		}
	}

};