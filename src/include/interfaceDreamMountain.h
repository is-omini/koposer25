#ifndef INTERFACEDRMAPP_H
#define INTERFACEDRMAPP_H

#include <QPushButton>
#include <QSvgRenderer>
#include <QPainter>

class ButtonSvg : public QPushButton {
	Q_OBJECT
public:
	QString attrID;
	QString attrPath;
	
	explicit ButtonSvg(const QString &text = nullptr, QString svgBalise = nullptr, int size = 8, QWidget *parent = nullptr);
};

class Button : public QPushButton {
	Q_OBJECT
public:
	QString attrID;
	QString attrPath;
	
	explicit Button(
		const QString &text = nullptr,
		QString svgBalise = nullptr,
		int size = 8,
		QWidget *parent = nullptr
	);
};

#endif