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
	QString currentProjectPath;


	//TextEdit *codeEditorInput;
	//QWebEngineView *vueWeb;

	explicit WindowDreamMountain(QWidget *parent = nullptr);
	~WindowDreamMountain();

	void hideCustomWindowBar();
	void hideRedoundWindowBorder();
	void showRedoundWindowBorder();

	QString getCurrentFilePath() { return currentFilePath; }
	void setCurrentFilePath(QString path) {
		currentFilePath = path;
		qDebug() << currentFilePath;
	}

	QString getCurrentProjectPath() { return currentProjectPath; }
	void setCurrentProjectPath(QString path) {
		currentProjectPath = path;
		qDebug() << currentProjectPath;
	}

	AppContentDreamMountain *getAppContentDreamMountain() { return appContentDreamMountain; }
	CustomBarDreamMountain *getCustomWindowBarDreamMountain() { return CustomWindowBarDreamMountain; }

	AppContentDreamMountain *getAppContent() { return appContentDreamMountain; }
private:
	CustomBarDreamMountain *CustomWindowBarDreamMountain;
	AppContentDreamMountain *appContentDreamMountain;
	QWidget *centralBackgroundWindow;

	void saveWindowGeometry();
    void loadWindowGeometry();
protected:
	void changeEvent(QEvent *event) override;
	void closeEvent(QCloseEvent *event) override;
};
#endif