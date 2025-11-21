#include "interface.h"

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent)
    : QSplitter(orientation, parent)
{
	setStyleSheet("QSplitter::handle { background: transparent; }");
	setContentsMargins(0,0,0,0);
	setHandleWidth(0);
};

VerticalBoxLayout::VerticalBoxLayout(QWidget *parent)
    : QVBoxLayout(parent)
{
	setContentsMargins(0,0,0,0);
	setSpacing(0);
};

HorizontalBoxLayout::HorizontalBoxLayout(QWidget *parent)
    : QHBoxLayout(parent)
{
	setContentsMargins(0,0,0,0);
	setSpacing(0);
	//addStretch();
};

Button::Button(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
	setStyleSheet(
		"QPushButton {"
		"   background-color: rgba(0, 120, 212, 1);"
		"   border: 1px solid rgba(0, 120, 212, 1);"
		"   color: white;"
		"   min-width: 100px;"
		"   padding: 8px 10px;"
		"   margin: 0;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(0, 120, 212, 0.8);"
		"}"
	);
};