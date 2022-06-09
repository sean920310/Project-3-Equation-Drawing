#include "paintWidget.h"
#include "ui_paintWidget.h"

paintWidget::paintWidget(QWidget *parent)
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
	QPainter painter(this);
	int w = this->width();
	int h = this->height();
	painter.drawLine(0, h/2, w, h/2);
	painter.drawLine(w/2, 0, w/2, h);
}
