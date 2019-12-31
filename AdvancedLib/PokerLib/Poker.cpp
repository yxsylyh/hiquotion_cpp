// Poker.cpp: implementation of the CPoker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Poker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// 花色位置图数据
int DefaultTypePosition[17][2]={
	{75,75},	{175,75},	{275,75},
				{175,155},
				{175,185},
	{75,215},				{275,215},
	{75,287},	{175,287},	{275,287},
	{75,360},				{275,360},
				{175,390},
				{175,420},
	{75,500},	{175,500},	{275,500}
};

// 花色位置坐标在花色位置图中的索引
// 二维数组中，第一维表示牌面值，第二维表示花色位置图中的索引数组（数组元素个数与牌面值一致）
int TypePositionIndex[10][10]={
	{8},										// 1
	{1,15},										// 2
	{1,8,15},									// 3
	{0,2,14,16},								// 4
	{0,2,8,14,16},								// 5
	{0,2,7,9,14,16},							// 6
	{0,2,4,7,9,14,16},							// 7
	{0,2,4,7,9,12,14,16},						// 8
	{0,2,5,6,8,10,11,14,16},					// 9
	{0,2,3,5,6,10,11,13,14,16}					// 10
};

// 花色正向的个数
int TypePositiveCount[10]={1, 1, 2, 2, 3, 4, 5, 5, 5, 5};

int GetZoomedValue(int a, int len, int defaultLen)
{
	if(len==defaultLen)
		return a;
	else
		return a*len/defaultLen;
}

int getPokerWidth()
{
	return pokerWidth;
}

void setPokerWidth(int width)
{
	pokerWidth=width;
}

int getPokerHeight()
{
	return pokerHeight;
}

void setPokerHeight(int height)
{
	pokerHeight=height;
}

// 设置牌正面背景图和背面背景图
void setBackgroundResource(DWORD res, DWORD imgExtType)
{
	m_background.setResource(res, imgExtType);
}

void setBackgroundPicture(std::string path, DWORD imageType)
{
	m_background.setPath(path, imageType);
}

void setOffBackgroundRecource(DWORD res, DWORD imgExtType)
{
	m_offBackground.setResource(res, imgExtType);
}

void setOffBackgroundPicture(std::string path, DWORD imageType)
{
	m_offBackground.setPath(path, imageType);
}

// 设置花色、牌面值以及JKQ的资源号或图片路径
void setTypeResource(PokerType type, DWORD res, DWORD imgExtType)
{
	m_type[type].setResource(res, imgExtType);

	m_typeRotated[type].setResource(res, imgExtType);
	m_typeRotated[type].rotate180();
}

void setTypePath(PokerType type, std::string path, DWORD imageType)
{
	m_type[type].setPath(path, imageType);
	
	m_typeRotated[type].setPath(path, imageType);
	m_typeRotated[type].rotate180();
}

void setValueResource(PokerType type, PokerValue v, DWORD res, DWORD imgExtType)
{
	m_value[type % 2][v].setResource(res, imgExtType);

	m_valueRotated[type % 2][v].setResource(res, imgExtType);
	m_valueRotated[type % 2][v].rotate180();
}

void setValuePath(PokerType type, PokerValue v, std::string path, DWORD imageType)
{
	m_value[type % 2][v].setPath(path, imageType);
	
	m_valueRotated[type % 2][v].setPath(path, imageType);
	m_valueRotated[type % 2][v].rotate180();
}

void setJResource(PokerType type, DWORD res, DWORD imgExtType)
{
	m_people[type][0].setResource(res, imgExtType);
}

void setJPath(PokerType type, std::string path, DWORD imageType)
{
	m_people[type][0].setPath(path, imageType);
}

void setKResource(PokerType type, DWORD res, DWORD imgExtType)
{
	m_people[type][2].setResource(res, imgExtType);
}

void setKPath(PokerType type, std::string path, DWORD imageType)
{
	m_people[type][2].setPath(path, imageType);
}

void setQResource(PokerType type, DWORD res, DWORD imgExtType)
{
	m_people[type][1].setResource(res, imgExtType);
}

void setQPath(PokerType type, std::string path, DWORD imageType)
{
	m_people[type][1].setPath(path, imageType);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoker::CPoker()
: m_isOff(FALSE), m_absoluteX(0), m_absoluteY(0)
{
	m_poker.type=Black;
	m_poker.value=PVAce;

	init();
}

CPoker::CPoker(PokerType pokerType, PokerValue pokerValue)
{
	setPoker(pokerType, pokerValue);

	init();
}

CPoker::~CPoker()
{

}

void CPoker::init()
{
	setBackColor(RGB(255, 255, 255));
	setFillStyle(0);
	setBorderStyle(BS_SOLID);
	setBorderWidth(2);

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i % 2 ==0)
				m_people[i][j].setBorderColor(RGB(0,0,0));
			else
				m_people[i][j].setBorderColor(RGB(200,0,0));
			
			m_people[i][j].setBorderStyle(BS_SOLID);
			m_people[i][j].setBorderWidth(1);
		}
	}
}

void CPoker::setOff(BOOL val)
{
	m_isOff = val;
	if(m_isOff)
	{
		setBackColor(RGB(120, 120, 120));
		setFillStyle(7);
	}
	else
	{
		setBackColor(RGB(255, 255, 255));
		setFillStyle(0);
	}
}

