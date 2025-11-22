#ifndef DEVELOPMENT_TAB_H
#define DEVELOPMENT_TAB_H

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

    QSplitter *layoutEditorAndWebviewer;

    QVector<Button*> allButtonsTabEditors;

    explicit DevelopmentTab(
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