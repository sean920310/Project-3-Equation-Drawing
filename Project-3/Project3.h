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
    void removeItem(QListWidgetItem& toRemove);

private slots:
    void on_addPushButton_clicked();
    void on_listWidget_itemChange();

private:
    Ui::Project3Class ui;
    QList<QListWidgetItem*> list;
    static Color colorCount;
};
