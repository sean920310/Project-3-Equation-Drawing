#pragma once

#include <QtWidgets/QWidget>
#include "ui_Project3.h"
#include <QMessageBox>
#include <QPainter>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <QStringListModel>
#include "paintWidget.h"

namespace Ui { class Project3; };

class Project3 : public QWidget
{
    Q_OBJECT

public:
    Project3(QWidget *parent = Q_NULLPTR);

private slots:
    void on_addPushButton_clicked();

private:
    Ui::Project3Class ui;
    QStringListModel* model;
};
