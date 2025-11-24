#include "interfaceDreamMountain.h"
	
ButtonSvg::ButtonSvg(const QString &text, QString svgBalise, int size, QWidget *parent)
	: QPushButton(text, parent)
{
	QSvgRenderer renderer(svgBalise.toUtf8());
	QPixmap pixmap(size, size);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	renderer.render(&painter);
	QIcon icon(pixmap);
	setIcon(icon);
	setIconSize(QSize(size, size));
};

Button::Button(
	const QString &text,
	QString svgBalise,
	int size,
	QWidget *parent
)
	: QPushButton(text, parent)
{
	QSvgRenderer renderer(svgBalise.toUtf8());
	QPixmap pixmap(size, size);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	renderer.render(&painter);
	QIcon icon(pixmap);
	setIcon(icon);
	setIconSize(QSize(size, size));
};