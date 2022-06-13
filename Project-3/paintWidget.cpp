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
	painter.drawText((0 - x_l) * (w / (x_r - x_l)), (0 - y_u) * (h / (y_d - y_u)), "O");

	painter.setPen(QPen(Qt::black, 0.5));
	//*horizontal
	for (int i = 1; i < 10; i++)
	{
		if (i != 10 / 2)
		{
			painter.drawLine(0, i * (h / 10), w, i * (h / 10));
			std::stringstream ss;
			ss << i * ((y_d - y_u) / 10) + y_u;	//y軸上數值
			painter.drawText(w / 2 + 5, i * (h / 10) + 10, QString::fromStdString(ss.str()));

		}
	}
	//*vertical
	for (int i = 1; i < 10; i++)
	{
		if (i != 10 / 2)
		{

			painter.drawLine(i * (w / 10), 0, i * (w / 10), h);
			std::stringstream ss;
			ss << i * ((x_r - x_l) / 10) + x_l;	//x軸上數值
			painter.drawText(i * (w / 10) + 5, h / 2 + 10, QString::fromStdString(ss.str()));
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
						painter.drawPoint((i - x_l) * (w / (x_r - x_l)), (y - y_u) * (h / (y_d - y_u)));
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
		qDebug() << u8"左鍵";
	}
	else if (e->button() == Qt::RightButton)
	{
		qDebug() << u8"右鍵";
	}
}

void paintWidget::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)
	{
		qDebug() << u8"上滾";
	}
	else
	{
		qDebug() << u8"下滾";
	}
}

