#ifndef EXPLORER_FILES_H
#define EXPLORER_FILES_H
#include "DreamMountain.h"

#include <QWebEngineView>
#include <QScrollArea>
#include "development_tab.h"

//QWidget* explorerFiles(QPlainTextEdit *codeEditorInput, QWebEngineView* webView, DevelopmentTab* developmentTab);
void explorerListFiles(std::string path, QWidget *newBloc, DevelopmentTab* developmentTab);


class ExplorerFiles : public QWidget {
    Q_OBJECT
private:
    DreamMountain* dreamMountain;

    QScrollArea *scroll;

	DevelopmentTab* developmentTabVar = nullptr;
	QVBoxLayout *verticalBox = nullptr;
	QWidget *contenaireExplorere = nullptr;
	QVBoxLayout *layoutExplorerListItems = nullptr;

public:
	QString styleNormal = R"(
	QPushButton {
		background-color: rgba(23,23,23,1);
		border: 1px solid rgba(23,23,23,1);
		color: white;
		padding: 5px 10px 5px 32px;
		margin: 0;
		text-align: left;
	}
	QPushButton:hover {
		background-color: rgba(31,31,31,1);
	}
	)";

	QString styleSelected = R"(
	QPushButton {
		background-color: rgba(0,120,212,0.3);
		border: 1px solid rgba(0,120,212,0.3);
		color: white;
		padding: 5px 10px 5px 32px;
		margin: 0;
		text-align: left;
	}
	QPushButton:hover {
		background-color: rgba(0,120,212,1.0);
	}
	)";

	QVector<QPushButton*> allButtonsExplorer;
    explicit ExplorerFiles(
        DreamMountain* dreamMountain,
    	QPlainTextEdit *codeEditorInput,
		QWebEngineView* webView,
		DevelopmentTab* developmentTab,
		QWidget *parent = nullptr);

    void explorerListFiles(std::string path);
    QWidget* TopExplorer();
	
	QString currentPath;

	std::vector<std::string> projectPathHistory;

	QString currentProjectPath;
	QString oldProjectPath;
};

#endif