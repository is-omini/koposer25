#ifndef EXPLORER_FILES_H
#define EXPLORER_FILES_H
#include "DreamMountain.h"

#include <QWebEngineView>
#include "development_tab.h"

//QWidget* explorerFiles(QPlainTextEdit *codeEditorInput, QWebEngineView* webView, DevelopmentTab* developmentTab);
void explorerListFiles(std::string path, QWidget *newBloc, DevelopmentTab* developmentTab);


class ExplorerFiles : public QWidget {
    Q_OBJECT
private:
    DreamMountain* dreamMountain;

	DevelopmentTab* developmentTabVar = nullptr;
	QVBoxLayout *verticalBox = nullptr;
	QWidget *contenaireExplorere = nullptr;
	QVBoxLayout *layoutExplorerListItems = nullptr;
	QString currentPath;

	std::vector<std::string> projectPathHistory;

	QString currentProjectPath;
	QString oldProjectPath;

public:
	QVector<QPushButton*> allButtonsExplorer;
    explicit ExplorerFiles(
        DreamMountain* dreamMountain,
    	QPlainTextEdit *codeEditorInput,
		QWebEngineView* webView,
		DevelopmentTab* developmentTab,
		QWidget *parent = nullptr);

    void explorerListFiles(std::string path);
    void ExplorerFocusButton(QString path);
};

#endif