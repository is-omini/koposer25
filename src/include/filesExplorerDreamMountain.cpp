#include "filesExplorerDreamMountain.h"
#include "windowDreamMountain.h"
#include "colorDreamMountain.h"
#include "iconDreamMountain.h"

#include "interfaceDreamMountain.h"

#include "system/fileExplorerEngine.h"
#include "system/fileEngine.h"
#include "system/fileSortingAlgorithm.h"

#include <QFileDialog>
#include <QDir>

FilesExplorerDreamMountain::FilesExplorerDreamMountain(WindowDreamMountain *app, QWidget *parent) : QWidget(parent) {
	setFixedWidth(240);

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

	QPushButton* test = windowParentApp->getCustomWindowBarDreamMountain()->AppendButtonList(
		nullptr,
		iconBackFolder,
		16,
		R"(
		QPushButton {
			background-color: #25282d;
			color: #fff;
			padding: 8px;
			border-radius: 5px;
			height: 16px;
			width: 16px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		})"
	);
	QObject::connect(test, &QPushButton::clicked, [this]() {
		if (windowParentApp->filesExplorerHistory.size() <= 1) {
			return;
		}
		windowParentApp->filesExplorerHistory.pop_back();

		std::string previous = windowParentApp->filesExplorerHistory.back();
		windowParentApp->currentPath = QString::fromStdString(previous);

		updateListFilesPoject(previous + "/", windowParentApp->porjectName);
	});
	windowParentApp->getCustomWindowBarDreamMountain()->appendLeftButtonList(test);

	QPushButton* uploadFolderProjectBtn = windowParentApp->getCustomWindowBarDreamMountain()->AppendButtonList(
		nullptr,
		iconAddProject,
		16,
		R"(
		QPushButton {
			background-color: #25282d;
			padding: 8px;
			border-radius: 5px;
			height: 16px;
			width: 16px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		})"
	);
	QObject::connect(uploadFolderProjectBtn, &QPushButton::clicked, [this]() {
		openFolder(windowParentApp);
		/*QString dossier = QFileDialog::getExistingDirectory(
			this,
			"Choisir un dossier"
		);

		if (!dossier.isEmpty()) {
			windowParentApp->setCurrentProjectPath(dossier);
			//windowParentApp->oldProjectPath.clear();
			windowParentApp->filesExplorerHistory.clear();
			windowParentApp->filesExplorerHistory.push_back(dossier.toStdString());
			updateListFilesPoject(windowParentApp->getCurrentProjectPath().toStdString() + "/");
		}*/
	});
	windowParentApp->getCustomWindowBarDreamMountain()->appendLeftButtonList(uploadFolderProjectBtn);

	QPushButton* uploadFileBtn = windowParentApp->getCustomWindowBarDreamMountain()->AppendButtonList(
		nullptr,
		iconAddFile,
		16,
		R"(
		QPushButton {
			background-color: #25282d;
			padding: 8px;
			border-radius: 5px;
			height: 16px;
			width: 16px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		})"
	);
	QObject::connect(uploadFileBtn, &QPushButton::clicked, [this]() {
		saveFile(windowParentApp);

		/*QFile fichier(fichierPath);

		QString texte = textEdit->toPlainText();
			
		if (fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream out(&fichier);
			out << texte;
		}*/
	});
	windowParentApp->getCustomWindowBarDreamMountain()->appendLeftButtonList(uploadFileBtn);

	windowParentApp->getCustomWindowBarDreamMountain()->UpdateButtonListLeft();
}


void FilesExplorerDreamMountain::updateListFilesPoject(std::string path, QString titleProject) {
	windowParentApp->porjectName = titleProject;
	windowParentApp->filesExplorer.clear();

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

	layoutExplorerListItems = new QVBoxLayout(contenaireExplorere);
	layoutExplorerListItems->setContentsMargins(0,0,0,0);
	layoutExplorerListItems->setSpacing(0);

	FileSortingAlgorithm *SortingPathFiles = new FileSortingAlgorithm(path);

	for (const auto& entry : SortingPathFiles->entries) {
		std::string fullPath = path + '/' + entry.path().filename().string();

		QString buttonIcon = iconFile;
		if (entry.is_directory()) buttonIcon = iconFolder;

		ButtonSvg *newButton = new ButtonSvg(
			QString::fromStdString(entry.path().filename().string()),
			buttonIcon,
			16
		);
		newButton->attrPath = QString::fromStdString(path + '/' + entry.path().filename().string());
		newButton->setStyleSheet(styleButonExplorerFileNormal);
		newButton->connect(newButton, &QPushButton::clicked, [=](){
			if (entry.is_directory()) {
				currentPath = QString::fromStdString(fullPath);
				if (windowParentApp->filesExplorerHistory.empty() || windowParentApp->filesExplorerHistory.back() != fullPath) {
					windowParentApp->filesExplorerHistory.push_back(fullPath);
				}

				QDir dir(QString::fromStdString(fullPath));
				if(dir.exists()) updateListFilesPoject(fullPath + "/", titleProject);
			} else {
				FileEngine *getFile = new FileEngine(fullPath);
				if (getFile->mimeFromExtension().find("text") == std::string::npos) return;
				char *text = getFile->read();
				windowParentApp->getAppContent()->EditFiles(
					text,
					getFile->mimeFromExtension(),
					path + '/' + entry.path().filename().string(),
					entry.path().filename().string(),
					1
				);
				free(text);
				windowParentApp->setCurrentFilePath(QString::fromStdString(fullPath));
			}
		});
		layoutExplorerListItems->addWidget(newButton, 0, Qt::AlignTop);
	}

	layoutExplorerListItems->addStretch();
}