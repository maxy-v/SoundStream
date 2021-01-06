#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget* a_parent)
	: QWidget(a_parent)
	, m_ui(new Ui::MainWidget)
{
	m_ui->setupUi(this);

	connect(m_ui->btnPlay , &QPushButton::clicked, [this]() { m_stream.start(44100, 1, 16); });
	connect(m_ui->btnPause, &QPushButton::clicked, &m_stream, &SoundStream::pause);
	connect(m_ui->btnStop , &QPushButton::clicked, &m_stream, &SoundStream::stop);

	connect(&m_stream, &SoundStream::dataRequired, this, &MainWidget::onSoundDataRequest);
}

MainWidget::~MainWidget()
{
	delete m_ui;
}

void MainWidget::onSoundDataRequest(char* a_buffer, qint64 a_size)
{
	int16_t* buffer = reinterpret_cast<int16_t*>(a_buffer);
	a_size /= sizeof(*buffer);

	auto max_value = std::numeric_limits<std::remove_reference_t<decltype(*buffer)>>::max();

	// Generate supersaw

	static std::array<double, 4> saws = {0,0,0,0};
	static std::array<double, 4> incs = {0.004,0.0041,0.0042,0.0043};

	for (qint64 sample = 0; sample < a_size; sample++, buffer++)
	{
		buffer[0] = 0;
		for (size_t saw = 0; saw < saws.size(); saw++)
		{
			double& level = saws[saw];
			buffer[0] += static_cast<uint16_t>( level*max_value/5.0 );
			level += incs[saw];
			if (level > 1.0)
				level = fmod(level, 1.0);
		}
	}
}
