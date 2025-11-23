#ifndef DREAMMOUNTAIN_H
#define DREAMMOUNTAIN_H

#include <QWidget>
#include <QMainWindow>
#include <QWebEngineView>

#include "interface.h"

#include "code_editor.h"

class DreamMountain : public QMainWindow {
public:
	QString blueColor; // #3477f7
	QString windowBackgoundColor; // #2c2d30
	QString contenaireBackgoundColor; // #1e1f22
	QString inputBackgoundColor; // #1e1f22
	QString borderColor; // #5c5d63
	
	TextEdit *codeEditorInput;
	QWebEngineView *vueWeb;

	QVector<Button*> tabDevAllButton; // Gere la tabulation en bas à droite
	QVector<ButtonSvg*> explorerAllButton;

	QString currentPath;
	explicit DreamMountain(QWidget *parent = nullptr);

	void setCurrentPath(QString path);
private:
	QHBoxLayout *filesActiveList;
	QWidget window;
	// attr : #58a8f5
	// base : #ce8e6d
	// othes : #6bb38a
};
#endif