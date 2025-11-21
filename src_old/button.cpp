#include "button.h"

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