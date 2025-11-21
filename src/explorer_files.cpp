#include "interface.h"
#include "file.h"
#include "explorer_files.h"

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

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

	// Contenaires files listes
	// Fait une fonction qui génere ça !!!
	layout->addWidget(porjectNameTmp, 0, Qt::AlignTop);
	std::string path = "/Users/julie/Documents/project-dev/koposer25/src/"; // ATTR_PATH de la fonction
	for (const auto& entry : fs::directory_iterator(path)) {
		//entry.path().filename().string()
		Button *saveButton = new Button(
			QString::fromStdString(entry.path().filename().string())
		);
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

		saveButton->connect(saveButton, &QPushButton::clicked, [=](){
			std::string fullPath = path + entry.path().filename().string();
			char *text = read(fullPath.c_str());
			codeEditorInput->setPlainText(QString::fromUtf8(text));
			//std::cout << text << std::endl;
			free(text);
		});

		layout->addWidget(saveButton, 0, Qt::AlignTop);
	}
	layout->addStretch();
	// Contenaires files listes

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