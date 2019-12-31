#pragma once

#include <mmsystem.h>

#define CONTENT_LEN 38
#define TRUNK1_LEN 18
#define DATA_LEN_POSITION CONTENT_LEN+4

class CWaveWriter
{
public:
	CWaveWriter(void);
	~CWaveWriter(void);

	BOOL createFile(CString path, PWAVEFORMATEX pWaveInfo);
	void writeData(char *data, int dataLen);
	void closeFile();

private:
	CFile m_file;

	int m_dataLen;
	BOOL m_isOpen;
};
