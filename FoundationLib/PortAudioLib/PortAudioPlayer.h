#pragma once

#include <C++\3rdParty\PortAudio\static\PortAudioCpp.hxx>
#include <c++\foudationlib\bufferlib\cycledbuffer.h>


#define DEFAULT_SAMPLE_RATE 8000
#define DEFAULT_FRAMES_PER_BUFFER  (64)

const int NUM_SECONDS = 5;
const double SAMPLE_RATE = 44100.0;
const int FRAMES_PER_BUFFER = 64;
const int TABLE_SIZE = 200;

class CPortAudioPlayer
{
public:
	CPortAudioPlayer(void);
	~CPortAudioPlayer(void);

	PaDeviceIndex getDefaultOutputDevice();
// 	BOOL open(PaDeviceIndex index, int channelCount, PaSampleFormat sampleFormat=paInt16, double sampleRate=DEFAULT_SAMPLE_RATE, ULONG framesPerBuffer=DEFAULT_FRAMES_PER_BUFFER);
	BOOL open(int channelCount=1, portaudio::SampleDataFormat sampleFormat=portaudio::INT16, double sampleRate=DEFAULT_SAMPLE_RATE, ULONG framesPerBuffer=DEFAULT_FRAMES_PER_BUFFER);
	BOOL close();
	BOOL start();
	BOOL stop();

	void addData(char *data, int dataLength);

	void initBuffer();

	long getDataLength();

	CString getErrMsg() const { return m_errMsg; }

protected:
	int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags);

// 	static int paCallback( const void *inputBuffer, void *outputBuffer,
// 		unsigned long framesPerBuffer,
// 		const PaStreamCallbackTimeInfo* timeInfo,
// 		PaStreamCallbackFlags statusFlags,
// 		void *userData );

	BOOL streamStop();

	int getSizeOf(portaudio::SampleDataFormat format);

protected:
	// Set up the System:
	portaudio::AutoSystem autoSys;
	portaudio::System &sys;

	// Create (and open) a new Stream, using the SineGenerator::generate function as a callback:
	portaudio::MemFunCallbackStream<CPortAudioPlayer> stream;

	CString m_errMsg;

// 	PaError err;
// 	BOOL m_isInitialized;
// 	BOOL m_isOpen;

	int m_channelCount;
	portaudio::SampleDataFormat m_sampleFormat;
	double m_sampleRate;
	ULONG m_framesPerBuffer;

// 	char *m_buffer;
// 	char m_abandonedBuffer[2048];

// 	BOOL m_isBufferComplete;

	CCycledBuffer m_cycledBuffer;

	BOOL m_isPlaying;
	BOOL m_isAudioPlayWhenDataAdding;

// 	int m_threshold;    // 最少 2 字节，否则程序会出错

};

