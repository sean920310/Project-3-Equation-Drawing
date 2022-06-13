#pragma once
#include "MainHeader.h"
#include "ListModel.h"
#include "Parser.h"
#include <QWidget>

namespace Ui { class paintWidget; };

class paintWidget : public QWidget
{
	Q_OBJECT

public:
	paintWidget(QWidget* parent = Q_NULLPTR);
	~paintWidget();

protected:
	void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void wheelEvent(QWheelEvent* event);

private:
	Ui::paintWidget* ui;
	double x_r, x_l, y_u, y_d;
	double scale = 1;
	QPointF mouseLastPos;
	bool drag = false;
	int w, h;
};
