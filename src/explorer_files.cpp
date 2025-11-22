#include "interface.h"
#include "file.h"
#include "explorer_files.h"

#include <QDebug>
#include <QScrollArea>

#include <QFileDialog>

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

void createButtonForExplorer(QString svgBalise, Button* &projectButton) {
	projectButton = new Button();
	projectButton->setSvg(svgBalise, 16, 16);
	projectButton->setStyleSheet(
		"QPushButton {"
		"   background-color: rgba(0, 120, 212, 1.0);"
		"	border: none;"
		"   color: white;"
		"   padding: 8px 8px;"
		"	width: 16px;"
		"	height: 16px;"
		"   margin: 0;"
		"	text-align: center;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(0, 120, 212, 0.6);"
		"}"
	);
}

ExplorerFiles::ExplorerFiles(
	QPlainTextEdit *codeEditorInput,
	QWebEngineView* webView,
	DevelopmentTab* developmentTab,
	QWidget *parent) : QWidget(parent) {
	setFixedWidth(240);

	developmentTabVar = developmentTab;

	QScrollArea *scroll = new QScrollArea(this);
	scroll->setWidgetResizable(true);	  // important pour le resize
	scroll->setFrameShape(QFrame::NoFrame); // option : enlever le cadre
	scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	contenaireExplorere = new QWidget();
	contenaireExplorere->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
		"color: white;"
	);

	// Crée un layout vertical pour ExplorerFiles
	verticalBox = new VerticalBoxLayout(this);
	QWidget *projectButtons = new QWidget();
	projectButtons->setStyleSheet(
		"background-color: rgba(23, 23, 23, 1);"
		"border: 1px solid rgba(0, 120, 212, 1);"
	);
	QHBoxLayout *layoutExplorerProjectActionButtons = new HorizontalBoxLayout(projectButtons);
	///
	Button *projectImportFile = new Button();
	createButtonForExplorer(R"(
	<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
	<path d="M240-80q-33 0-56.5-23.5T160-160v-640q0-33 23.5-56.5T240-880h320l240 240v240h-80v-200H520v-200H240v640h360v80H240Zm638 15L760-183v89h-80v-226h226v80h-90l118 118-56 57Zm-638-95v-640 640Z"/>
	</svg>
	)", projectImportFile);
	QObject::connect(projectImportFile, &Button::clicked, [codeEditorInput]() {
		open(codeEditorInput);
	});
	layoutExplorerProjectActionButtons->addWidget(projectImportFile);
	///
	Button *projectImportFolder = new Button();
	createButtonForExplorer(R"(
	<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
	<path d="M160-160q-33 0-56.5-23.5T80-240v-480q0-33 23.5-56.5T160-800h240l80 80h320q33 0 56.5 23.5T880-640H447l-80-80H160v480l96-320h684L837-217q-8 26-29.5 41.5T760-160H160Zm84-80h516l72-240H316l-72 240Zm0 0 72-240-72 240Zm-84-400v-80 80Z"/>
	</svg>
	)", projectImportFolder);
	QObject::connect(projectImportFolder, &Button::clicked, [projectButtons, this]() {
		QString dossier = QFileDialog::getExistingDirectory(
			projectButtons,
			"Choisir un dossier"
		);
		if(!dossier.isEmpty()) this->explorerListFiles(
			dossier.toStdString() + "/"
		);
	});
	layoutExplorerProjectActionButtons->addWidget(projectImportFolder);
	///
	Button *projectSaveButton = new Button();
	createButtonForExplorer(R"(
	<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
	<path d="M840-680v480q0 33-23.5 56.5T760-120H200q-33 0-56.5-23.5T120-200v-560q0-33 23.5-56.5T200-840h480l160 160Zm-80 34L646-760H200v560h560v-446ZM480-240q50 0 85-35t35-85q0-50-35-85t-85-35q-50 0-85 35t-35 85q0 50 35 85t85 35ZM240-560h360v-160H240v160Zm-40-86v446-560 114Z"/>
	</svg>
	)", projectSaveButton);
	QObject::connect(projectSaveButton, &Button::clicked, [codeEditorInput, this]() {
		save(codeEditorInput, this->currentPath);
	});
	layoutExplorerProjectActionButtons->addWidget(projectSaveButton);
	///
	verticalBox->addWidget(projectButtons, 0, Qt::AlignTop);
	layoutExplorerProjectActionButtons->addStretch();

	explorerListFiles("/Users/julie/Documents/project-dev/koposer25/src/");

	scroll->setWidget(contenaireExplorere);
	verticalBox->addWidget(scroll);
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
	
	Button *projectMenuTitle = new Button("My project-dev");
	projectMenuTitle->setStyleSheet(
		"QPushButton {"
		"   background-color: rgba(0, 120, 212, 0.3);"
		"   border: 1px solid rgba(0, 120, 212, 1.0);"
		"   color: white;"
		"   padding: 8px 8px;"
		"	width: 20px;"
		"	height: 20px;"
		"   margin: 0;"
		"	text-align: left;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(0, 120, 212, 0.8);"
		"}"
	);
	layoutExplorerListItems->addWidget(projectMenuTitle);
	
	for (const auto& entry : entries) {
		Button *newButton = new Button(
			QString::fromStdString(entry.path().filename().string())
		);
		newButton->attrPath = QString::fromStdString(path + '/' + entry.path().filename().string());
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
				this->currentPath = QString::fromStdString(fullPath);
				newButton->setEnabled(false);
				newButton->setStyleSheet(styleSelected);
				for (auto b : this->allButtonsExplorer) {
					if(b == newButton) continue;
					b->setEnabled(true);
					b->setStyleSheet(styleNormal);
				}
				developmentTabVar->updateViewer(fullPath.c_str(), entry.path().filename().string().c_str());
				qDebug() << "Hello";
				qDebug() << this->currentPath;
			});
		}

		layoutExplorerListItems->addWidget(newButton, 0, Qt::AlignTop);
	}
	layoutExplorerListItems->addStretch();
}