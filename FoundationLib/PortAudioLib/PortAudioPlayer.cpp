#include "StdAfx.h"
#include "PortAudioPlayer.h"

CPortAudioPlayer::CPortAudioPlayer(void)
: m_isAudioPlayWhenDataAdding(TRUE), m_sampleFormat(portaudio::INT16), m_framesPerBuffer(DEFAULT_FRAMES_PER_BUFFER), m_isPlaying(FALSE), m_cycledBuffer(102400000),
  sys(portaudio::System::instance())
{
}

CPortAudioPlayer::~CPortAudioPlayer(void)
{
}

PaDeviceIndex CPortAudioPlayer::getDefaultOutputDevice()
{
	return Pa_GetDefaultOutputDevice();
}

long CPortAudioPlayer::getDataLength()
{
	return m_cycledBuffer.getDataLength();
}


// BOOL CPortAudioPlayer::open(PaDeviceIndex index, int channelCount, PaSampleFormat sampleFormat, double sampleRate, ULONG framesPerBuffer)
BOOL CPortAudioPlayer::open(int channelCount, portaudio::SampleDataFormat sampleFormat, double sampleRate, ULONG framesPerBuffer)
{
	// Set up the parameters required to open a (Callback)Stream:
// 	portaudio::DirectionSpecificStreamParameters outParams(sys.defaultOutputDevice(), 2, portaudio::FLOAT32, false, sys.defaultOutputDevice().defaultLowOutputLatency(), NULL);
	portaudio::DirectionSpecificStreamParameters outParams(sys.defaultOutputDevice(), channelCount, sampleFormat, false, sys.defaultOutputDevice().defaultLowOutputLatency(), NULL);
// 	portaudio::StreamParameters params(portaudio::DirectionSpecificStreamParameters::null(), outParams, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff);
	portaudio::StreamParameters params(portaudio::DirectionSpecificStreamParameters::null(), outParams, sampleRate, framesPerBuffer, paClipOff);

	try
	{
		stream.open(params, *this, &CPortAudioPlayer::paCallbackMethod);
	}
	catch(portaudio::PaException &e)
	{
		m_errMsg=e.paErrorText();
		return FALSE;
	}

	m_channelCount=channelCount;
	m_sampleFormat=sampleFormat;
	m_sampleRate=sampleRate;
	m_framesPerBuffer=framesPerBuffer;

	return TRUE;
}

BOOL CPortAudioPlayer::close()
{
	try
	{
		stream.close();
	}
	catch(portaudio::PaException &e)
	{
		m_errMsg=e.paErrorText();
		return FALSE;
	}

	return TRUE;
}


BOOL CPortAudioPlayer::start()
{
	try
	{
		stream.start();
	}
	catch(portaudio::PaException &e)
	{
		m_errMsg=e.paErrorText();
		return FALSE;
	}

	m_isPlaying=TRUE;

	return TRUE;
}

BOOL CPortAudioPlayer::streamStop()
{
	try
	{
		stream.stop();
	}
	catch(portaudio::PaException &e)
	{
		m_errMsg=e.paErrorText();
		return FALSE;
	}

	return TRUE;
}

BOOL CPortAudioPlayer::stop()
{
	BOOL ret=streamStop();

	m_isPlaying=FALSE;

	return ret;
}

/* The instance callback, where we have access to every method/variable in object of class Sine */
int CPortAudioPlayer::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags)
{
	(void) timeInfo; /* Prevent unused variable warnings. */
	(void) statusFlags;
	(void) inputBuffer;

	int length=min(m_framesPerBuffer * getSizeOf(m_sampleFormat) * m_channelCount, m_cycledBuffer.getDataLength());
	if(length<=0)
	{
		streamStop();
	}
	else
	{
		length=length/getSizeOf(m_sampleFormat)/m_channelCount*getSizeOf(m_sampleFormat)*m_channelCount;

		// ！！！！===============！！！！！
		// 目前 PortAudio 都以 float 数组方式播放数据
		// 所以，缓冲区中的数据，必须保证是 float 类型的
		// 所有采集的整型数据数组，都要转换成 float 类型数据的数组
		// 这一点需要注意！！！！！！！！！！！！
		float *buffer=new float[length/sizeof(float)];
		m_cycledBuffer.read((char *)buffer, length);

		float **out = static_cast<float **>(outputBuffer);

		int leftPhase_=0;
		int rightPhase_=0;

// 		memcpy(outputBuffer, buffer, length);  // 这样不行，不出声音
		for (unsigned int i = 0; i < framesPerBuffer; ++i)
		{
			out[0][i] = buffer[leftPhase_];
			leftPhase_ += 1;

			if(m_channelCount>1)
			{
				out[1][i] = buffer[rightPhase_];
				rightPhase_ += 1;
			}
		}

		delete buffer;
	}

	return paContinue;
// 	return paComplete;
}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
// int CPortAudioPlayer::paCallback( const void *inputBuffer, void *outputBuffer,
// 					  unsigned long framesPerBuffer,
// 					  const PaStreamCallbackTimeInfo* timeInfo,
// 					  PaStreamCallbackFlags statusFlags,
// 					  void *userData )
// {
// 	/* Here we cast userData to Sine* type so we can call the instance method paCallbackMethod, we can do that since 
// 	we called Pa_OpenStream with 'this' for userData */
// 	return ((CPortAudioPlayer*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
// 		framesPerBuffer,
// 		timeInfo,
// 		statusFlags);
// }

void CPortAudioPlayer::addData(char *data, int dataLength)
{
	if(!data)
		return;

// 	if(dataLength<=0 || dataLength>m_cycledBuffer.getBufferLength())
// 		return;
// 
// 	if(dataLength>m_cycledBuffer.getRestLength())
// 		return;

	m_cycledBuffer.write(data, dataLength);

	if(m_isAudioPlayWhenDataAdding)
		if(m_isPlaying)
			start();

// 	if(!Pa_IsStreamActive(stream))
// 	{
// 		start();
// 	}
// 	m_cycledBuffer.WriteDataToBuff(data, dataLength);
}

void CPortAudioPlayer::initBuffer()
{
	if(m_cycledBuffer.getDataLength()>0)
		m_cycledBuffer.init();
}

int CPortAudioPlayer::getSizeOf(portaudio::SampleDataFormat format)
{
// #define paFloat32        ((PaSampleFormat) 0x00000001) /**< @see PaSampleFormat */
// #define paInt32          ((PaSampleFormat) 0x00000002) /**< @see PaSampleFormat */
// #define paInt24          ((PaSampleFormat) 0x00000004) /**< Packed 24 bit format. @see PaSampleFormat */
// #define paInt16          ((PaSampleFormat) 0x00000008) /**< @see PaSampleFormat */
// #define paInt8           ((PaSampleFormat) 0x00000010) /**< @see PaSampleFormat */
// #define paUInt8          ((PaSampleFormat) 0x00000020) /**< @see PaSampleFormat */
// #define paCustomFormat   ((PaSampleFormat) 0x00010000) /**< @see PaSampleFormat */

	int ret=0;

	switch(format)
	{
	case portaudio::FLOAT32:
	case portaudio::INT32:
		ret = 4;
		break;
	case portaudio::INT24:
		ret = 3;
		break;
	case portaudio::INT16:
		ret = 2;
		break;
	case portaudio::INT8:
	case portaudio::UINT8:
		ret = 1;
		break;
	case portaudio::INVALID_FORMAT:
		ret=0;
		break;
	default:
		ret = 0;
	}
	return ret;
}
