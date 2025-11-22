#include "interface.h"
#include "file.h"
#include "explorer_files.h"
#include "code_editor.h"
#include "web_view.h"
#include "development_tab.h"

#include <QScrollArea>

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
    filesActiveList->addWidget(newButton);
}

void DevelopmentTab::updateViewer(const char *filePath, const char *fileName, int addNewButton) {
    const QString styleNormal = R"(
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

    const QString styleSelected = R"(
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

    char *text = read(filePath);
    codeEditorElement->setPlainText(QString::fromUtf8(text));
    free(text);

    QString qFileName = QString::fromUtf8(fileName);
    QString qFilePath = QString::fromUtf8(filePath);
    
    if(addNewButton == 1) {
        bool exists = false;
        for (auto *b : dreamMountain->tabDevAllButton) {
            if (b->attrID == qFileName) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            //std::cout << ":D" << std::endl;
            Button *newButton;
            addButton(qFileName, newButton);
            newButton->attrID = qFileName;
            newButton->attrPath = qFilePath;
            newButton->connect(newButton, &QPushButton::clicked, [
                qFilePath,
                qFileName,
                this,
                newButton,
                styleSelected,
                styleNormal
            ](){
                //dreamMountain->currentPath = qFilePath;
                dreamMountain->setCurrentPath(qFilePath);

                for (auto b : dreamMountain->explorerAllButton) {
                    if(b->attrPath == newButton->attrPath) {
                        b->setEnabled(false);
                        b->setStyleSheet(styleSelected);
                    } else {
                        b->setEnabled(true);
                        b->setStyleSheet(styleNormal);
                    }
                }

                DevelopmentTab::updateViewer(qFilePath.toUtf8().constData(), qFileName.toUtf8().constData(), 0);
            });
            dreamMountain->tabDevAllButton.push_back(newButton);
        }

        
    }

    if(
        (strstr(fileName, ".html") == nullptr)
        ||
        (strstr(fileName, ".htm") == nullptr)
    ) webViewer->hide();
    else webViewer->show();
}

DevelopmentTab::DevelopmentTab(
    DreamMountain* main,

    TextEdit* &codeEditorInput,
    QWebEngineView* &webView,
    Qt::Orientation orientation,
    QWidget *parent)
    : QSplitter(orientation, parent)
{
    setStyleSheet("QSplitter::handle { background: transparent; }");
    setContentsMargins(0,0,0,0);
    setHandleWidth(0);

    this->dreamMountain = main;

    QSplitter *v = new Splitter(Qt::Vertical);
    layoutEditorAndWebviewer = new Splitter(Qt::Horizontal);

    //
    codeEditor = new EditorCode(codeEditorInput);
    webViewer = new WebViewer(webView, codeEditorInput);

    codeEditorElement = codeEditorInput;
    webViewElement = webView;
    layoutEditorAndWebviewer->addWidget(codeEditor);
    layoutEditorAndWebviewer->addWidget(webViewer);
    layoutEditorAndWebviewer->setSizes({640, 400});
    webViewer->hide();
    //

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setFixedHeight(32); 
    scroll->setWidgetResizable(true);               // Le contenu peut s’adapter
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // vertical invisible
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // horizontal invisible
    scroll->setFrameShape(QFrame::NoFrame);         // pas de bord

    QWidget *bloc = new QWidget();
    bloc->setStyleSheet(
        "background-color: rgba(23,23,23,1);"
    );

    //
    filesActiveList = new HorizontalBoxLayout(bloc);
    filesActiveList->setContentsMargins(0, 0, 0, 0);
    filesActiveList->setSpacing(0);
    filesActiveList->addStretch();
    //

    bloc->setFixedHeight(32);

    scroll->setWidget(bloc);

    v->addWidget(layoutEditorAndWebviewer);
    v->addWidget(scroll);

    addWidget(v);
}