#include "interface.h"
#include "file.h"
#include "explorer_files.h"
#include "code_editor.h"
#include "web_view.h"
#include "development_tab.h"

#include <cstring>

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

void DevelopmentTab::updateViewer(const char *files) {
    std::cout << "Hello World!" << std::endl;
    char *text = read(files);
    codeEditorElement->setPlainText(QString::fromUtf8(text));
    free(text);

    if(
        (strstr(files, ".html") == nullptr)
        ||
        (strstr(files, ".htm") == nullptr)
    ) webViewer->hide();
    else webViewer->show();
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
    layoutEditorAndWebviewer = new Splitter(Qt::Horizontal);

    //
    codeEditor = new EditorCode(codeEditorInput);
    webViewer = new WebViewer(webView, codeEditorInput);

    codeEditorElement = codeEditorInput;
    webViewElement = webView;

    layoutEditorAndWebviewer->addWidget(codeEditor);
    layoutEditorAndWebviewer->addWidget(webViewer);
    // 

    QWidget *bloc = new QWidget();
    bloc->setStyleSheet(
        "background-color: rgba(23,23,23,1);"
    );
    bloc->setFixedHeight(32);

    //
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
    QObject::connect(addedFile, &Button::clicked, [=]() {
        Button *addedFileButton;
        addButton("index.html", addedFileButton);
    });
    filesActiveList->addStretch();
    filesActiveList->setContentsMargins(0, 0, 0, 0);
    filesActiveList->setSpacing(0);
    //

    v->addWidget(layoutEditorAndWebviewer);
    v->addWidget(bloc);
    addWidget(v);
}