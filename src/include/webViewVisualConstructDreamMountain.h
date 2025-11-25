#ifndef WEBVIEWVISUALCONSTRUCTDRMAPP_H
#define WEBVIEWVISUALCONSTRUCTDRMAPP_H


#include "interfaceDreamMountain.h"

class WindowDreamMountain;

#include <QWidget>
#include <QString>
#include <QVBoxLayout>

class WVVisualConstructDrM : public QWidget {
public:
	explicit WVVisualConstructDrM(WindowDreamMountain *main,QWidget* parent = nullptr);

	void addLine(QString string) {
		qDebug() << string;
		Button *btn = new Button(string, nullptr, 0);
		QString colorText = "#ffffff"; // ou toute autre couleur
		if(string.contains("ERROR")) colorText = "#FF5F57";
		if(string.contains("WARNING")) colorText = "#FEBC2E";

		QString colorHover = "#1e1f22"; // ou toute autre couleur
		if(string.contains("ERROR")) colorHover = "#521D1A";
		if(string.contains("WARNING")) colorHover = "#52411A";

		btn->setStyleSheet(QString(R"(
			QPushButton {
				background-color: transparent;
				color: %1;
				border: none;
				text-align: left;
				border-radius: 4px;
				padding: 8px 14px;
			}
			QPushButton:hover {
				background-color: %2;
			}
		)").arg(colorText, colorHover));
		layoutConteneur->addWidget(btn);
	}

	void clearLine() {
		qDebug() << "CLEAR";

		if (layoutConteneur) {
			QLayoutItem *child;
			while ((child = layoutConteneur->takeAt(0)) != nullptr) {
				if (child->widget()) {
					delete child->widget();
				}
				delete child;
			}
		}

		layoutConteneur->addStretch();
	}
private:
	QVBoxLayout* layoutConteneur;

	WindowDreamMountain* windowParentApp;
};

#endif