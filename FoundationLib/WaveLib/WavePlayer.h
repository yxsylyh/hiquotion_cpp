// WaveOperation.h: interface for the CWaveOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEOPERATION_H__76DAED93_153A_4D2D_803E_4E26A4242AE3__INCLUDED_)
#define AFX_WAVEOPERATION_H__76DAED93_153A_4D2D_803E_4E26A4242AE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <c++\foundationlib\MultiThreadLib\ThreadBase.h>
#include <mmsystem.h>
#include <mmreg.h>
// #include <afxmt.h>
#include <c++\foundationlib\bufferlib\cycledbuffer.h>

#pragma  comment(lib, "winmm.lib")

#define Default_Channels 1
#define Default_BitPerSample 16
#define Default_SamplePerSecond 8000

#define Buffer_Count 8
#define Buffer_Length 1024
#define Max_Buffer_Length 10240  // 10KB（弄1MB会使程序崩溃～～～），请使用 m_waveFormat.nBlockAlign 的整数倍，否则第二次播放声音时可能会导致声音播放不出来

// #define Data_Length 4000

class CWavePlayer //: public CThreadBase
{
public:
	CWavePlayer();
	virtual ~CWavePlayer();

	// 初始化Wave格式
	// 声道数、采样位数（8位、16位等等）、采样率
	void initWaveFormat(int channels, int bitPerSample, int samplePerSecond);
	void initWaveFormat(WAVEFORMATEX waveFormat);

// 	// 是否存在音频设备
// 	BOOL hasWaveDev();

	// 打开音频输出设备
	BOOL waveOutOpen();

	// 播放
	BOOL CWavePlayer::wavePlay(char* buf, unsigned int nSize);

	// 是否正在播放
	BOOL isPlaying() const { return m_isPlaying; }

	// 关闭设备
	void waveOutClose();

	// 设置和获取音频音量
	DWORD getWaveVolume();
	void setWaveVolume(DWORD volValue);

// 	void setCycledBuffer(CCycledBuffer * val) { m_cycledBuffer = val; }

// 	CEvent WavePlayDone;

	void setBufferSize(int size);
	BOOL addData(char *data, int length);

protected:
// 	UINT threadRun();

// 	void play();

	afx_msg void OnBlockDone(WPARAM wParam, LPARAM lParam);
	afx_msg void OnQuitThread(WPARAM wParam, LPARAM lParam);

// 	DECLARE_MESSAGE_MAP()

private:
	WAVEFORMATEX m_waveFormat;

	HWAVEOUT m_hWaveOut;
	MMRESULT m_result;

	WAVEHDR m_waveHeader[Buffer_Count];
	int m_currentWaveHeaderIndex;

	BOOL m_isOpen;

	BOOL m_isPlaying;

	CCycledBuffer m_cycledBuffer;
	char m_buffer[Buffer_Count][Buffer_Length];
	char m_bufferPlaying[Max_Buffer_Length];
};

#endif // !defined(AFX_WAVEOPERATION_H__76DAED93_153A_4D2D_803E_4E26A4242AE3__INCLUDED_)
