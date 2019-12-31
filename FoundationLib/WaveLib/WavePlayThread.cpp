// WaveOperation.cpp: implementation of the CWaveOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavePlayThread.h"
#include <c++\foundationlib\SystemLib\SystemOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWavePlayThread::CWavePlayThread()
: m_result(NULL), m_isOpen(FALSE), m_isPlaying(FALSE), m_currentWaveHeaderIndex(0)
{
	ZeroMemory(m_waveHeader, sizeof(WAVEHDR) * Buffer_Count);
	ZeroMemory(m_buffer, Buffer_Length * Buffer_Count);
	m_cycledBuffer.redimLength(Max_Buffer_Length, FALSE);
}

CWavePlayThread::~CWavePlayThread()
{

}

// 初始化Wave格式
// 声道数、采样位数（8位、16位等等）、采样率
void CWavePlayThread::initWaveFormat(int channels, int bitPerSample, int samplePerSecond)
{
	memset(&m_waveFormat, 0, sizeof(m_waveFormat));
	m_waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	m_waveFormat.nChannels = (channels>0 ? channels : Default_Channels);
	m_waveFormat.wBitsPerSample = (bitPerSample>0 ? bitPerSample : Default_BitPerSample);
	m_waveFormat.cbSize = 0;
	m_waveFormat.nSamplesPerSec = (samplePerSecond>0 ? samplePerSecond : Default_SamplePerSecond);
	m_waveFormat.nAvgBytesPerSec = m_waveFormat.nChannels * m_waveFormat.nSamplesPerSec * m_waveFormat.wBitsPerSample / 8;
	m_waveFormat.nBlockAlign = (m_waveFormat.wBitsPerSample * m_waveFormat.nChannels) >> 3;  
}

void CWavePlayThread::initWaveFormat(WAVEFORMATEX waveFormat)
{
	memcpy(&m_waveFormat, &waveFormat, sizeof(m_waveFormat));
}

// 是否存在音频设备
// BOOL CWaveOperation::hasWaveDev()
// {
//     //lphWaveOut: PHWaveOut;   {用于返回设备句柄的指针; 如果 dwFlags=WAVE_FORMAT_QUERY, 这里应是 NULL}
//     //uDeviceID: UINT;         {设备ID; 可以指定为: WAVE_MAPPER, 这样函数会根据给定的波形格式选择合适的设备}
//     //lpFormat: PWaveFormatEx; {TWaveFormat 结构的指针; TWaveFormat 包含要申请的波形格式}
//     //dwCallback: DWORD        {回调函数地址或窗口句柄; 若不使用回调机制, 设为 NULL}
//     //dwInstance: DWORD        {给回调函数的实例数据; 不用于窗口}
//     //dwFlags: DWORD           {打开选项}// long120823
//     m_result = waveOutOpen(NULL,WAVE_MAPPER,&m_waveFormat,0,0,WAVE_FORMAT_QUERY);
//     if( m_result != MMSYSERR_NOERROR)
//         return FALSE;
// 	
// 	return TRUE;
// }

// 打开音频输出设备
BOOL CWavePlayThread::waveOutOpen()
{
// 	m_result = ::waveOutOpen( &m_hWaveOut, WAVE_MAPPER, &m_waveFormat, m_threadId, 0, CALLBACK_THREAD);
// 	m_result = ::waveOutOpen( &m_hWaveOut, WAVE_MAPPER, &m_waveFormat, NULL, NULL, NULL);
	m_result = ::waveOutOpen( &m_hWaveOut, WAVE_MAPPER, &m_waveFormat, m_threadId, NULL, CALLBACK_THREAD);
    if( m_result != MMSYSERR_NOERROR)
		return FALSE;
	
	m_isOpen=TRUE;
	m_currentWaveHeaderIndex=0;

	for(int i=0;i<Buffer_Count;i++)
	{
		MMRESULT mRet = waveOutPrepareHeader(m_hWaveOut,&m_waveHeader[i],sizeof(WAVEHDR));
	}

	return TRUE;
}

