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

void Button::setSvg(QString svg, int w, int h) {
	QSvgRenderer renderer(svg.toUtf8());
	QPixmap pixmap(w, h);
	pixmap.fill(Qt::transparent);         // fond transparent
	QPainter painter(&pixmap);
	renderer.render(&painter);
	QIcon icon(pixmap);  // chemin vers ton fichier SVG
	this->setIcon(icon);
	this->setIconSize(QSize(w, h));
};