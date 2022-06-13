#pragma once
#include "MainHeader.h"
#include <QWidget>
#include <QPainter>

namespace Ui { class paintWidget; };

class paintWidget : public QWidget
{
	Q_OBJECT

public:
	paintWidget(QWidget* parent = Q_NULLPTR);
	~paintWidget();

protected:
	void paintEvent(QPaintEvent* e);

private:
	Ui::paintWidget* ui;
	double x_r, x_l, y_u, y_d;
};
