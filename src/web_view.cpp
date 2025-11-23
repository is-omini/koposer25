#include "interface.h"
#include "web_view.h"

WebViewer::WebViewer(QWebEngineView* &webView, QPlainTextEdit* codeEditorInput, QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(
        "background-color: rgba(31,31,31,1);"
        "color: white;"
    );

    QVBoxLayout *layout = new VerticalBoxLayout(this);
    webView = new QWebEngineView(this);
    QObject::connect(webView, &QWebEngineView::loadFinished, [=](bool){
        webView->page()->runJavaScript("document.body.contentEditable = 'true';");
    });
    layout->addWidget(webView);
};