#include "paintWidget.h"
#include "Project3.h"
#include "ui_paintWidget.h"

QColor toQColor(Color color)
{
	switch (color)
	{
	case red:
		return QColor("red");
		break;
	case blue:
		return QColor("blue");
		break;
	case orange:
		return QColor("orange");
		break;
	case green:
		return QColor("green");
		break;
	case purple:
		return QColor("purple");
		break;
	case lime:
		return QColor("lime");
		break;
	case brown:
		return QColor("brown");
		break;
	default:
		return QColor("red");
		break;
	}
}

paintWidget::paintWidget(QWidget* parent)
	: QWidget(parent)
{
	ui = new Ui::paintWidget();
	ui->setupUi(this);
	setMouseTracking(true);

	x_r = 10;
	x_l = -10;
	y_u = 10;
	y_d = -10;
	scale = 1;
}

paintWidget::~paintWidget()
{
	delete ui;
}

void paintWidget::paintEvent(QPaintEvent* e)
{
	//x,y to w,h -> (i - x_l)* (w / (x_r - x_l)), (y - y_u)* (h / (y_d - y_u))

	//draw x,y axis

	QPainter painter(this);
	w = this->width();
	h = this->height();
	//painter.drawText((x - x_l) * (w / (x_r - x_l)) , (y - y_u) * (h / (y_d - y_u)));

	//*horizontal
	if (y_u < 0 || y_d>0)
	{
		painter.setPen(QPen(Qt::black, 0.5));
		for (int i = 1; i < 10; i++)
		{
			painter.drawLine(0, i * (h / 10), w, i * (h / 10));
			std::stringstream ss;
			ss << i * ((y_d - y_u) / 10) + y_u;	//y禸计
			painter.drawText(w / 2 + 5, i * (h / 10) + 10, QString::fromStdString(ss.str()));
		}
	}
	else
	{
		//x axis
		painter.setPen(QPen(Qt::black, 3));
		painter.drawLine(0, (0 - y_u) * (h / (y_d - y_u)), w, (0 - y_u) * (h / (y_d - y_u)));

		painter.setPen(QPen(Qt::black, 0.5));
		for (int i = -9; i < 10; i++)
		{
			if (i!=0)
			{
				painter.drawLine(0, (i * (y_u - y_d) / 10 - y_u) * (h / (y_d - y_u)), w, (i * (y_u - y_d) / 10 - y_u) * (h / (y_d - y_u)));
				std::stringstream ss;
				ss << i * ((y_d - y_u) / 10) + y_u;	//y禸计
				painter.drawText(w / 2 + 5, i * (h / 10) + 10, QString::fromStdString(ss.str()));
			}

		}
	}

	//*vertical
	if (x_r < 0 || x_l>0)
	{
		painter.setPen(QPen(Qt::black, 0.5));
		for (int i = 1; i < 10; i++)
		{
			painter.drawLine(i * (w / 10), 0, i * (w / 10), h);
			std::stringstream ss;
			ss << i * ((x_r - x_l) / 10) + x_l;	//x禸计
			painter.drawText(i * (w / 10) + 5, h / 2 + 10, QString::fromStdString(ss.str()));

		}
	}
	else
	{
		//y axis
		painter.setPen(QPen(Qt::black, 3));
		painter.drawLine((0 - x_l) * (w / (x_r - x_l)), 0, (0 - x_l) * (w / (x_r - x_l)), h);


		painter.setPen(QPen(Qt::black, 0.5));
		for (int i = -9; i < 10; i++)
		{
			if (i!=0)
			{
				painter.drawLine((i * (x_r - x_l) / 10 - x_l) * (w / (x_r - x_l)), 0, (i * (x_r - x_l) / 10 - x_l) * (w / (x_r - x_l)), h);
				std::stringstream ss;
				ss << i * ((x_r - x_l) / 10) + x_l;	//x禸计
				painter.drawText(i * (w / 10) + 5, h / 2 + 10, QString::fromStdString(ss.str()));
			}
		}
	}

	//draw equation
	vector<NumWithName> vars;
	NumWithName x;
	x.name = "x";
	x.num = 0;
	vars.push_back(x);
	for (auto model : Project3::getModelList())
	{
		painter.setPen(QPen(toQColor(model->getData().color), 2));
		if (model->getData().visible)
		{
			QPoint lastPoint;
			for (double i = x_l; i < x_r; i += (x_r - x_l) / 1000)
			{
				for (auto& var : vars)
				{
					if (var.name == "x")
						var.num = i;
				}
				vector<double> numbers;
				Parser equation(model->getData().equation.toStdString());

				if (!equation.calculate(vars, numbers))
				{
					if (numbers.size())
					{
						double y = numbers.at(0);
						if (lastPoint.isNull())
							lastPoint = QPoint((i - x_l) * (w / (x_r - x_l)), (y - y_u) * (h / (y_d - y_u)));
						else
						{
							painter.drawLine(lastPoint, QPoint((i - x_l) * (w / (x_r - x_l)), (y - y_u) * (h / (y_d - y_u))));
							lastPoint = QPoint((i - x_l) * (w / (x_r - x_l)), (y - y_u) * (h / (y_d - y_u)));
						}
						//painter.drawPoint((i - x_l) * (w / (x_r - x_l)), (y - y_u) * (h / (y_d - y_u)));
					}
				}
			}

		}
	}
}

void paintWidget::mousePressEvent(QMouseEvent* e)
{
	qDebug() << e->x() << ":" << e->y();
	if (e->button() == Qt::LeftButton)
	{
		qDebug() << u8"オ龄";
	}
	else if (e->button() == Qt::RightButton)
	{
		qDebug() << u8"龄";
	}

	drag = true;
	this->update();
}

void paintWidget::mouseReleaseEvent(QMouseEvent* e)
{
	mouseLastPos = QPointF();
	drag = false;
	this->update();
}

void paintWidget::mouseMoveEvent(QMouseEvent* e)
{
	if (drag)
	{
		if (mouseLastPos.isNull())
			mouseLastPos = e->localPos();
		else
		{
			QPointF delta = e->localPos() - mouseLastPos;
			mouseLastPos = e->localPos();
			x_r -= delta.x() / w * (x_r - x_l);
			x_l -= delta.x() / w * (x_r - x_l);
			y_u += delta.y() / h * (y_u - y_d);
			y_d += delta.y() / h * (y_u - y_d);
		}
	}
	this->update();
}

void paintWidget::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)
	{
		scale /= 1.3;
		x_r /= 1.3;
		x_l /= 1.3;
		y_u /= 1.3;
		y_d /= 1.3;
		qDebug() << u8"簎" << scale;
	}
	else
	{
		scale *= 1.3;
		x_r *= 1.3;
		x_l *= 1.3;
		y_u *= 1.3;
		y_d *= 1.3;
		qDebug() << u8"簎" << scale;
	}
	this->update();
}

