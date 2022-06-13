#pragma once
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QListView>
#include <QIcon>
#include <QString>
#include <QDebug>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

#define RED "QLabel { background-color : red;}"
#define BLUE "QLabel { background-color : blue;}"
#define ORANGE "QLabel { background-color : orange;}"
#define GREEN "QLabel { background-color : green;}"
#define PURPLE "QLabel { background-color : purple;}"
#define LIME "QLabel { background-color : lime;}"
#define BROWN "QLabel { background-color : brown;}"

#define VISIBLE_PATH ":/Project3/uiIcons/visible_icon.png"
#define INVISIBLE_PATH ":/Project3/uiIcons/invisible_icon.png"
#define CLOSE_PATH ":/Project3/uiIcons/close_icon.png"

enum Color
{
	red,
	blue,
	orange,
	green,
	purple,
	lime,
	brown
};

struct EquationData
{
	Color color;
	bool visible;
	QString equation;
};
