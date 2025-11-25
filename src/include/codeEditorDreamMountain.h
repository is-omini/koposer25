#ifndef CODEEDITORDRMAPP_H
#define CODEEDITORDRMAPP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "system/textEditor.h"

class WindowDreamMountain;

class CodeEditorDreamMountain : public QWidget {
public:
	explicit CodeEditorDreamMountain(WindowDreamMountain *main,QWidget *parent = nullptr);

	TextEditor *getSystemEnfant() { return textEditorSystem; }
	//void setText(QString string) { textEditorSystem->setText(string); }
	QString getText() { return textEditorSystem->toPlainText(); }
	void setText(QString string) { textEditorSystem->setPlainText(string); }

	void updatePosition();

	void clearOverlay();

	WindowDreamMountain* getWindowParentApp();

	QPushButton* createButtonToOverlay(
		QString string = nullptr,
		QString Svg = nullptr,
		int svgSize = 12,
		QString css = nullptr
	);

	bool overlayCodeEditorIsVisible() { return menuDeroulantCodeEditor->isVisible(); }

	void appendButtonToOverlay(QPushButton* button) {
		menuDeroulantCodeEditorList->addWidget(button);
		button->show(); // Forcer le bouton à être visible
		menuDeroulantCodeEditor->adjustSize();
		menuDeroulantCodeEditor->show();
	}
private:
	TextEditor *textEditorSystem;
	QWidget* menuDeroulantCodeEditor;
	QVBoxLayout* menuDeroulantCodeEditorList;

	WindowDreamMountain* windowParentApp;
};

#endif