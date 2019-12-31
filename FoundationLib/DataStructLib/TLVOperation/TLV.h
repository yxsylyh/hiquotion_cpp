// TLV.h: interface for the CTLV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLV_H__3B11192D_74BF_48F4_ABC1_B56FAB2B88B1__INCLUDED_)
#define AFX_TLV_H__3B11192D_74BF_48F4_ABC1_B56FAB2B88B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Tag Length Value 类
// 可以用两个方式使用其 Value
// 一种是将原数据复制到 m_valueNew 缓冲区
// 另一种是直接使用原数据的起始地址，即 m_value
// 通过 m_isUseValueNew 来判断使用哪种的数据
class CTLV  
{
public:
	CTLV(short tag, int length, char *value, BOOL isUseValueNew=FALSE);
	virtual ~CTLV();

	char getTag() const { return m_tag; }
	void setTag(char val) { m_tag = val; }

	int getLength() const { return m_length; }

	char * getValue();
	void setValue(char *val, int length, BOOL isUseValueNew);

protected:
	short m_tag;
	int m_length;
	char *m_value;
	char *m_valueNew;

	BOOL m_isUseValueNew;
};

#endif // !defined(AFX_TLV_H__3B11192D_74BF_48F4_ABC1_B56FAB2B88B1__INCLUDED_)
