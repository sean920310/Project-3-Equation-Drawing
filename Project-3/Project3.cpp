#include "Project3.h"

Color Project3::colorCount;


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
    /*
    
    QWidget* model = new QWidget();
    QLabel* color = new QLabel();
    QLineEdit* lineEdit = new QLineEdit();
    QPushButton* showBtn = new QPushButton();
    QPushButton* closeBtn = new QPushButton();
    QHBoxLayout* modelLayout = new QHBoxLayout();

    //*color
    color->setStyleSheet(colorStyleSheet(colorCount));
    color->setMinimumSize(30, 30);

    //*lineEdit
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPixelSize(20);
    lineEdit->setFont(font);

    //*show
    if (1)
    {
        QIcon visible(VISIBLE_PATH);
        showBtn->setIcon(visible);
        showBtn->setIconSize(QSize(25, 25));
    }
    else
    {
        QIcon invisible(INVISIBLE_PATH);
        showBtn->setIcon(invisible);
    }

    //*close

    modelLayout->addWidget(color);
    modelLayout->addWidget(lineEdit);
    modelLayout->addWidget(showBtn);
    modelLayout->addWidget(closeBtn);
    
    modelLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    model->setLayout(modelLayout);
    */

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