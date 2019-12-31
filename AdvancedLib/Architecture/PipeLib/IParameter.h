// IParameter.h: interface for the IParameter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPARAMETER_H__2D1008FC_5BCF_48F2_AC67_C42872C7B092__INCLUDED_)
#define AFX_IPARAMETER_H__2D1008FC_5BCF_48F2_AC67_C42872C7B092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IParameter  
{
public:
	IParameter();
	virtual ~IParameter();

	BOOL isDestroy(){return m_isDestroy;};
	
	void setDestroy(BOOL val){m_isDestroy=val;};
	
private:
	BOOL m_isDestroy;
};

#endif // !defined(AFX_IPARAMETER_H__2D1008FC_5BCF_48F2_AC67_C42872C7B092__INCLUDED_)
