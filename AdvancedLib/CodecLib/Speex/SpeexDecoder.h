#pragma once

#include <C++\3rdParty\Speex\speex.h>

#define FRAME_SIZE 160

class CSpeexDecoder
{
public:
	CSpeexDecoder(void);
	~CSpeexDecoder(void);

	BOOL init(int quality=1);
	BOOL decode(char *src, int srcLen, float *dst, int *dstLen);
	void destroy();

	CString getErrMsg() const { return m_errMsg; }

private:
	SpeexBits bits;
	void *state;

	CString m_errMsg;
};
