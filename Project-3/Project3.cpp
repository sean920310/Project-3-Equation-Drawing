#include "Project3.h"

Project3::Project3(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    model = new QStringListModel(this);

}

void Project3::on_addPushButton_clicked()
{
    auto newText = new QLineEdit(ui.listWidget);
    newText->setMinimumSize(0, 40);
    QFont font("Microsoft JhengHei UI",20);
    newText->setFont(font);
    auto item = new QListWidgetItem("", ui.listWidget);
    ui.listWidget->setItemWidget(item, newText);

    int row = model->rowCount();   // model = new QStringListModel
    model->insertRow(row);

    ui.listView->setModel(model);

    //QMessageBox::warning(this, u8"警告", u8"測試警告");
}
