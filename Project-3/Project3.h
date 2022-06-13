#pragma once

#include <QtWidgets/QWidget>
#include "ui_Project3.h"
#include "paintWidget.h"
#include "ListModel.h"
#include "MainHeader.h"

namespace Ui { class Project3; };

struct CustomData
{
    Color color;
    QString equation;
    bool show;
};

class Project3 : public QWidget
{
    Q_OBJECT

public:
    Project3(QWidget *parent = Q_NULLPTR);
    void removeItem(int index);

private slots:
    void on_addPushButton_clicked();

private:
    Ui::Project3Class ui;
    QList<ListModel*> list;
    static Color colorCount;
};
