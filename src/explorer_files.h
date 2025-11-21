#ifndef EXPLORER_FILES_H
#define EXPLORER_FILES_H
#include <QWebEngineView>
#include "development_tab.h"

//QWidget* explorerFiles(QPlainTextEdit *codeEditorInput, QWebEngineView* webView, DevelopmentTab* developmentTab);
void explorerListFiles(std::string path, QWidget *newBloc, DevelopmentTab* developmentTab);


class ExplorerFiles : public QWidget {
    Q_OBJECT
private:
	DevelopmentTab* developmentTabVar = nullptr;
	QVBoxLayout *verticalBox = nullptr;
	QWidget *contenaireExplorere = nullptr;
	QVBoxLayout *layoutExplorerListItems = nullptr;

public:
	QVector<QPushButton*> allButtonsExplorer;
    explicit ExplorerFiles(
    	QPlainTextEdit *codeEditorInput,
		QWebEngineView* webView,
		DevelopmentTab* developmentTab,
		QWidget *parent = nullptr);

    void explorerListFiles(std::string path);
};

#endif