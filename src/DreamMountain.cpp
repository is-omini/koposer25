#include "DreamMountain.h"

#include "explorer_files.h"
#include "development_tab.h"

#include "interface.h"

#include <QMainWindow>

#include <QString>
#include <QDir>

#include <QFileDialog>

void createButtonForExplorer(QString svgBalise, Button* &projectButton) {
	projectButton = new Button();
	projectButton->setSvg(svgBalise, 18, 18);
	projectButton->setStyleSheet(
		"QPushButton {"
		"   background-color: rgba(42, 42, 42, 0.0);"
		"	border: none;"
		"   color: white;"
		"   padding: 8px 8px;"
		"	width: 18px;"
		"	height: 18px;"
		"   margin: 0;"
		"	text-align: center;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(42, 42, 42, 1.0);"
		"}"
	);
	projectButton->setCursor(Qt::PointingHandCursor);
}

QWidget* TopExplorer(ExplorerFiles *projectExplorer, DevelopmentTab *tablDeveloppement) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
	);
	newBloc->setFixedHeight(40);

	QHBoxLayout *layoutExplorerProjectActionButtons = new HorizontalBoxLayout(newBloc);
	layoutExplorerProjectActionButtons->setContentsMargins(4,4,4,4);
	///
	Button *projectBackPath = new Button();
	createButtonForExplorer(R"(
	<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
	<path d="M280-200v-80h284q63 0 109.5-40T720-420q0-60-46.5-100T564-560H312l104 104-56 56-200-200 200-200 56 56-104 104h252q97 0 166.5 63T800-420q0 94-69.5 157T564-200H280Z"/>
	</svg>
	)", projectBackPath);
	QObject::connect(projectBackPath, &Button::clicked, [projectExplorer]() {
		if (projectExplorer->projectPathHistory.size() <= 1) {
			return;
		}
		projectExplorer->projectPathHistory.pop_back();

		std::string previous = projectExplorer->projectPathHistory.back();
		projectExplorer->currentPath = QString::fromStdString(previous);

		projectExplorer->explorerListFiles(previous + "/");
	});
	layoutExplorerProjectActionButtons->addWidget(projectBackPath);
	///
	Button *projectImportFolder = new Button();
	createButtonForExplorer(R"(
	<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
	<path d="M160-160q-33 0-56.5-23.5T80-240v-480q0-33 23.5-56.5T160-800h240l80 80h320q33 0 56.5 23.5T880-640H447l-80-80H160v480l96-320h684L837-217q-8 26-29.5 41.5T760-160H160Zm84-80h516l72-240H316l-72 240Zm0 0 72-240-72 240Zm-84-400v-80 80Z"/>
	</svg>
	)", projectImportFolder);
	QObject::connect(projectImportFolder, &Button::clicked, [projectExplorer, newBloc]() {
		QString dossier = QFileDialog::getExistingDirectory(
			newBloc,
			"Choisir un dossier"
		);

		if (!dossier.isEmpty()) {
			projectExplorer->currentPath = dossier;
			projectExplorer->oldProjectPath.clear();
			projectExplorer->projectPathHistory.clear();
			projectExplorer->projectPathHistory.push_back(dossier.toStdString());
			projectExplorer->explorerListFiles(dossier.toStdString() + "/");
		}
	});
	layoutExplorerProjectActionButtons->addWidget(projectImportFolder);

	///
	Button *projectImportFile = new Button();
	createButtonForExplorer(R"(
	<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
	<path d="M240-80q-33 0-56.5-23.5T160-160v-640q0-33 23.5-56.5T240-880h320l240 240v240h-80v-200H520v-200H240v640h360v80H240Zm638 15L760-183v89h-80v-226h226v80h-90l118 118-56 57Zm-638-95v-640 640Z"/>
	</svg>
	)", projectImportFile);
	QObject::connect(projectImportFile, &Button::clicked, [tablDeveloppement]() {
		//open(tablDeveloppement->dreamMountain->codeEditorInput);
	});
	layoutExplorerProjectActionButtons->addWidget(projectImportFile);
	///
	Button *projectSaveButton = new Button();
	createButtonForExplorer(R"(
	<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
	<path d="M840-680v480q0 33-23.5 56.5T760-120H200q-33 0-56.5-23.5T120-200v-560q0-33 23.5-56.5T200-840h480l160 160Zm-80 34L646-760H200v560h560v-446ZM480-240q50 0 85-35t35-85q0-50-35-85t-85-35q-50 0-85 35t-35 85q0 50 35 85t85 35ZM240-560h360v-160H240v160Zm-40-86v446-560 114Z"/>
	</svg>
	)", projectSaveButton);
	QObject::connect(projectSaveButton, &Button::clicked, [tablDeveloppement]() {
		//save(tablDeveloppement->dreamMountain->codeEditorInput, tablDeveloppement->dreamMountain->currentPath);
	});
	layoutExplorerProjectActionButtons->addWidget(projectSaveButton);
	///
	layoutExplorerProjectActionButtons->addStretch();
	return newBloc;
}

DreamMountain::DreamMountain() {
	window.setWindowTitle("DreamMountain : InDevelopment");
	window.resize(1280, 800);
	window.show();

	DevelopmentTab *tablDeveloppement;
	ExplorerFiles *projectExplorer;

	QVBoxLayout *mainWindow = new VerticalBoxLayout(&window);
	QSplitter *mainSection = new Splitter(Qt::Horizontal); // FileExplorer
	QSplitter *bodySection = new Splitter(Qt::Vertical); // Editeur

	tablDeveloppement = new DevelopmentTab(this, codeEditorInput, vueWeb, Qt::Horizontal);
	projectExplorer = new ExplorerFiles(this, codeEditorInput, vueWeb, tablDeveloppement);
	QWidget *actionBar = TopExplorer(projectExplorer, tablDeveloppement);

	QString binPath = QCoreApplication::applicationDirPath();
	QDir dir(binPath);
	dir.cdUp();
	dir.cdUp();
	dir.cdUp();
	qDebug() << dir.filePath("").toUtf8().constData();
	projectExplorer->explorerListFiles(dir.filePath("project/").toUtf8().constData());

	mainSection->addWidget(projectExplorer);
	mainSection->addWidget(tablDeveloppement);

	bodySection->addWidget(actionBar);
	bodySection->addWidget(mainSection);

	mainWindow->addWidget(bodySection);
}

void DreamMountain::setCurrentPath(QString path) {
	qDebug() << path;
	currentPath = path;
	window.setWindowTitle("DreamMountain : InDevelopment : "+currentPath);
}