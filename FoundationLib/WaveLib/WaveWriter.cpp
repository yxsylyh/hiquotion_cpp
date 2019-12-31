#include "stdafx.h"
#include "WaveWriter.h"

CWaveWriter::CWaveWriter(void)
{
	m_isOpen=FALSE;
	m_dataLen=0;
}

CWaveWriter::~CWaveWriter(void)
{
	if(m_isOpen)
		closeFile();
}

BOOL CWaveWriter::createFile(CString path, PWAVEFORMATEX pWaveInfo)
{
	if(!m_file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
		return FALSE;

	m_isOpen=TRUE;

	char RIFF[4]={'R', 'I', 'F', 'F'};
	char WAVE[4]={'W', 'A', 'V', 'E'};
	char fmt[4]={'f', 'm', 't', ' '};
	char data[4]={'d', 'a', 't', 'a'};
	int len=0;
	m_file.Write(RIFF, 4);   // 多媒体文件标识
	len=CONTENT_LEN;
	m_file.Write(&len, 4);      // 整个数据长度，不包括RIFF表示和该4字节的长度本身，至少包括 36 字节的WAVE格式信息数据
	m_file.Write(WAVE, 4);   // WAVE 文件标识
	m_file.Write(fmt, 4);    // 子块1的id
	len=TRUNK1_LEN;
	m_file.Write(&len, 4);     // 本子块的大小
	m_file.Write(&pWaveInfo->wFormatTag, 2);   // 音频格式
	m_file.Write(&pWaveInfo->nChannels, 2);    // 声道数
	m_file.Write(&pWaveInfo->nSamplesPerSec, 4); // 采样率   22050
	m_file.Write(&pWaveInfo->nAvgBytesPerSec, 4); // 比特率，即每秒字节数，等于 SampleRate * numChannels * BitsPerSample / 8     44100
	m_file.Write(&pWaveInfo->nBlockAlign, 2);     // 对齐， 等于 NumChannels * BitsPerSample / 8 
	m_file.Write(&pWaveInfo->wBitsPerSample, 2);  // 采样位数
	len=0;
	m_file.Write(&len, 2);          // cbSize值(此处为0)
	m_file.Write(data, 4);   // 数据块标识
	len=0;
	m_file.Write(&len, 4);      // 数据长度，当前为0

	return TRUE;
}

void CWaveWriter::writeData(char *data, int dataLen)
{
	// 写入数据
	m_file.Write(data, dataLen);
	m_dataLen+=dataLen;

	// 写入数据区长度
	m_file.Seek(4, CFile::begin);
	int len=CONTENT_LEN+m_dataLen;
	m_file.Write(&len, 4); // 写入总长度（38 + 数据长度）
	m_file.Seek(DATA_LEN_POSITION, CFile::begin);
	m_file.Write(&m_dataLen, 4);    // 写入数据长度
	m_file.SeekToEnd();
}

void CWaveWriter::closeFile()
{
	if(m_isOpen)
		m_file.Close();
	m_isOpen=FALSE;
}
