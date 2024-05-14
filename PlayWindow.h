#ifndef PLAYWINDOW_H_
#define PLAYWINDOW_H_
#include"Snake.h"
#include<QWidget>

class QTimer;
class QPushButton;
class QLabel;
class QMediaPlayer;
class PlayWindow : public QWidget
{
	Q_OBJECT
public:
	PlayWindow(QWidget* parent = nullptr);
	~PlayWindow();
	void playMusic();
	void init();
	void drawFood();
protected:
	void paintEvent(QPaintEvent* ev)override;
	void keyPressEvent(QKeyEvent* event)override;
private:
	//初始时间间隔
	int m_interval;
	//speed increase
	int m_multi;

	QTimer* m_timer;
	Snake* m_snake{};
	QLabel* m_food{};
	//分数
	QLabel* m_mark;
	int m_score;
	//当前食物序号 
	int m_curFood;
	int m_foodScore[3] = { 4,6,8 };

	//吃食物声音
	QMediaPlayer* m_player1{};
	QMediaPlayer* m_player2{};
};

#endif // !PLAYWINDOW_H_
