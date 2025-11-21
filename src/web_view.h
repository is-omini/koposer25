#ifndef WEB_VIEW_H
#define WEB_VIEW_H
#include <QWebEngineView>
#include <QPlainTextEdit>

class WebViewer : public QWidget {
    Q_OBJECT
public:
    explicit WebViewer(QWebEngineView* &webView, QPlainTextEdit* codeEditorInput, QWidget *parent = nullptr);
};
#endif