#ifndef DEVELOPMENT_TAB_H
#define DEVELOPMENT_TAB_H
#include "DreamMountain.h"

#include "interface.h"
#include "code_editor.h"

#include <QSplitter>
#include <QPlainTextEdit>
#include <QWebEngineView>

#include <iostream>

class DevelopmentTab : public QSplitter {
    Q_OBJECT
public:
    TextEdit *codeEditorElement; 
    QWebEngineView *webViewElement;

    QWidget *codeEditor;
    QWidget *webViewer;


    QString currentPath;

    QSplitter *layoutEditorAndWebviewer;

    QVector<Button*> allButtonsTabEditors;
    DreamMountain* dreamMountain;

    explicit DevelopmentTab(
        DreamMountain* dreamMountain,
        TextEdit* &codeEditorInput,
        QWebEngineView* &webView,
        Qt::Orientation orientation,
        QWidget *parent = nullptr);

    void updateViewer(const char *filePath, const char *fileName, int addNewButton = 1);
private:

    static QHBoxLayout *filesActiveList;
    void addButton(const QString &text, Button* &newButton) ;
};
#endif