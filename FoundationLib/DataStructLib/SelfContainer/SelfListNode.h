// SelfListNode.h: interface for the CSelfListNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELFLISTNODE_H__7E0E98B7_30B6_4529_BBA5_49F6CC7C51B8__INCLUDED_)
#define AFX_SELFLISTNODE_H__7E0E98B7_30B6_4529_BBA5_49F6CC7C51B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T>
class CSelfListNode  
{
public:
	CSelfListNode()
	{
		m_t=NULL;
	};

	CSelfListNode(T t)
	{
		m_t=t;
	}

	virtual ~CSelfListNode(){};

	// 获取末端结点
	T getEnding()
	{
		if(!m_t)
			return this;

		return m_t.getEnding();
	}

	T getT() const { return m_t; }
	void setT(T val) { m_t = val; }

protected:
	T m_t;
};

#endif // !defined(AFX_SELFLISTNODE_H__7E0E98B7_30B6_4529_BBA5_49F6CC7C51B8__INCLUDED_)
