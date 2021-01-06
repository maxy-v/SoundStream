#include "SoundStream.h"

void SoundStream::start(int a_sample_rate, int a_channel_count, int a_sample_size)
{
	if (m_audio_output != nullptr)
		delete m_audio_output;

	QAudioFormat format;
	format.setSampleRate(a_sample_rate);
	format.setChannelCount(a_channel_count);
	format.setSampleSize(a_sample_size);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	open(QIODevice::ReadOnly);

	m_audio_output = new QAudioOutput(format, this);
	m_audio_output->start(this);
}

void SoundStream::pause()
{
	if (m_audio_output == nullptr)
		return;

	if (m_audio_output->state() == QAudio::ActiveState)
		m_audio_output->suspend();
	else
		m_audio_output->resume();
}

void SoundStream::stop()
{
	if (m_audio_output == nullptr)
		return;

	m_audio_output->stop();
}

qint64 SoundStream::readData(char* a_buffer, qint64 a_size)
{
	emit dataRequired(a_buffer, a_size);
	return a_size;
}

qint64 SoundStream::writeData(const char*, qint64)
{
	// Not supported
	return 0;
}
