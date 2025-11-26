#ifndef INTERFACEDRMAPP_H
#define INTERFACEDRMAPP_H

#include <QPushButton>
#include <QSvgRenderer>
#include <QPainter>

class ButtonSvg : public QPushButton {
	Q_OBJECT
public:

	QString getTexte() {
		return "Hello World";
	}

	QString attrID;
	QString attrPath;
	
	explicit ButtonSvg(
		const QString &text = nullptr,
		QString svgBalise = nullptr,
		int size = 8,
		QWidget *parent = nullptr);
};

class Button : public QPushButton {
	Q_OBJECT
public:
	QString attrID;
	QString attrPath;

	QString buttonTexte;

	QString getTexte() {
		return buttonTexte;
	}

	QVector<Button*> getContextMenu() {
		return contextMenuButtons;
	}
	
	explicit Button(
		const QString &text = nullptr,
		QString svgBalise = nullptr,
		int size = 8,
		QWidget *parent = nullptr
	);

	QString getSvg() {
		return "";
	}

	void append(Button* b) {
		contextMenuButtons.append(b);
	}

private:
	QVector<Button*> contextMenuButtons;
};

#endif