#ifndef WEBVIEWVISUALCONSTRUCTDRMAPP_H
#define WEBVIEWVISUALCONSTRUCTDRMAPP_H


#include "interfaceDreamMountain.h"

#include <QWidget>
#include <QString>
#include <QVBoxLayout>

class WVVisualConstructDrM : public QWidget {
public:
	explicit WVVisualConstructDrM(QWidget* parent = nullptr);

	void addLine(QString string) {
		qDebug() << string;
		Button *btn = new Button(string, nullptr, 0);
		btn->setStyleSheet(R"(
			QPushButton {
				background-color: #1e1f22;
				border: 1px solid #1e1f22;
				color: white;
				padding: 8px 10px 8px 10px;
				margin: 0;
				text-align: left;
			}
		)");
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
};

#endif