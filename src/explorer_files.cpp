#include "interface.h"
#include "file.h"
#include "explorer_files.h"

#include <QDebug>
#include <QScrollArea>

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

ExplorerFiles::ExplorerFiles(
	QPlainTextEdit *codeEditorInput,
	QWebEngineView* webView,
	DevelopmentTab* developmentTab,
	QWidget *parent) : QWidget(parent) {
	setFixedWidth(240);

	developmentTabVar = developmentTab;

	QScrollArea *scroll = new QScrollArea(this);
	scroll->setWidgetResizable(true);      // important pour le resize
	scroll->setFrameShape(QFrame::NoFrame); // option : enlever le cadre
	scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	contenaireExplorere = new QWidget();
	contenaireExplorere->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
		"color: white;"
	);

	// Crée un layout vertical pour ExplorerFiles
	verticalBox = new VerticalBoxLayout(this);
	explorerListFiles("/Users/julie/Documents/project-dev/koposer25/src/");

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

	QObject::connect(saveButton, &Button::clicked, [codeEditorInput]() {
		save(codeEditorInput);
	});

	Button *syncButton = new Button("Sync");
	QObject::connect(syncButton, &QPushButton::clicked, [=](){
		webView->page()->toHtml([=](const QString &html){
			codeEditorInput->setPlainText(html);
		});
	});
	scroll->setWidget(contenaireExplorere);
	verticalBox->addWidget(scroll);
	verticalBox->addWidget(syncButton);
	verticalBox->addWidget(saveButton);
}

void ExplorerFiles::explorerListFiles(std::string path) {
	allButtonsExplorer.clear();
	if (layoutExplorerListItems) {
		qDebug() << "DELETE !!!!!!";
		QLayoutItem *child;
		while ((child = layoutExplorerListItems->takeAt(0)) != nullptr) {
			if (child->widget()) {
				delete child->widget();  // supprime le widget
			}
			delete child; // supprime l’item du layout
		}
		delete layoutExplorerListItems;
		layoutExplorerListItems = nullptr;
	}	


	const QString styleNormal = R"(
	QPushButton {
	    background-color: rgba(23,23,23,1);
	    border: 1px solid rgba(23,23,23,1);
	    color: white;
	    min-width: 200px;
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
	    min-width: 200px;
	    padding: 5px 10px 5px 32px;
	    margin: 0;
	    text-align: left;
	}
	QPushButton:hover {
	    background-color: rgba(0,120,212,1.0);
	}
	)";

	std::vector<fs::directory_entry> entries;
	//TRIER
	for (const auto& entry : fs::directory_iterator(path)) {
		entries.push_back(entry);
	}
	std::sort(entries.begin(), entries.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
		if (a.is_directory() && !b.is_directory()) return true;
		if (!a.is_directory() && b.is_directory()) return false;
		return a.path().filename().string() < b.path().filename().string();
	});
	//TRIER

	layoutExplorerListItems = new VerticalBoxLayout(contenaireExplorere);
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
	layoutExplorerListItems->addWidget(porjectNameTmp, 0, Qt::AlignTop);

	
	for (const auto& entry : entries) {
		Button *newButton = new Button(
			QString::fromStdString(entry.path().filename().string())
		);
		newButton->setStyleSheet(
			styleNormal
		);
		allButtonsExplorer.push_back(newButton);

		std::string fullPath = path + '/' + entry.path().filename().string();
		if (entry.is_directory()) {
			newButton->connect(newButton, &QPushButton::clicked, [=](){
				ExplorerFiles::explorerListFiles(fullPath);
			});
		} else {
			newButton->connect(newButton, &QPushButton::clicked, [
				styleNormal,
				styleSelected,
				entry,
				fullPath,
				newButton,
				this
			](){
				newButton->setEnabled(false);
				newButton->setStyleSheet(styleSelected);
				for (auto b : this->allButtonsExplorer) {
					if(b == newButton) continue;
					b->setEnabled(true);
					b->setStyleSheet(styleNormal);
				}
				developmentTabVar->updateViewer(fullPath.c_str(), entry.path().filename().string().c_str());
				qDebug() << "Hello";
			});
		}

		layoutExplorerListItems->addWidget(newButton, 0, Qt::AlignTop);
	}
	layoutExplorerListItems->addStretch();
}