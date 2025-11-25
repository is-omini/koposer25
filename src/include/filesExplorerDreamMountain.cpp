#include "filesExplorerDreamMountain.h"
#include "windowDreamMountain.h"
#include "colorDreamMountain.h"
#include "iconDreamMountain.h"

#include "interfaceDreamMountain.h"

#include "system/fileExplorerEngine.h"
#include "system/fileSortingAlgorithm.h"

#include <QFileDialog>
#include <QDir>

#include <QMenu>
#include <QMessageBox>

#include <QInputDialog>

void FilesExplorerDreamMountain::clearLayoutExplorerListItems() {
	//windowParentApp->filesExplorerHistory.clear();
	if (layoutExplorerListItems) {
		QLayoutItem *child;
		while ((child = layoutExplorerListItems->takeAt(0)) != nullptr) {
			if (child->widget()) {
				delete child->widget();
			}
			delete child;
		}
		delete layoutExplorerListItems;
		layoutExplorerListItems = nullptr;
	}
}


void FilesExplorerDreamMountain::updateListFilesPoject(std::string pathExplorer, QString titleProject) {
	windowParentApp->porjectName = titleProject;
	clearLayoutExplorerListItems();

	layoutExplorerListItems = new QVBoxLayout(contenaireExplorere);
	layoutExplorerListItems->setContentsMargins(0,0,0,0);
	layoutExplorerListItems->setSpacing(0);

	FileSortingAlgorithm *SortingPathFiles = new FileSortingAlgorithm(pathExplorer);

	for (const auto& entry : SortingPathFiles->entries) {
		std::string fullPath = pathExplorer + '/' + entry.path().filename().string();

		QString buttonIcon = iconFile;
		if (entry.is_directory()) buttonIcon = iconFolder;

		Button *newButton = new Button(
			QString::fromStdString(entry.path().filename().string()),
			buttonIcon,
			16
		);
		newButton->attrPath = QString::fromStdString(pathExplorer + '/' + entry.path().filename().string());
		newButton->setStyleSheet(styleButonExplorerFileNormal);
		newButton->connect(newButton, &QPushButton::clicked, [=](){
			if (entry.is_directory()) {
				qDebug() << "/::" << pathExplorer;
				windowParentApp->filesExplorerHistoryPush(pathExplorer);

				QDir dir(QString::fromStdString(fullPath));
				if(dir.exists()) updateListFilesPoject(fullPath + "/", titleProject);
			} else {
				openFile(windowParentApp, fullPath);
				windowParentApp->setCurrentFilePath(QString::fromStdString(fullPath));
			}
		});
		layoutExplorerListItems->addWidget(newButton, 0, Qt::AlignTop);


		Button *c1 = new Button("Ouvrir");
		c1->connect(c1, &QPushButton::clicked, [=](){
			if (entry.is_directory()) {
				windowParentApp->filesExplorerHistoryPush(pathExplorer);

				QDir dir(QString::fromStdString(fullPath));
				if(dir.exists()) updateListFilesPoject(fullPath + "/", titleProject);
			}
			else {
				openFile(windowParentApp, fullPath);
				windowParentApp->setCurrentFilePath(QString::fromStdString(fullPath));
			}
		});
		newButton->append(c1);
		Button *c2 = new Button("Renommer");
		c2->connect(c2, &QPushButton::clicked, [=](){
			bool ok;
			QString newName = QInputDialog::getText(
				this,
				"Renommer",
				"Nouveau nom :",
				QLineEdit::Normal,
				QString::fromStdString(entry.path().filename().string()),
				&ok
			);
			if (ok && !newName.isEmpty()) {
				/* try {
					fs::rename(fullPath, fs::path(fullPath).parent_path() / newName.toStdString());
					//this->explorerListFiles(path);
					updateListFilesPoject(fullPath, titleProject);
				} catch (const fs::filesystem_error& e) {
					QMessageBox::warning(this, "Erreur", e.what());
				} */
			}
		});
		newButton->append(c2);
		Button *c3 = new Button("Supprimer");
		c3->connect(c3, &QPushButton::clicked, [=](){
			QMessageBox::StandardButton reply = QMessageBox::question(
				this, "Supprimer",
				QString("Voulez-vous vraiment supprimer '%1'?").arg(newButton->text()),
				QMessageBox::Yes | QMessageBox::No
			);
			if (reply == QMessageBox::Yes) {
				try {
					fs::remove_all(fullPath);
					//updateListFilesPoject(path);
				} catch (const fs::filesystem_error& e) {
					QMessageBox::warning(this, "Erreur", e.what());
				}
			}
		});
		newButton->append(c3);
		// Button *c4 = new Button("Hello World 4");
		// newButton->append(c4);
	}

	layoutExplorerListItems->addStretch();
}



FilesExplorerDreamMountain::FilesExplorerDreamMountain(WindowDreamMountain *app, QWidget *parent) : QWidget(parent) {
	setMinimumWidth(240);
	setMaximumWidth(340);

	windowParentApp = app;

	verticalBox = new QVBoxLayout(this);
	verticalBox->setContentsMargins(0,0,0,0);
	verticalBox->setSpacing(0);

	scroll = new QScrollArea(this);
	scroll->setWidgetResizable(true);
	scroll->setFrameShape(QFrame::NoFrame);
	scroll->setStyleSheet(scrollBarWindow);

	contenaireExplorere = new QWidget(scroll);
	contenaireExplorere->setStyleSheet("background-color: "+windowBackgoundColor+";");

	scroll->setWidget(contenaireExplorere);
	verticalBox->addWidget(scroll);


	// backExplorerBtn
	QPushButton* backExplorerBtn = windowParentApp->getCustomWindowBarDreamMountain()->AppendButtonList(
		nullptr,
		iconBackFolder,
		24,
		R"(
		QPushButton {
			background-color: #25282d;
			color: #fff;
			padding: 6px;
			border-radius: 5px;
			height: 24px;
			width: 24px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		})"
	);

	WindowDreamMountain* wp = windowParentApp;
	QObject::connect(backExplorerBtn, &QPushButton::clicked, [this, wp]() {
		//qDebug() << "//" << windowParentApp->filesExplorerHistory.back();
		backFolderToExplorer(windowParentApp);
	});
	windowParentApp->getCustomWindowBarDreamMountain()->appendLeftButtonList(backExplorerBtn);

	//uploadFolderProjectBtn
	QPushButton* uploadFolderProjectBtn = windowParentApp->getCustomWindowBarDreamMountain()->AppendButtonList(
		nullptr,
		iconAddProject,
		24,
		R"(
		QPushButton {
			background-color: #25282d;
			padding: 6px;
			border-radius: 5px;
			height: 24px;
			width: 24px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		})"
	);
	QObject::connect(uploadFolderProjectBtn, &QPushButton::clicked, [this]() { openFolder(windowParentApp); });
	windowParentApp->getCustomWindowBarDreamMountain()->appendLeftButtonList(uploadFolderProjectBtn);

	//uploadFileBtn
	QPushButton* saveFileBtn = windowParentApp->getCustomWindowBarDreamMountain()->AppendButtonList(
		nullptr,
		iconSave,
		24,
		R"(
		QPushButton {
			background-color: #25282d;
			padding: 6px;
			border-radius: 5px;
			height: 24px;
			width: 24px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		})"
	);
	QObject::connect(saveFileBtn, &QPushButton::clicked, [this]() { saveFile(windowParentApp); });
	windowParentApp->getCustomWindowBarDreamMountain()->appendLeftButtonList(saveFileBtn);

	windowParentApp->getCustomWindowBarDreamMountain()->UpdateButtonListLeft();
}