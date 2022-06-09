#pragma once

#include <QWidget>
#include <QPainter>

namespace Ui { class paintWidget; };

class paintWidget : public QWidget
{
	Q_OBJECT

public:
	paintWidget(QWidget *parent = Q_NULLPTR);
	~paintWidget();

protected:
	void paintEvent(QPaintEvent* e);

private:
	Ui::paintWidget *ui;
};
