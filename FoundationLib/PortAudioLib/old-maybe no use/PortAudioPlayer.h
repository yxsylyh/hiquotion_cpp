#pragma once

#include <c++\3rdparty\portaudio\portaudio.h>
#include <c++\foudationlib\bufferlib\cycledbuffer.h>


#define DEFAULT_SAMPLE_RATE 8000
#define DEFAULT_FRAMES_PER_BUFFER  (4)

class CPortAudioPlayer
{
public:
	CPortAudioPlayer(void);
	~CPortAudioPlayer(void);

	PaDeviceIndex getDefaultOutputDevice();
	BOOL open(PaDeviceIndex index, int channelCount, PaSampleFormat sampleFormat=paInt16, double sampleRate=DEFAULT_SAMPLE_RATE, ULONG framesPerBuffer=DEFAULT_FRAMES_PER_BUFFER);
	BOOL close();
	BOOL start();
	BOOL stop();

	void addData(char *data, int dataLength);

	void initBuffer();

	long getDataLength();

	BOOL isInitialized() const { return m_isInitialized; }
	BOOL isOpen() const { return m_isOpen; }

	int getThreshold() const { return m_threshold; }
	void setThreshold(int val) { m_threshold = val; }

protected:
	int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags);

	static int paCallback( const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData );

	int getSizeOf(PaSampleFormat format);

protected:
	PaError err;
	BOOL m_isInitialized;
	BOOL m_isOpen;
	PaStream *stream;

	PaSampleFormat m_sampleFormat;
	ULONG m_framesPerBuffer;

	char *m_buffer;
	char m_abandonedBuffer[2048];

	BOOL m_isBufferComplete;

	CCycledBuffer m_cycledBuffer;

	int m_threshold;    // 最少 2 字节，否则程序会出错
	// 	RingBuff m_cycledBuffer;
};

