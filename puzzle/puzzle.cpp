#include "puzzle.h"
#include <qpainter.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qfiledialog.h>

puzzle::puzzle(QWidget *parent)
	: QMainWindow(parent)
{
	totalRadius = 600;
	width = 3;
	height = 3;
	radius = totalRadius / width;
	win = false;

	map = new Sudoku*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new Sudoku[width];
		for (int j = 0; j < width; j++) {
			map[i][j].rect = QRect(radius*j, radius*i, radius, radius);
			map[i][j].partId = i * width + j;
			map[i][j].row = i;
			map[i][j].col = j;
		}
	}

	orderBroken();
	update();
	this->setFixedSize(1000, 600);

	QString fileName = tr(":/puzzl/Resources/1.jpg");
	img = new QImage;
	img->load(fileName);
	*img = img->scaled(600, 600, Qt::IgnoreAspectRatio);

	btn = new QPushButton(this);
	btn->setText(tr("select"));
	btn->setFont(QFont(tr("宋体"), 12));
	btn->setGeometry(totalRadius + 150, 80, 120, 40);
	connect(btn, &QPushButton::clicked,
		this, &puzzle::onBtnClicked);
}

puzzle::~puzzle()
{
	for (int i = 0; i < height; i++) {
		delete[] map[i];
	}
	delete[] map;

	delete img;
	delete btn;
}

void puzzle::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setBrush(Qt::white);

	p.setPen(QPen(Qt::white, 5, Qt::SolidLine));
	p.setFont(QFont("宋体", radius*0.6));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			map[i][j].drawPart(p, img);
		}
	}

	p.drawImage(totalRadius + 50, totalRadius - 350,
		img->scaled(300, 300, Qt::IgnoreAspectRatio),
		0, 0, 300, 300);

}

void puzzle::onBtnClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("select"), "", tr("Images(*.png *.bmp *.jpg *.gif )"));
	if (!fileName.isEmpty()) {
		QImage *imgTemp;
		imgTemp = new QImage;
		if (imgTemp->load(fileName)) {
			*imgTemp = imgTemp->scaled(width*radius, height*radius,
				Qt::IgnoreAspectRatio);
			if (img)
				delete img;
			img = imgTemp;
			onSpinBoxValueChanged(width);
			update();
		}
		else {
			delete imgTemp;
			return;
		}

	}

}

void puzzle::onSpinBoxValueChanged(int value)
{
	for (int i = 0; i < height; i++) {
		delete[] map[i];
	}
	delete[] map;

	width = height = value;
	radius = totalRadius / width;

	map = new Sudoku*[height];

	for (int i = 0; i < height; i++) {
		map[i] = new Sudoku[width];
		for (int j = 0; j < width; j++) {
			map[i][j].rect = QRect(radius*j, radius*i, radius, radius);
			map[i][j].partId = i * width + j;
			map[i][j].row = i;
			map[i][j].col = j;
		}
	}
	orderBroken();
	update();
}

void puzzle::orderBroken()
{
	int k_x1=0, k_y1=0, x2, y2,n;
	for (int i = 0; i < 20; i++) {
		n = rand() % 4;
		int cells[4][2] = { 0,-1,0,1,1,0,-1,0 };
		int y2 = k_y1 - cells[n][0];
		int x2 = k_x1 - cells[n][1];
		if (checkRange(y2, x2)) {
			Sudoku temp;
			temp = map[k_y1][k_x1];
			map[k_y1][k_x1] = map[y2][x2];
			map[y2][x2] = temp;
			k_y1 = y2;
			k_x1 = x2;
		}
	}
}

void puzzle::click(QPoint pt)
{
	if (radius == 0)
		return;
	int y = pt.y() / radius;
	int x = pt.x() / radius;
	if (!checkRange(y, x))
		return;
	//左 右 下 上
	int cells[4][2] = { 0,-1,0,1,1,0,-1,0 };

	for (int i = 0; i < 4; i++) {
		int ry = y + cells[i][0];
		int rx = x + cells[i][1];
		if (checkRange(ry, rx) && map[ry][rx].partId == 0) {
			Sudoku temp;
			temp = map[y][x];
			map[y][x] = map[ry][rx];
			map[ry][rx] = temp;
		}
	}
	update();
	if (checkGameOver() && !win) {
		win = true;
		QMessageBox::StandardButton reply;
		reply = QMessageBox::information(this, tr("Congratulations!"), tr("You Win!"), QMessageBox::Retry | QMessageBox::Cancel);
		if (reply == QMessageBox::Retry) {
			win = false;
			orderBroken();
			update();
		}
		else {
			win = false;
		}
	}
}

void puzzle::mouseReleaseEvent(QMouseEvent *ev)
{
	if (ev->button() != Qt::LeftButton) { 
		return;
	}
	click(ev->pos());
}

bool puzzle::checkRange(int y, int x)
{
	return y >= 0 && y < height&&x >= 0 && x < width;
}

bool puzzle::checkGameOver()
{
	int a=0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j].partId == i * width + j) {
				a++;
			}
		}
	}
	if (a==9) {
		return true;
	}
	else {
		return false;
	}
}