// 播放
BOOL CWavePlayThread::wavePlay(char* buf,unsigned int  nSize)
{
    if( !m_isOpen )
        return FALSE;

	if(m_isPlaying)
		return FALSE;

	if(!buf)
		return FALSE;

	if(nSize<=0)
		return FALSE;

    MMRESULT mRet;
//     char*   lpData = NULL;
    WAVEHDR* pWaveHead = &m_waveHeader[m_currentWaveHeaderIndex];
	
//     ZeroMemory(pWaveHead,sizeof(WAVEHDR));
	pWaveHead->dwBufferLength = min(Buffer_Length, nSize);
	pWaveHead->lpData = buf;
	pWaveHead->dwLoops=1;
	pWaveHead->dwFlags=0;
	pWaveHead->dwUser=0 ;
	pWaveHead->lpNext=NULL;
	pWaveHead->reserved=0;


//     lpData = new char[nSize];
	
//     memcpy(lpData,buf,nSize);
//     pWaveHead->lpData = lpData;
	
    mRet = waveOutPrepareHeader(m_hWaveOut,pWaveHead,sizeof(WAVEHDR));
    if( mRet != MMSYSERR_NOERROR )
	{
		m_isPlaying=FALSE;
        return FALSE;
	}

	m_currentWaveHeaderIndex++;
	if(m_currentWaveHeaderIndex<Buffer_Count)
		return FALSE;
	
	m_currentWaveHeaderIndex=0;
    mRet = waveOutWrite(m_hWaveOut,&m_waveHeader[0],sizeof(WAVEHDR));
    if( mRet != MMSYSERR_NOERROR )
	{
		m_isPlaying=FALSE;
		return FALSE;
	}

// 	while(waveOutUnprepareHeader(m_hWaveOut,pWaveHead,sizeof(WAVEHDR)) == WAVERR_STILLPLAYING)
// 	{
// 		Sleep(1);
// 		m_isPlaying=TRUE;
// 	}
// 
// 	CSystemOperation::DoEvents();
// 	CSystemOperation::DoEvents();

	m_isPlaying=TRUE;

    return TRUE;
}

// 关闭设备
void CWavePlayThread::waveOutClose()
{
	if (!m_isOpen)
        return;
	
    if(!m_hWaveOut)
        return;
	
    MMRESULT mRet =waveOutReset(m_hWaveOut);
	if(mRet != MMSYSERR_NOERROR)
		return;

	mRet = ::waveOutClose(m_hWaveOut);
    if(mRet != MMSYSERR_NOERROR)
        return;
	
    m_hWaveOut = NULL;
    m_isOpen = FALSE;

}

// 设置和获取音频音量
DWORD CWavePlayThread::getWaveVolume()
{
	if(m_result)
		return -1;
	
	DWORD volValue=0;
	waveOutGetVolume(m_hWaveOut, &volValue);
	return volValue;
}

void CWavePlayThread::setWaveVolume(DWORD volValue)
{
	if(m_result)
		return;

	waveOutSetVolume(m_hWaveOut, volValue);
}

void CWavePlayThread::setBufferSize(int size)
{
	if(size<=Max_Buffer_Length)
		return;

	m_cycledBuffer.redimLength(size);
}

BOOL CWavePlayThread::addData(char *data, int length)
{
	if(!data)
		return FALSE;

	if(length<=0)
		return FALSE;

	return m_cycledBuffer.write(data, length);
}

