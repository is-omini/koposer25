#ifndef STATUTAPPBARDRMAPP_H
#define STATUTAPPBARDRMAPP_H

class WindowDreamMountain;

#include <QWidget>
#include <QPushButton>

#include <QHBoxLayout>

#include "interfaceDreamMountain.h"

class StatutAppBarDreamMountain : public QWidget {
public:
	explicit StatutAppBarDreamMountain(WindowDreamMountain *main, QWidget *parent = nullptr);

	Button* AppendButtonList(
		QString string = nullptr,
		QString Svg = nullptr,
		int svgSize = 12,
		QString css = nullptr
	);

	void UpdateButtonListLeft();

	void appendLeftButtonList(Button* btn) { leftButtonList.append(btn); };

	bool isFileStatusBar(std::string filePath) {
		bool exists = false;
		for (auto *b : leftButtonList) {
			if (b->attrPath == QString::fromStdString(filePath)) {
				exists = true;
				break;
			}
		}
		return exists;
	}

private:
	QList<Button*> leftButtonList;

	QWidget* widgetLeftStatutAppBarButtonList;
	QHBoxLayout* layoutLeftStatutAppBarButtonList;
	QWidget* widgetRightStatutAppBarButtonList;
	QHBoxLayout* layoutRightStatutAppBarButtonList;

	QWidget *statutAppBarDreamMountain;



	WindowDreamMountain *windowParentApp;
};

#endif