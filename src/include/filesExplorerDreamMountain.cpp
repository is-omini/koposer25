#include "filesExplorerDreamMountain.h"
#include "windowDreamMountain.h"
#include "colorDreamMountain.h"
#include "iconDreamMountain.h"

#include "system/fileExplorerEngine.h"
#include "system/fileSortingAlgorithm.h"

#include <QFileDialog>
#include <QDir>

#include <QMenu>
#include <QMessageBox>

#include <QInputDialog>

Button* FilesExplorerDreamMountain::ButtonExplorer(
	QString buttonText,
	QString buttonIconSvg,

	QString fileName,
	QString path,



	QString QStrCurrentFolderPath,
	QString titleProject,

	bool isDirectory
) {
	Button *btn = new Button(
		buttonText,
		buttonIconSvg,
		16
	);
	btn->setStyleSheet(styleButonExplorerFileNormal);
	btn->attrPath = fileName;

	QString QStrFilePath = QStrCurrentFolderPath + "/" + fileName + "/";


	// Re-definition
	std::string StdFileName = fileName.toStdString();
	std::string StdCurrentFolderPath = QStrCurrentFolderPath.toStdString();
	std::string StdFilePath = QStrFilePath.toStdString();


	// Ajout du clique
	btn->connect(btn, &QPushButton::clicked, [=](){
		if (isDirectory) {
			qDebug() << "StdFileName : " << StdFileName;
			qDebug() << "StdCurrentFolderPath : " << StdCurrentFolderPath;
			qDebug() << "StdFilePath : " << StdFilePath;
			
			//windowParentApp->filesExplorerHistoryPush(StdFilePath);

			//QDir dir(path);
			//if(dir.exists()) updateListFilesPoject(StdFilePath, titleProject);
			openExplorerFolder(
				windowParentApp,
				StdCurrentFolderPath,
				StdFilePath,
				QStrFilePath,
				titleProject
			);
		} else {
			openExplorerFile(windowParentApp, StdFileName, QStrFilePath);
			//openFile(windowParentApp, StdFileName);
			//windowParentApp->setCurrentFilePath(QStrFilePath);
		}
	});


	// Ajout dans le QVBoxLayout
	layoutExplorerListItems->addWidget(btn, 0, Qt::AlignTop);

	return btn;
}

void FilesExplorerDreamMountain::clearLayoutExplorerListItems() {
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


void FilesExplorerDreamMountain::updateListFilesPoject(std::string StdCurrentFolderPath, QString titleProject) {
	windowParentApp->porjectName = titleProject;
	clearLayoutExplorerListItems();

	layoutExplorerListItems = new QVBoxLayout(contenaireExplorere);
	layoutExplorerListItems->setContentsMargins(0,0,0,0);
	layoutExplorerListItems->setSpacing(0);

	FileSortingAlgorithm *SortingPathFiles = new FileSortingAlgorithm(StdCurrentFolderPath);

	for (const auto& entry : SortingPathFiles->entries) {
		QString buttonIcon = iconFile;
		if(entry.is_directory()) buttonIcon = iconFolder;

		std::string StdPathFileName = entry.path().filename().string();
		std::string StdFilePath = StdCurrentFolderPath + "/" + entry.path().filename().string() + "/";

		QString QStrPathFileName = QString::fromUtf8(StdPathFileName.c_str());
		QString QStrFileName = QString::fromUtf8(StdFilePath.c_str());
		QString QStrCurrentFolderPath = QString::fromUtf8(StdCurrentFolderPath.c_str());

		Button* newButton = ButtonExplorer(
			// Default (name + icon)
			QStrPathFileName, 
			buttonIcon, 

			// Custome
			QStrPathFileName,
			QStrFileName,

			// Event
			QStrCurrentFolderPath,
			titleProject,

			entry.is_directory()
		);

		/* Button *newButton = new Button(
			QString::fromStdString(entry.path().filename().string()),
			buttonIcon,
			16
		);
		newButton->attrPath = QString::fromStdString(StdCurrentFolderPath + '/' + entry.path().filename().string());
		newButton->setStyleSheet(styleButonExplorerFileNormal);
		newButton->connect(newButton, &QPushButton::clicked, [=](){
			if (entry.is_directory()) {
				qDebug() << "/::" << StdCurrentFolderPath;
				windowParentApp->filesExplorerHistoryPush(StdCurrentFolderPath);

				QDir dir(QStrFileName);
				if(dir.exists()) updateListFilesPoject(StdFilePath + "/", titleProject);
			} else {
				openFile(windowParentApp, StdFilePath);
				windowParentApp->setCurrentFilePath(QStrFileName);
			}
		});
		layoutExplorerListItems->addWidget(newButton, 0, Qt::AlignTop);*/


		Button *c1 = new Button("Ouvrir");
		c1->connect(c1, &QPushButton::clicked, [=](){
			if (entry.is_directory()) {
				windowParentApp->filesExplorerHistoryPush(StdCurrentFolderPath);

				QDir dir(QStrFileName);
				if(dir.exists()) updateListFilesPoject(StdFilePath, titleProject);
			}
			else {
				openFile(windowParentApp, StdFilePath);
				windowParentApp->setCurrentFilePath(QStrFileName);
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
					fs::rename(StdFilePath, fs::path(StdFilePath).parent_path() / newName.toStdString());
					//this->explorerListFiles(path);
					updateListFilesPoject(StdFilePath, titleProject);
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
					fs::remove_all(StdFilePath);
					//updateListFilesPoject(path);
				} catch (const fs::filesystem_error& e) {
					QMessageBox::warning(this, "Erreur", e.what());
				}
			}
		});
		newButton->append(c3);
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