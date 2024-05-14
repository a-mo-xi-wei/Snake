#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include<QWidget>
#include"PlayWindow.h"

class QPushButton;
class QMediaPlayer;
class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	void init();

protected:
	void paintEvent(QPaintEvent* ev)override;
private:
	QPushButton* m_startBtn{};
	PlayWindow* m_playWindow{};
	QMediaPlayer* m_player1{};
	QMediaPlayer* m_player2{};
};

#endif // !MAINWINDOW_H_
