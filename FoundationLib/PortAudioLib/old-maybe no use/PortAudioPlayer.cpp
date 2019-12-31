#include "StdAfx.h"
#include "PortAudioPlayer.h"

CPortAudioPlayer::CPortAudioPlayer(void)
: m_isOpen(FALSE), m_buffer(NULL), m_sampleFormat(paInt16), m_framesPerBuffer(DEFAULT_FRAMES_PER_BUFFER), m_isBufferComplete(FALSE), m_threshold(1000)
{
	err=Pa_Initialize();
	if( err != paNoError )
		m_isInitialized=FALSE;
	else
		m_isInitialized=TRUE;

	ZeroMemory(m_abandonedBuffer, 2048);

// 	m_cycledBuffer.redimLength(1024000);

}

CPortAudioPlayer::~CPortAudioPlayer(void)
{
	Pa_Terminate();
}

PaDeviceIndex CPortAudioPlayer::getDefaultOutputDevice()
{
	return Pa_GetDefaultOutputDevice();
}

long CPortAudioPlayer::getDataLength()
{
	return m_cycledBuffer.getDataLength();
}


BOOL CPortAudioPlayer::open(PaDeviceIndex index, int channelCount, PaSampleFormat sampleFormat, double sampleRate, ULONG framesPerBuffer)
{
	m_isOpen=FALSE;

	if(!m_isInitialized)
		return FALSE;

	m_sampleFormat=sampleFormat;
	m_framesPerBuffer=framesPerBuffer;

	PaStreamParameters outputParameters;

	outputParameters.device = index;
	if (outputParameters.device == paNoDevice) {
		m_isOpen=FALSE;
		return FALSE;
	}

	outputParameters.channelCount = channelCount;       /* stereo output */
	outputParameters.sampleFormat = sampleFormat; /* 32 bit floating point output */
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	PaError err = Pa_OpenStream(
		&stream,
		NULL, /* no input */
		&outputParameters,
		sampleRate,
		framesPerBuffer,
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		&CPortAudioPlayer::paCallback,
		this            /* Using 'this' for userData so we can cast to Sine* in paCallback method */
		);

	if (err != paNoError)
	{
		/* Failed to open stream to device !!! */
		m_isOpen=FALSE;
		return FALSE;
	}

// 	err = Pa_SetStreamFinishedCallback( stream, &CPortAudioPlayer::paStreamFinished );
// 	if (err != paNoError)
// 	{
// 		Pa_CloseStream( stream );
// 		stream = 0;
// 
// 		return false;
// 	}

// 	if(m_buffer)
// 		delete m_buffer;
// 	m_buffer=new char[framesPerBuffer * getSizeOf(m_sampleFormat)];

	m_isOpen=TRUE;

	return TRUE;
}

BOOL CPortAudioPlayer::close()
{
	if (stream == 0)
		return false;

	PaError err = Pa_CloseStream( stream );
	stream = 0;

// 	if(m_buffer)
// 		delete m_buffer;

	if(err==paNoError)
		m_isOpen=FALSE;

	return (err == paNoError);
}


BOOL CPortAudioPlayer::start()
{
	if (stream == 0)
		return false;

	PaError err = Pa_StartStream( stream );

	return (err == paNoError);
}

BOOL CPortAudioPlayer::stop()
{
	if (stream == 0)
		return false;

	PaError err = Pa_StopStream( stream );

	return (err == paNoError);
}

/* The instance callback, where we have access to every method/variable in object of class Sine */
int CPortAudioPlayer::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags)
{
	m_isBufferComplete=FALSE;

	float *out = (float*)outputBuffer;
// 	unsigned long i;

	(void) timeInfo; /* Prevent unused variable warnings. */
	(void) statusFlags;
	(void) inputBuffer;

//         for( i=0; i<framesPerBuffer/2; i++ )
//         {
//             *out++ = sine[left_phase];  /* left */
//             *out++ = sine[right_phase];  /* right */
//             left_phase += 1;
//             if( left_phase >= TABLE_SIZE ) left_phase -= TABLE_SIZE;
//             right_phase += 3; /* higher pitch so we can distinguish left and right. */
//             if( right_phase >= TABLE_SIZE ) right_phase -= TABLE_SIZE;
//         }

// 		for(i=0/2;i<framesPerBuffer;i++)
// 		{
// 			*out++=100;
// 			*out++=25;
// 		}

	int length=min(m_framesPerBuffer * getSizeOf(m_sampleFormat), m_cycledBuffer.getDataLength());
	if(length<=0)  // 如果没有音频数据，则传入静音数据
	{
// 		m_isBufferComplete=TRUE;
// 		return paComplete;
		memset(outputBuffer, 0x00, m_framesPerBuffer * getSizeOf(m_sampleFormat));
	}
	else
	{
		m_cycledBuffer.read((char *)outputBuffer, length);
		if(m_cycledBuffer.getDataLength()>=m_threshold)
			m_cycledBuffer.read(m_abandonedBuffer, 2);
	}

	return paContinue;

}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
int CPortAudioPlayer::paCallback( const void *inputBuffer, void *outputBuffer,
					  unsigned long framesPerBuffer,
					  const PaStreamCallbackTimeInfo* timeInfo,
					  PaStreamCallbackFlags statusFlags,
					  void *userData )
{
	/* Here we cast userData to Sine* type so we can call the instance method paCallbackMethod, we can do that since 
	we called Pa_OpenStream with 'this' for userData */
	return ((CPortAudioPlayer*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
		framesPerBuffer,
		timeInfo,
		statusFlags);
}

void CPortAudioPlayer::addData(char *data, int dataLength)
{
	if(!data)
		return;

	if(dataLength<=0 || dataLength>m_cycledBuffer.getBufferLength())
		return;

	m_cycledBuffer.write(data, dataLength);

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

int CPortAudioPlayer::getSizeOf(PaSampleFormat format)
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
	case paFloat32:
	case paInt32:
		ret = 4;
		break;
	case paInt24:
		ret = 3;
		break;
	case paInt16:
		ret = 2;
		break;
	case paInt8:
	case paUInt8:
		ret = 1;
		break;
	default:
		ret = 4;
	}
	return ret;
}
