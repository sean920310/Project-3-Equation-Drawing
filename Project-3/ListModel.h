#pragma once
#include <QWidget>

#include "MainHeader.h"

namespace Ui { class ListModel; };

class ListModel : public QWidget
{
	Q_OBJECT

public:
	ListModel(QWidget* parent = Q_NULLPTR);
	~ListModel();

	void setEquationColor(Color& color);
	EquationData getData();

private slots:
	void on_showBtn_clicked();
	void on_closeBtn_clicked();

private:
	Ui::ListModel* ui;
	bool visible = true;
	Color color;
};
