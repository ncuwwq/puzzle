#pragma once
#include <QtWidgets/QMainWindow>

class Sudoku : public QMainWindow
{
	Q_OBJECT
public:
	Sudoku(QWidget *parent = Q_NULLPTR);
	void drawPart(QPainter &p, QImage *img);
	QRect rect;
	unsigned int partId;
	Sudoku& operator = (const Sudoku&);
	int row, col;
signals:
public slots:
};