#include "Project3.h"

Color Project3::colorCount;
QList<ListModel*> Project3::list;

Project3::Project3(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    this->setGeometry(200, 200, 800, 480);
    srand(time(0));
    colorCount = (Color)(rand() % 7);


}

void Project3::on_addPushButton_clicked()
{
    
    auto item = new QListWidgetItem();
    ListModel* model = new ListModel();
    model->setEquationColor(colorCount);
    model->setRow(list.size());
    model->setParent(this);
   
    item->setSizeHint(model->sizeHint());

    ui.listWidget->addItem(item);
    ui.listWidget->setItemWidget(item, model);
    list.push_back(model);
}

void Project3::removeItem(int index)
{
    list.erase(list.begin() + index);
    delete ui.listWidget->item(index);

    for (int i = 0; i < list.size(); i++) {
        list[i]->setRow(i);
    }
}

QList<ListModel*> Project3::getModelList()
{
    return list;
}
