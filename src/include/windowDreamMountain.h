#ifndef WINDOWDRMAPP_H
#define WINDOWDRMAPP_H

#include "customBarDreamMountain.h"
#include "appContentDreamMountain.h"

#include <QMainWindow>

#include <cstring>
#include <QVector>
#include <QPushButton>

class WindowDreamMountain : public QMainWindow {
public:
	//tmp
	QString porjectName;
	QVector<QPushButton*> filesExplorerTab;
	QVector<QPushButton*> filesExplorer;
	std::vector<std::string> filesExplorerHistory;
	QString currentPath;
	QString currentFilePath;


	//TextEdit *codeEditorInput;
	//QWebEngineView *vueWeb;

	explicit WindowDreamMountain(QWidget *parent = nullptr);

	void hideCustomWindowBar();
	void hideRedoundWindowBorder();
	void showRedoundWindowBorder();

	QString getCurrentFilePath() { return currentFilePath; }
	void setCurrentFilePath(QString path) { currentFilePath = path; }

	AppContentDreamMountain *getAppContentDreamMountain() { return appContentDreamMountain; }
	CustomBarDreamMountain *getCustomWindowBarDreamMountain() { return CustomWindowBarDreamMountain; }

	AppContentDreamMountain *getAppContent() { return appContentDreamMountain; }
private:
	CustomBarDreamMountain *CustomWindowBarDreamMountain;
	AppContentDreamMountain *appContentDreamMountain;

	QWidget *centralBackgroundWindow;
protected:
	void changeEvent(QEvent *event) override;
};
#endif