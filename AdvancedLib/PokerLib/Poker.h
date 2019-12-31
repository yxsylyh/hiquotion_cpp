// Poker.h: interface for the CPoker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKER_H__2BE0A91D_CD35_4F49_A898_00CAE78AD3DA__INCLUDED_)
#define AFX_POKER_H__2BE0A91D_CD35_4F49_A898_00CAE78AD3DA__INCLUDED_

#include <C++\FoudationLib\UIHandlerLib\IUIHandler.h>
#include <C++\FoudationLib\DrawingLib\Picture.h>
#include <string>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 图形位置定义

// 1）默认纸牌宽高
#define DEFAULT_POKER_WIDTH   450
#define DEFAULT_POKER_HEIGHT  685

// 2）默认大花色宽高
#define DEFAULT_POKER_LARGE_TYPE_WIDTH 90
#define DEFAULT_POKER_LARGE_TYPE_HEIGHT 110

// 3）默认小花色宽高
#define DEFAULT_POKER_SMALL_TYPE_WIDTH DEFAULT_POKER_LARGE_TYPE_WIDTH/2
#define DEFAULT_POKER_SMALL_TYPE_HEIGHT DEFAULT_POKER_LARGE_TYPE_HEIGHT/2

// 默认小花色坐标
// 左上角20,130
#define Default_Poker_Small_Type_LeftTop_X 20
#define Default_Poker_Small_Type_LeftTop_Y 130

// 右下角380,505
#define Default_Poker_Small_Type_RightBottom_X 380
#define Default_Poker_Small_Type_RightBottom_Y 505

// 4）默认牌面值宽高
#define DEFAULT_POKER_VALUE_WIDTH 50
#define DEFAULT_POKER_VALUE_HEIGHT 80

// 默认牌面值左上角坐标
#define Default_Value_LeftTop_X 15
#define Default_Value_LeftTop_Y 35

// 默认牌面值右下角坐标
#define Default_Value_RightBottom_X 380
#define Default_Value_RightBottom_Y 575

// 默认 JKQ 图案左上角坐标
#define JKQ_X 73
#define JKQ_Y 63

// 默认 JKQ 图案宽高
#define JKQ_Width 300
#define JKQ_Height 565

int GetZoomedValue(int a, int len, int defaultLen);
// {
// 	if(len==defaultLen)
// 		return a;
// 	else
// 		return a*len/defaultLen;
// }

#define GetZoomedX2(x, width) GetZoomedValue(x, width, DEFAULT_POKER_WIDTH)
#define GetZoomedY2(y, height) GetZoomedValue(y, height, DEFAULT_POKER_HEIGHT)

#define GetZoomedX(x) GetZoomedX2(x, m_rect.Width())
#define GetZoomedY(y) GetZoomedY2(y, m_rect.Height())

// 纸牌的实际宽高
static int pokerWidth=DEFAULT_POKER_WIDTH;
static int pokerHeight=DEFAULT_POKER_HEIGHT;

int getPokerWidth();
void setPokerWidth(int width);
int getPokerHeight();
void setPokerHeight(int height);

// 7、数据结构定义

// 位置数据定义

// 花色位置图数据（见 .cpp）

// 花色位置坐标在花色位置图中的索引
// 二维数组中，第一维表示牌面值，第二维表示花色位置图中的索引数组（数组元素个数与牌面值一致）
// （见 .cpp）

// 逻辑数据定义

// 1）花色

enum PokerType
{
	Black,  // 黑桃
	Red,    // 红桃
	Flower, // 草花
	Diamond, // 方片
//	Joker,  // 王
};

// 2）牌面值

enum PokerValue
{
	PVAce,//=1,
	PV2,
	PV3,
	PV4,
	PV5,
	PV6,
	PV7,
	PV8,
	PV9,
	PV10,
	PVJack,
	PVQueen,
	PVKing,

// 	// 王
// 	PVMinorJoker=100,
// 	PVMajorJoker=101,
};

// 3）一张扑克牌

struct Poker
{
	PokerType type;
	PokerValue value;
};

// 4）一副扑克

// struct PokerSet
// {
// 	Poker poker[54];
// };

static CPicture m_background;     // 牌正面底图
static CPicture m_offBackground;  // 牌背面底图
static CPicture m_type[4];        // 花色图
static CPicture m_typeRotated[4]; // 倒转的花色图
static CPicture m_value[2][13];         // 牌面值
static CPicture m_valueRotated[2][13];  // 倒转的牌面值
static CPicture m_people[4][3];         // 牌面值人物（J，Q，K）二维数组，第一维表示四种花色，第二维表示J、Q或K
	
// 设置牌正面背景图和背面背景图
void setBackgroundResource(DWORD res, DWORD imgExtType);
void setBackgroundPicture(std::string path, DWORD imageType=0);
void setOffBackgroundRecource(DWORD res, DWORD imgExtType);
void setOffBackgroundPicture(std::string path, DWORD imageType=0);

// 设置花色、牌面值以及JKQ的资源号或图片路径
void setTypeResource(PokerType type, DWORD res, DWORD imgExtType);
void setTypePath(PokerType type, std::string path, DWORD imageType=0);

void setValueResource(PokerType type, PokerValue v, DWORD res, DWORD imgExtType);
void setValuePath(PokerType type, PokerValue v, std::string path, DWORD imageType=0);

void setJResource(PokerType type, DWORD res, DWORD imgExtType);
void setJPath(PokerType type, std::string path, DWORD imageType=0);

void setKResource(PokerType type, DWORD res, DWORD imgExtType);
void setKPath(PokerType type, std::string path, DWORD imageType=0);

void setQResource(PokerType type, DWORD res, DWORD imgExtType);
void setQPath(PokerType type, std::string path, DWORD imageType=0);

// 5）带界面可交互的一张牌
class CPoker : public IUIHandler  
{
public:
	CPoker();
	CPoker(PokerType pokerType, PokerValue pokerValue);
	virtual ~CPoker();

	static int getWidth() { return getPokerWidth(); }
	static void setWidth(int width) { setPokerWidth(width); }
	static int getHeight() { return getPokerHeight(); }
	static void setHeight(int height) { setPokerHeight(height); }

	Poker getPoker() const { return m_poker; }
	void setPoker(Poker val) { m_poker = val; }
	void setPoker(PokerType pokerType, PokerValue pokerValue)
	{
		m_poker.type=pokerType;
		m_poker.value=pokerValue;
	}

	PokerType getPokerType() const { return m_poker.type; }
	void setPokerType(PokerType val) { m_poker.type=val; }

	PokerValue getPokerValue() const {return m_poker.value; }
	void setPokerValue(PokerValue val) { m_poker.value=val; }

	BOOL getOff() const { return m_isOff; }
	void setOff(BOOL val);

	int getAbsoluteX() const { return m_absoluteX; }
	int getAbsoluteY() const { return m_absoluteY; }

protected:
	void init();
	virtual void drawMe(CDC *pDC, CPoint point);

	// 继承
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnMouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint);
	virtual void OnSize(int cx, int cy);

protected:
	Poker m_poker;
	BOOL m_isOff;          // 牌是否是扣着的（决定显示哪些图形）

	// 距离整个界面绘图区左上角的x y坐标
	int m_absoluteX;
	int m_absoluteY;
};

#endif // !defined(AFX_POKER_H__2BE0A91D_CD35_4F49_A898_00CAE78AD3DA__INCLUDED_)
