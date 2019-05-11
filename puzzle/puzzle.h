#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_puzzle.h"
#include "Sudoku.h"
#include <QMouseEvent>
#include <qpushbutton.h>
#include <qspinbox.h>

class puzzle : public QMainWindow
{
	Q_OBJECT

public:
	puzzle(QWidget *parent = Q_NULLPTR);
	~puzzle();

	virtual void paintEvent(QPaintEvent *);
public slots:
	void onBtnClicked();
	void onSpinBoxValueChanged(int);

private:
	int width, height, radius, totalRadius;

	QImage *img;
	QPushButton *btn;

	Sudoku **map;

	bool win;

	void orderBroken();
	virtual void click(QPoint pt);
	virtual void mouseReleaseEvent(QMouseEvent *ev);
	bool checkRange(int, int);
	bool checkGameOver();
	Ui::puzzleClass ui;
};
