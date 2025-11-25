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

	void filesExplorerHistoryPush(std::string fullPath) {
		if (!filesExplorerHistory.empty() && filesExplorerHistory.back() == fullPath) return;
		filesExplorerHistory.push_back(fullPath);
	}
	void filesExplorerHistoryPop() {
		filesExplorerHistory.pop_back();
	}
	void filesExplorerHistoryClear() {
		filesExplorerHistory.clear();
	}

	std::string filesExplorerHistoryGetLast() {
		std::string path;
		if (filesExplorerHistory.empty()) {
			path = "/";
		} else {
			path = filesExplorerHistory.back();
			if (path.empty()) path = "/";
		}

		return path;
	}


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

		int lastSlash = currentProjectPath.lastIndexOf('/');
		QString lastSegment = currentProjectPath.mid(lastSlash + 1);

		CustomWindowBarDreamMountain->sourceBnC->setText(
			lastSegment
		);
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