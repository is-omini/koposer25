#ifndef DEVELOPMENT_TAB_H
#define DEVELOPMENT_TAB_H

#include "interface.h"
#include <QSplitter>
#include <QPlainTextEdit>
#include <QWebEngineView>

class DevelopmentTab : public QSplitter {
    Q_OBJECT
public:
    explicit DevelopmentTab(
        QPlainTextEdit* &codeEditorInput,
        QWebEngineView* &webView,
        Qt::Orientation orientation,
        QWidget *parent = nullptr);
private:
    static QHBoxLayout *filesActiveList;
    void addButton(const QString &text, Button* &newButton) ;
};
#endif