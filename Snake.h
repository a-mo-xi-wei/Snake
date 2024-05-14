#ifndef SNAKE_H_
#define SNAKE_H_

#include<QLabel>
#include<QWidget>
class QMediaPlayer;
class Snake
{
public:
	//运动方向
	enum Direction {
		Up = 1,
		Down = 2,
		Left = 3,
		Right = 4
	};
	//传入必要参数
	Snake(const int winWidth,const int winHeight,QWidget* parent = nullptr);
	//设整体移动
	void move();
	//添加尾部
	void addBody();
	//改变方向
	void changeDir(const Direction& d);
	//消息提示框
	void drawMassageBox(const QString& str);
	//获取头部中心点 ， 因为矩形的话范围大了
	const QPoint getHeadRectCenter();
	//是否咬尾
	bool isEatTail();
	~Snake();
	//正在改变头的运动方向
	bool isChangeing();
	//获取身体长度
	const int getLen();
private:
	QWidget* m_parent{};

	int m_winWidth;
	int m_winHeight;

	QVector<QLabel*>m_body{};

	Direction m_curDirection = Direction::Right;

	bool m_changeing;

	QMediaPlayer* m_player1{};

};

#endif // !SNAKE_H_
