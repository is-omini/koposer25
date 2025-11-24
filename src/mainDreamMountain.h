#ifndef MAINDRMAPP_H
#define MAINDRMAPP_H

#include "include/windowDreamMountain.h"

#include <QWidget>
#include <QString>

class DreamMountain : public QWidget {
public:
	//TextEdit *codeEditorInput;
	//QWebEngineView *vueWeb;

	explicit DreamMountain(QWidget *parent = nullptr);

	// SETTER & GETTER
	void setCurrentPath(QString path);
	QString getCurrentPath();
private:
	// Buffers
	WindowDreamMountain *WindowDrMApp;

	//QVector<Button*> filesExplorerTab;
	//QVector<ButtonSvg*> filesExplorer;

	QString currentPath;
};
#endif