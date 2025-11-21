#include "interface.h"
#include "file.h"
#include "explorer_files.h"

QWidget* explorerFiles(QPlainTextEdit *codeEditorInput, QWebEngineView* webView) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
		"color: white;"
	);
	newBloc->setFixedWidth(240);

	QVBoxLayout *layout = new VerticalBoxLayout(newBloc);

	Button *porjectNameTmp = new Button("My Project");
	porjectNameTmp->setStyleSheet(
		"QPushButton {"
		"   background-color: rgba(0, 120, 212, .3);"
		"   border: 1px solid rgba(0, 120, 212, 1);"
		"   color: white;"
		"   min-width: 200px;"
		"   padding: 8px 10px;"
		"   margin: 0;"
		"	text-align: left;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(0, 120, 212, 0.8);"
		"}"
	);
	layout->addWidget(porjectNameTmp, 0, Qt::AlignTop);

	for (int i = 0; i < 5; ++i) {
	Button *saveButton = new Button((std::string("fileName_") + std::to_string(i) + ".julia").c_str());
	saveButton->setStyleSheet(
		"QPushButton {"
		"   background-color: rgba(23, 23, 23, 1.0);"
		"   border: 1px solid rgba(23, 23, 23, 1);"
		"   color: white;"
		"   min-width: 200px;"
		"   padding: 5px 10px 5px 32px;"
		"   margin: 0;"
		"	text-align: left;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(31, 31, 31, 1.0);"
		"}"
	);
	layout->addWidget(saveButton, 0, Qt::AlignTop);
	}

	layout->addStretch();

	Button *saveButton = new Button("Sauvegarder");
	saveButton->setStyleSheet(
		"QPushButton {"
		"   background-color: rgba(0, 120, 212, 1);"
		"   border: 1px solid rgba(0, 120, 212, 1);"
		"   color: white;"
		"   min-width: 240px;"
		"   padding: 8px 10px;"
		"   margin: 0;"
		"	text-align: left;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(0, 120, 212, 0.8);"
		"}"
	);
	layout->addWidget(saveButton, 0, Qt::AlignTop);

	QObject::connect(saveButton, &Button::clicked, [codeEditorInput]() {
		save(codeEditorInput);
	});

	Button *syncButton = new Button("Sync");
	QObject::connect(syncButton, &QPushButton::clicked, [=](){
        webView->page()->toHtml([=](const QString &html){
            codeEditorInput->setPlainText(html);
        });
    });
    layout->addWidget(syncButton);

	return newBloc;
}