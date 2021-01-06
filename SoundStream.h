#pragma once
#include <QIODevice>
#include <QAudioOutput>

class SoundStream: public QIODevice
{
	Q_OBJECT
public:
	SoundStream() = default;
	SoundStream(const SoundStream& ) = delete;
	SoundStream(      SoundStream&&) = delete;
	SoundStream& operator=(const SoundStream& ) = delete;
	SoundStream& operator=(      SoundStream&&) = delete;

	void start(int a_sample_rate, int a_channel_count, int a_sample_size);
	void pause();
	void stop();

signals:
	void dataRequired(char* a_buffer, qint64 a_size);

protected:
	// QIODevice
	virtual qint64 readData(char* a_buffer, qint64 a_size) override;
	virtual qint64 writeData(const char*, qint64) override;

private:
	QAudioOutput* m_audio_output = nullptr;
};
