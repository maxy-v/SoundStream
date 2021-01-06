#pragma once
#include <cmath>
#include <array>
#include <QWidget>
#include <QGraphicsItem>
#include "../SoundStream.h"

namespace Ui { class MainWidget; }

class MainWidget : public QWidget
{
	Q_OBJECT
public:
	MainWidget(QWidget* a_parent = nullptr);
	~MainWidget();

private slots:
	void onSoundDataRequest(char* a_buffer, qint64 a_size);

private:
	Ui::MainWidget* m_ui;
	SoundStream m_stream;
};