void CPoker::drawMe(CDC *pDC, CPoint point)
{
	CContainer::drawMe(pDC, point);

	m_absoluteX=point.x;
	m_absoluteY=point.y;

	CPoint p=m_rect.TopLeft();
	p.Offset(point);

	if(m_isOff)
	{
		m_offBackground.setRect(0, 0, GetZoomedX(DEFAULT_POKER_WIDTH), GetZoomedY(DEFAULT_POKER_HEIGHT));
		m_offBackground.draw(pDC, p);
		return;
	}

	m_background.setRect(0, 0, GetZoomedX(DEFAULT_POKER_WIDTH), GetZoomedY(DEFAULT_POKER_HEIGHT));
	m_background.draw(pDC, p);

	int index=m_poker.value;

	// 牌面值正向
	m_value[m_poker.type % 2][index].setRect(GetZoomedX(Default_Value_LeftTop_X), GetZoomedY(Default_Value_LeftTop_Y), GetZoomedX(Default_Value_LeftTop_X+DEFAULT_POKER_VALUE_WIDTH), GetZoomedY(Default_Value_LeftTop_Y+DEFAULT_POKER_VALUE_HEIGHT));
	m_value[m_poker.type % 2][index].draw(pDC, p);

	// 小花色正向
	m_type[m_poker.type].setRect(GetZoomedX(Default_Poker_Small_Type_LeftTop_X), GetZoomedY(Default_Poker_Small_Type_LeftTop_Y), GetZoomedX(Default_Poker_Small_Type_LeftTop_X+DEFAULT_POKER_SMALL_TYPE_WIDTH), GetZoomedY(Default_Poker_Small_Type_LeftTop_Y+DEFAULT_POKER_SMALL_TYPE_HEIGHT));
	m_type[m_poker.type].draw(pDC, p);

	if(m_poker.value<10)
	{
		int i=0;

		// 大花色正向
		for(i=0;i<TypePositiveCount[index];i++)
		{
			int x=DefaultTypePosition[TypePositionIndex[index][i]][0];
			int y=DefaultTypePosition[TypePositionIndex[index][i]][1];

			m_type[m_poker.type].setRect(GetZoomedX(x), GetZoomedY(y), GetZoomedX(x+DEFAULT_POKER_LARGE_TYPE_WIDTH), GetZoomedY(y+DEFAULT_POKER_LARGE_TYPE_HEIGHT));
			m_type[m_poker.type].draw(pDC, p);
		}

		// 大花色反向
		for(i=TypePositiveCount[index];i<=index;i++)
		{
			int x=DefaultTypePosition[TypePositionIndex[index][i]][0];
			int y=DefaultTypePosition[TypePositionIndex[index][i]][1];
			
			m_typeRotated[m_poker.type].setRect(GetZoomedX(x), GetZoomedY(y), GetZoomedX(x+DEFAULT_POKER_LARGE_TYPE_WIDTH), GetZoomedY(y+DEFAULT_POKER_LARGE_TYPE_HEIGHT));
			m_typeRotated[m_poker.type].draw(pDC, p);
		}
	}
	else
	{
		// 绘制 JQK 人物
		m_people[m_poker.type][m_poker.value-10].setRect(GetZoomedX(JKQ_X), GetZoomedY(JKQ_Y), GetZoomedX(JKQ_X+JKQ_Width), GetZoomedY(JKQ_Y+JKQ_Height));
		m_people[m_poker.type][m_poker.value-10].draw(pDC, p);
	}

	// 牌面值反向
	m_valueRotated[m_poker.type % 2][index].setRect(GetZoomedX(Default_Value_RightBottom_X), GetZoomedY(Default_Value_RightBottom_Y), GetZoomedX(Default_Value_RightBottom_X+DEFAULT_POKER_VALUE_WIDTH), GetZoomedY(Default_Value_RightBottom_Y+DEFAULT_POKER_VALUE_HEIGHT));
	m_valueRotated[m_poker.type % 2][index].draw(pDC, p);

	// 小花色反向
	m_typeRotated[m_poker.type].setRect(GetZoomedX(Default_Poker_Small_Type_RightBottom_X), GetZoomedY(Default_Poker_Small_Type_RightBottom_Y), GetZoomedX(Default_Poker_Small_Type_RightBottom_X+DEFAULT_POKER_SMALL_TYPE_WIDTH), GetZoomedY(Default_Poker_Small_Type_RightBottom_Y+DEFAULT_POKER_SMALL_TYPE_HEIGHT));
	m_typeRotated[m_poker.type].draw(pDC, p);
}

void CPoker::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 如果点击在牌上，牌是扣着的，并且牌下面没有牌了，则该牌可以反转过来
	if(m_rect.PtInRect(point) && m_isOff && CTreeNode<IUIHandler *>::count()<=0)
	{
		setOff(FALSE);
		if(m_wndForRefresh)
			m_wndForRefresh->Invalidate();
	}

	IUIHandler::OnLButtonDown(nFlags, point);
}

void CPoker::OnMouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint)
{
	// 如果牌是扣着的，并且牌下面还有牌，则返回（即不允许移动）
	if(m_isOff && CTreeNode<IUIHandler *>::count()>0)
		return;

	IUIHandler::OnMouseDrag(nFlags, currPoint, origPoint);
}

void CPoker::OnSize(int cx, int cy)
{
	setPokerWidth(cx);
	setPokerHeight(cy);
}
