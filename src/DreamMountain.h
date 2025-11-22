#ifndef DREAMMOUNTAIN_H
#define DREAMMOUNTAIN_H

#include <QWidget>
#include <QWebEngineView>

#include "interface.h"

#include "code_editor.h"

class DreamMountain {
public:
	TextEdit *codeEditorInput;
	QWebEngineView *vueWeb;

	QVector<Button*> tabDevAllButton; // Gere la tabulation en bas à droite
	QVector<Button*> explorerAllButton;

	QString currentPath;
	DreamMountain();

	void setCurrentPath(QString path);
private:
	QWidget window;
};
#endif