UINT CWavePlayThread::threadRun()
{
    MSG msg;
    while(1)
    {
		Sleep(1);

		if(!GetMessage(&msg,0,0,0))
		{
			if(m_status!=Running)
			{
				m_isPlaying=FALSE;
				break;
			}
			continue;
		}

		if(m_status!=Running)
		{
			m_isPlaying=FALSE;
			break;
		}

        switch(msg.message )
        {
        case WOM_OPEN:  // waveform output message
            break;
        case WOM_CLOSE:
            break;
        case WOM_DONE:  // same value of MM_WOM_DONE:

            WAVEHDR *pWaveHead = (WAVEHDR*)msg.lParam;
//			waveOutUnprepareHeader((HWAVEOUT)msg.wParam,pWaveHead,sizeof(WAVEHDR));
// 			waveOutUnprepareHeader((HWAVEOUT)msg.wParam,&m_waveHeader,sizeof(WAVEHDR));

			waveOutUnprepareHeader(m_hWaveOut, pWaveHead, sizeof(WAVEHDR));

			int length = min(Buffer_Length, m_cycledBuffer.getDataLength() / m_waveFormat.nBlockAlign * m_waveFormat.nBlockAlign);

			if(length<=0)
			{
				m_isPlaying=FALSE;
				break;
			}


			m_cycledBuffer.read(m_bufferPlaying, length);

// 			int reducedLength=length/20*2;

// 			wavePlay(m_buffer+reducedLength, length-reducedLength);
// 			wavePlay(m_bufferPlaying, length);

			memcpy(m_buffer[m_currentWaveHeaderIndex], m_bufferPlaying, length);
			pWaveHead->dwBufferLength=length;
			pWaveHead->lpData=m_buffer[m_currentWaveHeaderIndex];
			m_currentWaveHeaderIndex=(m_currentWaveHeaderIndex+1) % Buffer_Count;

			MMRESULT mRet = waveOutPrepareHeader(m_hWaveOut,pWaveHead,sizeof(WAVEHDR));
			if( mRet != MMSYSERR_NOERROR )
			{
				m_isPlaying=FALSE;
				return FALSE;
			}

			mRet = waveOutWrite(m_hWaveOut,pWaveHead,sizeof(WAVEHDR));
			if( mRet != MMSYSERR_NOERROR )
			{
				m_isPlaying=FALSE;
				return FALSE;
			}


// 			WavePlayDone.SetEvent();
//             delete []pWaveHead->lpData;
//             delete pWaveHead;
            break;
        }

		if(m_status!=Running)
		{
			m_isPlaying=FALSE;
			break;
		}
    }

	m_isPlaying=FALSE;
    return msg.wParam;
// 
// 	while(m_cycledBuffer->read(m_buffer, Max_Buffer_Length))
// 	{
// 		wavePlay(m_buffer, Max_Buffer_Length);
// 	}
}
// 
// void CWavePlayThread::play()
// {
// 	waveOutUnprepareHeader(m_hWaveOut, &m_waveHeader, sizeof(WAVEHDR));
// 
// 	int length = min(Max_Buffer_Length, m_cycledBuffer.getDataLength() / m_waveFormat.nBlockAlign * m_waveFormat.nBlockAlign);
// 
// 	if(length<=0)
// 	{
// 		m_isPlaying=FALSE;
// 		return;
// 	}
// 
// 	m_cycledBuffer.read(m_buffer, length);
// 
// 	wavePlay(m_buffer, length);
// 
// // 	for (int i=0; i<Max_Buffer_Length; i++)
// // 	{
// // 		m_soundBuf[m_bufIndex][i] = m_buffer[ int(i * fRate) ];
// // 	}
// // 	if (length < int(2 * Max_Buffer_Length * fRate + 0.5)) 
// // 	{
// // 		memset(&m_soundBuf[m_bufIndex][length / 2 - 1], 
// // 			0, 
// // 			2 * Max_Buffer_Length - length
// // 			);
// // 		//		TRACE("!!数据不足\n");
// // 	}
// // 
// // 	::PostMessage(CGlobalVar::m_hShowWavWnd, WM_ADD_DATA_SHOW, (WPARAM)m_soundBuf[m_bufIndex], SOUND_BUF_LEN);
// // 
// // 	m_waveHdrs[m_bufIndex].dwBufferLength = SOUND_BUF_LEN * sizeof(short);
// // 	m_waveHdrs[m_bufIndex].dwFlags = 0;
// // 	waveOutPrepareHeader(m_hWaveOut, &m_waveHdrs[m_bufIndex], sizeof(WAVEHDR));
// // 
// // 	// 播放一块声音数据
// // 	waveOutWrite(m_hWaveOut, &m_waveHdrs[m_bufIndex], sizeof(WAVEHDR));
// // 
// // 	m_bufIndex ++;
// // 	if (m_bufIndex >= SOUND_BUF_NUM) 
// // 	{
// // 		m_bufIndex = 0;
// // 	}
// }