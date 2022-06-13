#pragma once
#include <QWidget>
#include "MainHeader.h"

namespace Ui { class ListModel; };
class Project3;

class ListModel : public QWidget
{
	Q_OBJECT

public:
	ListModel(QWidget* parent = Q_NULLPTR);
	~ListModel();

	void setParent(Project3* parent);
	void setEquationColor(Color& color);
	void setRow(int num);
	int getRow();
	EquationData getData();

private slots:
	void on_showBtn_clicked();
	void on_closeBtn_clicked();

private:
	Ui::ListModel* ui;
	Project3* parent;
	bool visible = true;
	Color color;
	int row;
};

