#include "paintWidget.h"
#include "ui_paintWidget.h"

paintWidget::paintWidget(QWidget* parent)
	: QWidget(parent)
{
	ui = new Ui::paintWidget();
	ui->setupUi(this);
}

paintWidget::~paintWidget()
{
	delete ui;
}

void paintWidget::paintEvent(QPaintEvent* e)
{
	//draw x,y axis
	x_r = 10;
	x_l = -10;
	y_u = 10;
	y_d = -10;
	QPainter painter(this);
	int w = this->width();
	int h = this->height();
	painter.setPen(QPen(Qt::black, 2));
	painter.drawLine(0, h / 2, w, h / 2);
	painter.drawLine(w / 2, 0, w / 2, h);
	painter.drawText(w / 2 - 10, h / 2 + 10, "O");

	painter.setPen(QPen(Qt::black, 0.5));
	//*horizontal
	for (int i = 1; i < 8; i++)
	{
		if (i != 8 / 2)
		{
			painter.drawLine(0, i * (h / 8), w, i * (h / 8));
			std::stringstream ss;
			ss << i * ((y_d - y_u) / 8) + y_u;	//y軸上數值
			painter.drawText(w / 2+5, i * (h / 8) + 10, QString::fromStdString(ss.str()));

		}
	}
	//*vertical
	for (int i = 1; i < 8; i++)
	{
		if (i != 8 / 2)
		{

			painter.drawLine(i * (w / 8), 0, i * (w / 8), h);
			std::stringstream ss;
			ss << i * ((x_r - x_l) / 8) + x_l;	//x軸上數值
			painter.drawText(i * (w / 8) + 5, h / 2 + 10, QString::fromStdString(ss.str()));
		}
	}

	//draw equation

}
