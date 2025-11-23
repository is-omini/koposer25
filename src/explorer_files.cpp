#include "interface.h"
#include "file.h"
#include "explorer_files.h"

#include "ui_styles.h"

#include <QDebug>
#include <QScrollArea>

#include <QFileDialog>

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

ExplorerFiles::ExplorerFiles(
	DreamMountain* main,
	QPlainTextEdit *codeEditorInput,
	QWebEngineView* webView,
	DevelopmentTab* developmentTab,
	QWidget *parent) : QWidget(parent) {
	setFixedWidth(240);

	styleNormal = R"(
	QPushButton {
		background-color: #2c2d30;
		border: 1px solid #2c2d30;
		color: white;
		padding: 5px 10px 5px 32px;
		margin: 0;
		text-align: left;
	}
	QPushButton:hover {
		background-color: rgba(31,31,31,1);
	}
	)";

	styleSelected = R"(
	QPushButton {
		background-color: #44454a;
		border: 1px solid #44454a;
		color: white;
		padding: 5px 10px 5px 32px;
		margin: 0;
		text-align: left;
	}
	QPushButton:hover {
		background-color: #2c2d30);
	}
	)";

	developmentTabVar = developmentTab;
	this->dreamMountain = main;

	verticalBox = new VerticalBoxLayout(this);

	scroll = new QScrollArea(this);
	scroll->setWidgetResizable(true);	  // important pour le resize
	scroll->setFrameShape(QFrame::NoFrame); // option : enlever le cadre
	scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setStyleSheet(scrollBarWindow);

	contenaireExplorere = new QWidget();
	contenaireExplorere->setStyleSheet(
		"background-color: "+dreamMountain->windowBackgoundColor+";"
		"color: white;"
	);

	scroll->setWidget(contenaireExplorere);
	verticalBox->addWidget(scroll);
}

void ExplorerFiles::explorerListFiles(std::string path, QString titleProject) {
	dreamMountain->explorerAllButton.clear();
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
		background-color: #2c2d30;
		border: 1px solid #2c2d30;
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
		background-color: #44454a;
		border: 1px solid #44454a;
		color: white;
		padding: 5px 10px 5px 32px;
		margin: 0;
		text-align: left;
	}
	QPushButton:hover {
		background-color: #2c2d30);
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
	
	Button *projectMenuTitle = new Button(titleProject);
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
		newButton->setStyleSheet(styleNormal);
		dreamMountain->explorerAllButton.push_back(newButton);

		std::string fullPath = path + '/' + entry.path().filename().string();
		if (entry.is_directory()) {
			newButton->connect(newButton, &QPushButton::clicked, [=](){
				// Met à jour le chemin courant
				this->currentPath = QString::fromStdString(fullPath);

				// Ajoute à l'historique si nécessaire
				if (projectPathHistory.empty() || projectPathHistory.back() != fullPath) {
					projectPathHistory.push_back(fullPath);
				}

				// Recharge l’explorateur
				this->explorerListFiles(fullPath + "/");
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
				for (auto b : dreamMountain->explorerAllButton) {
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