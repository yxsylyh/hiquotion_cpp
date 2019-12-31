// Handle.h: interface for the CHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANDLE_H__1024BD7F_9DA1_4809_9368_4FFA033AC574__INCLUDED_)
#define AFX_HANDLE_H__1024BD7F_9DA1_4809_9368_4FFA033AC574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
// 选择框中的可以操作的矩形（句柄）

#define Default_Handle_Sizex 8
#define Default_Handle_Sizey 8

class CHandle  
{
public:
	CHandle(POINT handlePosition, BOOL bHandleEnabled=TRUE);
	CHandle(int handlePositionX, int handlePositionY, BOOL bHandleEnabled=TRUE);
	virtual ~CHandle();

	// 属性
	BOOL isHandleEnabled();    // 这个句柄是不是可以操作的
	SIZE getHandleSize();      // 获取句柄的尺寸
	POINT getHandlPosition();  // 获取句柄的位置
	void setHandlePosition(int x, int y); // 设置句柄的位置
	void setHandleSize(SIZE handleSize);  // 设置句柄大小，默认不需要设置
	CRect getHandleRect();     // 获取句柄所在的Rect

	// 方法
	void drawHandle(CDC *DC);

protected:
	BOOL m_bHandleEnabled;
	POINT m_handlePosition;
	SIZE m_handleSize;

};

#endif // !defined(AFX_HANDLE_H__1024BD7F_9DA1_4809_9368_4FFA033AC574__INCLUDED_)
