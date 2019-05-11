#include <cmath>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qrect.h>
#include "Sudoku.h"

Sudoku::Sudoku(QWidget *parent) : QMainWindow(parent)
{
	partId = 0;
}

void Sudoku::drawPart(QPainter &p, QImage *img)
{
	p.setBrush(Qt::white);
	p.drawRect(col*rect.width(), row*rect.height(), rect.width(), rect.height());
	if (partId != 0) {
		p.drawImage(col*rect.width(), row*rect.height(), *img, rect.x(), rect.y(), rect.width(), rect.height());
	}
}

Sudoku &Sudoku::operator=(const Sudoku &pp)
{
	partId = pp.partId;
	rect = pp.rect;
	return *this;
}