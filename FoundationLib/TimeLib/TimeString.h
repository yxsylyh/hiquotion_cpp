#pragma once

class CTimeString
{
public:
	CTimeString(void);
	~CTimeString(void);

	static CString getCurrentDateTimeString(int type=0);
};
