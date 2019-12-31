#pragma once

#include <C++\3rdParty\PortAudio\static\PortAudioCpp.hxx>
#include <c++\foudationlib\bufferlib\cycledbuffer.h>

#define DEFAULT_SAMPLE_RATE 8000
#define DEFAULT_FRAMES_PER_BUFFER  (64)

class CPortAudioRecorder
{
public:
	CPortAudioRecorder(void);
	~CPortAudioRecorder(void);

	BOOL open(int channelCount=1, portaudio::SampleDataFormat sampleFormat=portaudio::INT16, double sampleRate=DEFAULT_SAMPLE_RATE, ULONG framesPerBuffer=DEFAULT_FRAMES_PER_BUFFER);
	BOOL close();
	BOOL start();
	BOOL stop();

	// 返回值表示buffer中数据的长度
	int getData(char *buffer, int bufferLen);

	CString getDefaultInputDevice() const { return m_defaultInputDevice; }

	CString getErrMsg() const { return m_errMsg; }

protected:
	int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags);

	int getSizeOf(portaudio::SampleDataFormat format);

protected:
	// Set up the System:
	portaudio::AutoSystem autoSys;
	portaudio::System &sys;

	// Create (and open) a new Stream, using the SineGenerator::generate function as a callback:
	portaudio::MemFunCallbackStream<CPortAudioRecorder> stream;

	CString m_errMsg;

	int m_channelCount;
	portaudio::SampleDataFormat m_sampleFormat;
	double m_sampleRate;
	ULONG m_framesPerBuffer;

	CCycledBuffer m_cycledBuffer;

	CString m_defaultInputDevice;
};
