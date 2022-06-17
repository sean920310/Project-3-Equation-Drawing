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
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(1000);

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
	//x,y to w,h -> (x - x_l)* (w / (x_r - x_l)), (y - y_u)* (h / (y_d - y_u))

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
			ss << i * ((y_d - y_u) / 10) + y_u;	//y軸上數值
			//painter.drawText(w / 2 + 5, i * (h / 10) + 10, QString::fromStdString(ss.str()));
			if (x_r < 0 || x_l>0)
				painter.drawText(0, i * (h / 10) + 10, QString::fromStdString(ss.str()));
			else
				painter.drawText((0 - x_l) * (w / (x_r - x_l)) + 5, i * (h / 10) + 10, QString::fromStdString(ss.str()));

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
			if (i != 0)
			{
				painter.drawLine(0, (i * (y_u - y_d) / 10 - y_u) * (h / (y_d - y_u)), w, (i * (y_u - y_d) / 10 - y_u) * (h / (y_d - y_u)));
				std::stringstream ss;
				ss << i * ((y_u - y_d) / 10.f);	//y軸上數值
				if (x_r < 0 || x_l>0)
					painter.drawText(0, (i * (y_u - y_d) / 10 - y_u) * (h / (y_d - y_u)) + 10, QString::fromStdString(ss.str()));
				else
					painter.drawText((0 - x_l) * (w / (x_r - x_l)) + 5, (i * (y_u - y_d) / 10 - y_u) * (h / (y_d - y_u)) + 10, QString::fromStdString(ss.str()));
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
			ss << i * ((x_r - x_l) / 10) + x_l;	//x軸上數值
			//painter.drawText(i * (w / 10) + 5, h / 2 + 10, QString::fromStdString(ss.str()));
			if (y_u < 0 || y_d>0)
				painter.drawText(i * (w / 10) + 5, h - 5, QString::fromStdString(ss.str()));
			else
				painter.drawText(i * (w / 10) + 5, (0 - y_u) * (h / (y_d - y_u)) + 15, QString::fromStdString(ss.str()));

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
			if (i != 0)
			{
				painter.drawLine((i * (x_r - x_l) / 10 - x_l) * (w / (x_r - x_l)), 0, (i * (x_r - x_l) / 10 - x_l) * (w / (x_r - x_l)), h);
				std::stringstream ss;
				ss << i * ((x_r - x_l) / 10.f);	//x軸上數值
				if (y_u < 0 || y_d>0)
					painter.drawText((i * (x_r - x_l) / 10 - x_l) * (w / (x_r - x_l)) + 5, h - 5, QString::fromStdString(ss.str()));
				else
					painter.drawText((i * (x_r - x_l) / 10 - x_l) * (w / (x_r - x_l)) + 5, (0 - y_u) * (h / (y_d - y_u)) + 15, QString::fromStdString(ss.str()));
			}
		}
	}

	//draw equation

	Parser equation;
	for (auto model : Project3::getModelList())
	{
		painter.setPen(QPen(toQColor(model->getData().color), 2));

		equation.setInput(model->getData().equation.toStdString());
		int type = equation.type();

		QPointF lastPoint;
		QLineF lastLine;
		bool lock = false;

		if (type == 0)
		{
			equation.tranVar();
			for (double i = x_l; i < x_r; i += (x_r - x_l) / 500)
			{
				Variable setX("x", "x", i), getY("y", "y");
				int code = equation.calculate(setX, getY);			//設定變數和結果
				if (!code)
				{
					model->error(false);


					if (model->getData().visible)
					{
						double y = getY.num; //得到結果

						if (lastPoint.isNull())
							lastPoint = QPointF((i - x_l) * (w / (x_r - x_l)), (y - y_u) * (h / (y_d - y_u)));
						else
						{
							QPointF nowPoint((i - x_l) * (w / (x_r - x_l)), (y - y_u) * (h / (y_d - y_u)));
							QLineF nowLine(lastPoint, nowPoint);

							double degree = nowLine.angleTo(lastLine);
							//if (abs(i) <3)
								//qDebug() <<i <<' ' << degree;
							if (degree > 170 && degree < 190)	//判斷是否為斷層
								lock = !lock;


							if (!lock)
								painter.drawLine(nowLine);


							//if (abs(i) < 1);
								//qDebug() << "last: " << lastY << "| now: " << nowY;
							lastPoint = nowPoint;
							lastLine = nowLine;
						}
					}
				}
				else if (code == -1)
				{
					model->error(true);
					break;
				}
				else if (code == 1)
				{
					model->error(false);
				}

			}
		}
		else if (type == 1)
		{
			equation.tranVar();
			for (double i = y_d; i < y_u; i += (y_u - y_d) / 500)
			{
				Variable getX("x", "x"), setY("y", "y", i);
				int code = equation.calculate(setY, getX);			//設定變數和結果
				if (!code)
				{
					model->error(false);


					if (model->getData().visible)
					{
						double x = getX.num; //得到結果

						if (lastPoint.isNull())
							lastPoint = QPointF((x - x_l) * (w / (x_r - x_l)), (i - y_u) * (h / (y_d - y_u)));
						else
						{
							QPointF nowPoint((x - x_l) * (w / (x_r - x_l)), (i - y_u) * (h / (y_d - y_u)));
							QLineF nowLine(lastPoint, nowPoint);

							double degree = nowLine.angleTo(lastLine);
							//if (abs(i) <3)
								//qDebug() <<i <<' ' << degree;
							if (degree > 170 && degree < 190)	//判斷是否為斷層
								lock = !lock;


							if (!lock)
								painter.drawLine(nowLine);


							//if (abs(i) < 1);
								//qDebug() << "last: " << lastY << "| now: " << nowY;
							lastPoint = nowPoint;
							lastLine = nowLine;
						}
					}
				}
				else if (code == -1)
				{
					model->error(true);
					break;
				}
				else if (code == 1)
				{
					model->error(false);
				}
			}
		}
		else
		{
			bool equationError = equation.setVariable() == -1;
			Variable setX("x", "x"), getY("y", "y");
			equation.tranVar();
			int code = equation.calculate(setX, getY);
			model->error(code == -1 || equationError);
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
			double dx = delta.x() / w * (x_r - x_l), dy = delta.y() / h * (y_u - y_d);
			x_r -= dx;
			x_l -= dx;
			y_u += dy;
			y_d += dy;
		}
	}
	this->update();
}

void paintWidget::wheelEvent(QWheelEvent* event)
{
	//int mX = event->x(), mY = event->y();
	double dx = ((event->x() * (x_r - x_l) / this->width() + x_l)-(x_l+x_r)/2) * (0.3),
		dy = ((event->y() * (y_d - y_u) / this->height() + y_u)-(y_u+y_d)/2) * (0.3);
	if (event->delta() > 0)
	{
		scale /= 1.3;
		x_r /= 1.3;
		x_l /= 1.3;
		y_u /= 1.3;
		y_d /= 1.3;

		x_r += dx;
		x_l += dx;
		y_d += dy;
		y_u += dy;

		qDebug() << u8"上滾" << scale;
	}
	else
	{
		scale *= 1.3;
		x_r *= 1.3;
		x_l *= 1.3;
		y_u *= 1.3;
		y_d *= 1.3;

		x_r -= dx;
		x_l -= dx;
		y_d -= dy;
		y_u -= dy;

		qDebug() << u8"下滾" << scale;
	}
	this->update();
}

