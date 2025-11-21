#include "interface.h"
#include "file.h"
#include "explorer_files.h"
#include "code_editor.h"
#include "web_view.h"
#include "development_tab.h"

QHBoxLayout* DevelopmentTab::filesActiveList = nullptr;
void DevelopmentTab::addButton(const QString &text, Button* &newButton) {

    newButton = new Button(text);
    newButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(0, 120, 212, .2);"
        "   border: 1px solid rgba(0, 120, 212, 1);"
        "   color: white;"
        "   padding: 8px 10px;"
        "   margin: 0;"
        "   text-align: left;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(0, 120, 212, 0.8);"
        "}"
    );
    filesActiveList->addWidget(newButton, 0, Qt::AlignLeft);
}

DevelopmentTab::DevelopmentTab(
    QPlainTextEdit* &codeEditorInput,
    QWebEngineView* &webView,
    Qt::Orientation orientation,
    QWidget *parent)
    : QSplitter(orientation, parent)
{
    setStyleSheet("QSplitter::handle { background: transparent; }");
    setContentsMargins(0,0,0,0);
    setHandleWidth(0);

    QSplitter *v = new Splitter(Qt::Vertical);
    QSplitter *h = new Splitter(Qt::Horizontal);

    QWidget *blocB = new EditorCode(codeEditorInput);
    QWidget *blocC = new WebViewer(webView, codeEditorInput);
    h->addWidget(blocB);
    h->addWidget(blocC);

    QWidget *bloc = new QWidget();
    bloc->setStyleSheet(
        "background-color: rgba(23,23,23,1);"
    );
    bloc->setFixedHeight(32);

    filesActiveList = new HorizontalBoxLayout(bloc);

    Button *addedFile;
    addButton("index.html", addedFile);
    addedFile->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(0, 120, 212, 1);"
        "   border: 1px solid rgba(0, 120, 212, 1);"
        "   color: white;"
        "   padding: 8px 10px;"
        "   margin: 0;"
        "   text-align: left;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(0, 120, 212, 0.8);"
        "}"
    );
    //addButton("index.css");
    //addButton("index.js");

    QObject::connect(addedFile, &Button::clicked, [=]() {
        Button *addedFileButton;
        addButton("index.html", addedFileButton);
    });
    filesActiveList->addStretch();
    filesActiveList->setContentsMargins(0, 0, 0, 0);
    filesActiveList->setSpacing(0);

    v->addWidget(h);
    v->addWidget(bloc);

    addWidget(v);
}