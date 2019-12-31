#include "StdAfx.h"
#include "PortAudioRecorder.h"

CPortAudioRecorder::CPortAudioRecorder(void)
: m_sampleFormat(portaudio::INT16), m_framesPerBuffer(DEFAULT_FRAMES_PER_BUFFER), sys(portaudio::System::instance())
{
}

CPortAudioRecorder::~CPortAudioRecorder(void)
{
}

BOOL CPortAudioRecorder::open( int channelCount/*=1*/, portaudio::SampleDataFormat sampleFormat/*=portaudio::INT16*/, double sampleRate/*=DEFAULT_SAMPLE_RATE*/, ULONG framesPerBuffer/*=DEFAULT_FRAMES_PER_BUFFER*/ )
{
	portaudio::DirectionSpecificStreamParameters inParams(sys.defaultInputDevice(), channelCount, sampleFormat, false, sys.defaultInputDevice().defaultLowInputLatency(), NULL);
	portaudio::StreamParameters params(inParams, portaudio::DirectionSpecificStreamParameters::null(), sampleRate, framesPerBuffer, paClipOff);

	m_defaultInputDevice=sys.defaultInputDevice().name();

	try
	{
		stream.open(params, *this, &CPortAudioRecorder::paCallbackMethod);

		m_channelCount=channelCount;
		m_sampleFormat=sampleFormat;
		m_sampleRate=sampleRate;
		m_framesPerBuffer=framesPerBuffer;
	}
	catch(portaudio::PaException &e)
	{
		m_errMsg=e.paErrorText();
		return FALSE;
	}

	return TRUE;
}

BOOL CPortAudioRecorder::close()
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

BOOL CPortAudioRecorder::start()
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

	return TRUE;
}

BOOL CPortAudioRecorder::stop()
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

int CPortAudioRecorder::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
									   unsigned long framesPerBuffer,
									   const PaStreamCallbackTimeInfo* timeInfo,
									   PaStreamCallbackFlags statusFlags)
{
	(void) timeInfo; /* Prevent unused variable warnings. */
	(void) statusFlags;
	(void) inputBuffer;

	if(m_cycledBuffer.getDataLength()+framesPerBuffer*getSizeOf(m_sampleFormat)*m_channelCount>m_cycledBuffer.getBufferLength())
		return paContinue;

	int length=m_framesPerBuffer * getSizeOf(m_sampleFormat) * m_channelCount;
	m_cycledBuffer.write((char *)inputBuffer, length);
// 	if(length<=0)
// 	{
// 		stop();
// 		// 		memset(outputBuffer, 0x00, m_framesPerBuffer * getSizeOf(m_sampleFormat) * m_channelCount);
// 	}
// 	else
// 	{
// 		// 		m_cycledBuffer.read((char *)outputBuffer, length);
// 
// 		length=length/getSizeOf(m_sampleFormat)*getSizeOf(m_sampleFormat);
// 		float *buffer=new float[length/sizeof(float)];
// 		m_cycledBuffer.read((char *)buffer, length);
// 
// 		float **out = static_cast<float **>(outputBuffer);
// 
// 		int leftPhase_=0;
// 		int rightPhase_=0;
// 		for (unsigned int i = 0; i < framesPerBuffer; ++i)
// 		{
// 			out[0][i] = buffer[leftPhase_];
// 			out[1][i] = buffer[rightPhase_];
// 
// 			leftPhase_ += 1;
// 			// 			if (leftPhase_ >= tableSize_)
// 			// 				leftPhase_ -= tableSize_;
// 
// 			rightPhase_ += 1;
// 			// 			if (rightPhase_ >= tableSize_)
// 			// 				rightPhase_ -= tableSize_;
// 		}
// 
// 		delete buffer;
// 	}

	return paContinue;

	// 	return paComplete;

}

int CPortAudioRecorder::getSizeOf( portaudio::SampleDataFormat format )
{
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

int CPortAudioRecorder::getData( char *buffer, int bufferLen )
{
	int length=min(bufferLen, m_cycledBuffer.getDataLength());
	if(length<=0)
		return 0;

	m_cycledBuffer.read(buffer, length);
	return length;
}
