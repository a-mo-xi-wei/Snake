#include "MainWindow.h"
#include<QPixmap>
#include<QPainter>
#include<QPushButton>
#include<QFile>
#include<QGraphicsDropShadowEffect>
#include<QMediaPlayer>
#include<QAudioOutput>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
{
	init();
}

void MainWindow::init()
{
	//给窗口加上阴影特效
	auto effect = new QGraphicsDropShadowEffect(this);
	effect->setOffset(0);
	effect->setBlurRadius(10);
	this->setGraphicsEffect(effect);
	//设置窗口属、样式
	this->setFixedSize(800, 500);
	this->setWindowIcon(QIcon(":/Resource/she.png"));
	QFile file(":/style.css");
	if (file.open(QIODevice::ReadOnly))
	{
		this->setStyleSheet(file.readAll());
	}
	//初始化媒体播放器
	m_player1 = new QMediaPlayer(this);
	auto audio1 = new QAudioOutput(this);
	m_player1->setAudioOutput(audio1);
	m_player1->setSource(QUrl("qrc:/Resource/gameStart.wav"));

	//开始按钮
	m_startBtn = new QPushButton(this);
	m_startBtn->setFixedSize(QSize(100, 50));
	m_startBtn->setText("开始游戏");
	m_startBtn->move((this->width() - m_startBtn->width()) / 2, this->height() - 150);

	connect(m_startBtn, &QPushButton::clicked, [=]
		{
			m_player1->play();
			this->close();
			m_playWindow = new PlayWindow;
			m_playWindow->show();
		});
}

void MainWindow::paintEvent(QPaintEvent* ev)
{
	QPixmap pix;
	pix.load(":/Resource/bg1.png");
	pix = pix.scaled(this->size());
	QPainter painter(this);
	painter.drawPixmap(0, 0, pix);

}