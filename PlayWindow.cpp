#include "PlayWindow.h"
#include<QPixmap>
#include<QPainter>
#include<QPushButton>
#include<QFile>
#include<QGraphicsDropShadowEffect>
#include<QTimer>
#include<QMouseEvent>
#include<QRandomGenerator>
#include<QLabel>
#include<QMediaPlayer>
#include<QAudioOutput>
#include<QThread>
PlayWindow::PlayWindow(QWidget* parent)
	:QWidget(parent)
	, m_multi(0)
	, m_interval(300)
	, m_score(0)
{
	//效果好很多
	QThread::create(&PlayWindow::playMusic, this)->start();
	//playMusic();
	init();
}

PlayWindow::~PlayWindow()
{
	delete m_snake;
}

void PlayWindow::playMusic()
{
	m_player2 = new QMediaPlayer;
	auto audio2 = new QAudioOutput(this);
	m_player2->setAudioOutput(audio2);
	m_player2->setSource(QUrl("qrc:/Resource/background.wav"));
	m_player2->setLoops(QMediaPlayer::Infinite);
	m_player2->play();
}

void PlayWindow::init()
{
	//给窗口加上阴影特效
	auto effect = new QGraphicsDropShadowEffect(this);
	effect->setOffset(0);
	effect->setBlurRadius(10);
	this->setGraphicsEffect(effect);
	this->setFixedSize(800, 500);
	this->setWindowIcon(QIcon(":/Resource/she.png"));
	QFile file(":/style.css");
	if (file.open(QIODevice::ReadOnly))
	{
		this->setStyleSheet(file.readAll());
	}

	m_snake = new Snake(this->width(), this->height(), this);
	m_timer = new QTimer(this);
	m_timer->setInterval(this->m_interval - m_multi*25);
	m_timer->start();
	//食物
	m_food = new QLabel(this);
	m_food->setFixedSize(25, 25);
	drawFood();
	//分数板
	m_mark = new QLabel(this);
	QString str = "QLabel{color:#99FFFF;font:bold 20px ‘华文行楷’;min-width:180px;}";//若是宽度不够，会造成显示不全
	m_mark->setStyleSheet(str);
	m_mark->adjustSize();
	m_mark->setText(QString("当前分数 ：%1").arg(m_score));
	m_mark->move(this->width() - m_mark->width(), 20);

	//初始化媒体
	m_player1 = new QMediaPlayer(this);
	auto audio = new QAudioOutput(this);
	m_player1->setAudioOutput(audio);
	m_player1->setSource(QUrl("qrc:/Resource/eatFood.wav"));

	connect(m_timer, &QTimer::timeout, [&]
		{
			m_snake->move();
			auto R = m_snake->getHeadRectCenter();
			//转换坐标系
			QRect foodRect = m_food->rect().translated(m_food->mapToParent(QPoint(0, 0)));
			//qDebug() << foodRect << "  " << R;
			if(foodRect.contains(R)) {
				m_player1->play();
				m_food->clear();
				m_snake->addBody();
				m_score += m_foodScore[m_curFood - 1];
				QString str = QString("当前分数 ：%1").arg(m_score);
				qDebug() << str;
				m_mark->setText(str);
				drawFood();
				//身体长度是3的倍数是加快一次
				if (m_snake->getLen() / 3 > m_multi && m_multi < 8) {
					m_multi = m_snake->getLen() / 3;
					m_timer->setInterval(this->m_interval - m_multi * 25);
					m_timer->start();
				}
			}
		});
	
}

void PlayWindow::drawFood()
{
	QPixmap pix;
	m_curFood = QRandomGenerator::global()->bounded(1, 4);
	pix.load(QString(":/Resource/food%1.png").arg(m_curFood));//左闭右开
	pix = pix.scaled(m_food->size());
	m_food->setPixmap(pix);
	m_food->move(QRandomGenerator::global()->bounded(50, this->width()-50), 
		QRandomGenerator::global()->bounded(50, this->height()-50));
}

void PlayWindow::paintEvent(QPaintEvent* ev)
{
	QPixmap pix;
	pix.load(":/Resource/bg2.png");
	pix = pix.scaled(this->size());
	QPainter painter(this);
	painter.drawPixmap(0,0,pix);

}

void PlayWindow::keyPressEvent(QKeyEvent* event)
{
	if (!m_snake->isChangeing()) {
		switch (event->key())
		{
		case Qt::Key_Up:
		{
			m_snake->changeDir(Snake::Direction::Up);
			break;
		}
		case Qt::Key_Down:
		{
			m_snake->changeDir(Snake::Direction::Down);

			break;
		}
		case Qt::Key_Left:
		{
			m_snake->changeDir(Snake::Direction::Left);

			break;
		}
		case Qt::Key_Right:
		{
			m_snake->changeDir(Snake::Direction::Right);

			break;
		}
		default:
			break;
		}
	}

}

