#include "ListModel.h"
#include "Project3.h"
#include "ui_ListModel.h"

QString colorStyleSheet(Color& color)
{
    switch (color)
    {
    case red:
        color = blue;
        return RED;
        break;
    case blue:
        color = orange;
        return BLUE;
        break;
    case orange:
        color = green;
        return ORANGE;
        break;
    case green:
        color = purple;
        return GREEN;
        break;
    case purple:
        color = lime;
        return PURPLE;
        break;
    case lime:
        color = brown;
        return LIME;
        break;
    case brown:
        color = red;
        return BROWN;
        break;
    default:
        color = blue;
        return RED;
        break;
    }
}

ListModel::ListModel(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ListModel();
	ui->setupUi(this);
    //showBtn
    QIcon showIcon(INVISIBLE_PATH);
    ui->showBtn->setIcon(showIcon);
        
    //closeBtn
    QIcon closeIcon(CLOSE_PATH);
    ui->closeBtn->setIcon(closeIcon);

    
}

ListModel::~ListModel()
{
	delete ui;
}

void ListModel::setParent(Project3* parent)
{
    this->parent = parent;
}

void ListModel::setEquationColor(Color& color)
{
    this->color = color;
    ui->label->setStyleSheet(colorStyleSheet(color));
}

void ListModel::setRow(int num)
{
    this->row = num;
}

int ListModel::getRow()
{
    return this->row;
}

EquationData ListModel::getData()
{
    EquationData data;
    data.color = color;
    data.visible = visible;
    data.equation = ui->lineEdit->text();

    return data;
}

void ListModel::on_showBtn_clicked()
{
    visible = !visible;
    if (!visible)
    {
        QIcon icon(VISIBLE_PATH);
        ui->showBtn->setIcon(icon);
    }
    else
    {
        QIcon icon(INVISIBLE_PATH);
        ui->showBtn->setIcon(icon);
    }
    qDebug() << getData().equation;
}

void ListModel::on_closeBtn_clicked()
{
    this->parent->removeItem(row);
    this->~ListModel();
}
