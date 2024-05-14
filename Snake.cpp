#include "Snake.h"

#include<QFont>
#include<QFile>
#include<QMessageBox>
#include<QMediaPlayer>
#include<QAudioOutput>

const int BODYSIZE = 30;

Snake::Snake(const int winWidth, const int winHeight,QWidget* parent)
	:m_winWidth(winWidth)
	,m_winHeight(winHeight)
	,m_parent(parent)	//身体节数
	,m_changeing(false)
{
	//先初始化一节头一节尾
	auto lab = new QLabel(m_parent);
	QPixmap pix;
	
	pix.load(":/Resource/head.png");
	pix = pix.scaled(BODYSIZE, BODYSIZE);
	lab->setFixedSize(pix.size());
	lab->setPixmap(pix);
	lab->move(100, 100);
	m_body.push_back(lab);

	auto lab1 = new QLabel(m_parent);
	pix.load(":/Resource/tail.png");
	pix = pix.scaled(BODYSIZE, BODYSIZE);
	lab1->setFixedSize(pix.size());
	lab1->setPixmap(pix);
	lab1->move(85, 100);
	m_body.push_back(lab1);
	
	auto audio1 = new QAudioOutput(m_parent);

	m_player1 = new QMediaPlayer(m_parent);
	m_player1->setAudioOutput(audio1);
	m_player1->setSource(QUrl("qrc::/Resource/gameOver.wav"));
}

void Snake::move()
{
	//qDebug() << "当前身体长度 ： " << m_body.size();

	//移动身体
	for (size_t i = m_body.size()-1; i >= 1 ; i--)
	{
		auto it = m_body[i - 1];//和前面的相比
		m_body[i]->move(it->pos());
		//qDebug() << " i : " << i << " pos : " << m_body[i]->pos();
	}
	//移动头
	switch (this->m_curDirection)
		{
		case Direction::Up:
		{
			//qDebug() << "开始往上移动";
			if (this->m_curDirection == Direction::Down)break;
			this->m_curDirection = Direction::Up;
			auto it = m_body[0];
			if (it->y() <= 25) {
				drawMassageBox("撞地找不到北？");
			}
			it->move(it->x(), it->y() - BODYSIZE * 0.6);
			break;
		}
		case Direction::Down:
		{
			//qDebug() << "开始往下移动";
			if (this->m_curDirection == Direction::Up)break;
			this->m_curDirection = Direction::Down;
			auto it = m_body[0];
			if (it->y() >= m_winHeight-40) {
				drawMassageBox("不撞南墙不回头？");
			}
			it->move(it->x(), it->y() + BODYSIZE * 0.6);
			break;
		}
		case Direction::Left:
		{
			//qDebug() << "开始往左移动";
			if (this->m_curDirection == Direction::Right)break;
			this->m_curDirection = Direction::Left;
			auto it = m_body[0];
			if (it->x() <= 25) {
				drawMassageBox("撞一下舒服吗？");
			}
			it->move(it->x() - BODYSIZE * 0.6, it->y());
			break;
		}
		case Direction::Right:
		{
			//qDebug() << "开始往右移动";
			if (this->m_curDirection == Direction::Left)break;
			this->m_curDirection = Direction::Right;
			auto it = m_body[0];
			if (it->x() >= m_winWidth-40) {
				drawMassageBox("手别抖啊...");
			}
			it->move(it->x() + BODYSIZE * 0.6, it->y());
			break;
		}
		default:
			break;
		}
	//判断头是否咬到尾巴
	if (isEatTail()) {
		drawMassageBox("咬到自己尾巴了 ^A^ ");
	}

	//移动过才算 转换方向成功 
	m_changeing = false;
}

void Snake::addBody()
{
	//qDebug() << "添加身体";
	auto lab = new QLabel(m_parent);
	QPixmap pix;
	pix.load(":/Resource/tail.png");
	pix = pix.scaled(BODYSIZE, BODYSIZE);
	lab->setFixedSize(pix.size());
	lab->setPixmap(pix);
	lab->move(m_body.back()->pos());
	lab->setVisible(true);	//莫名其妙 //不这样的话在connect(m_timer, &QTimer::timeout, [&]内部调用addBody没有效果 
	m_body.push_back(lab);
	//qDebug() << "当前身体长度 ： " << m_body.size();
}

void Snake::changeDir(const Direction& d)
{
	m_changeing = true;
	if ((this->m_curDirection == Left && d != Right)||(this->m_curDirection == Right && d != Left)||
		(this->m_curDirection == Up && d != Down) || (this->m_curDirection == Down && d != Up))
		this->m_curDirection = d;
	//qDebug() << "当前方向 ： " << d;

}

void Snake::drawMassageBox(const QString& str)
{
	m_player1->play();
	QMessageBox m(m_parent);
	QFile file(":/style.css");
	if (file.open(QIODevice::ReadOnly)) { m.setStyleSheet(file.readAll()); }
	m.setWindowTitle("Game Over");
	m.setText(str);
	m.setIconPixmap(QPixmap(":/Resource/gameover.png").scaled(100, 100));
	m.exec();
	this->m_parent->close();
}

const QPoint Snake::getHeadRectCenter()
{
	return m_body[0]->rect().translated(m_body[0]->mapToParent(QPoint(0, 0))).center();
}

bool Snake::isEatTail()
{
	for (size_t i = 1; i < m_body.size(); i++)
	{//m_food->rect().translated(m_food->mapToParent(QPoint(0, 0)));
		auto rect = m_body[i]->rect().translated(m_body[i]->mapToParent(QPoint(0, 0)));
		//qDebug() << "rect : " << rect << " head : " << getHeadRectCenter();
		if (rect.contains(getHeadRectCenter())) {
			return true;
		}
	}
	return false;
}

Snake::~Snake()
{
	
}

bool Snake::isChangeing()
{
	return m_changeing;
}

const int Snake::getLen()
{
	return m_body.size();
}
