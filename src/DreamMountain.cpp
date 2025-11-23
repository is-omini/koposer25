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
	projectButton->setSvg(svgBalise, 20, 20);
	projectButton->setStyleSheet(
		"QPushButton {"
		"	border: none;"
		"   color: white;"
		"   background-color: transparent;"
		"   padding: 8px 8px;"
		"	width: 20px;"
		"	height: 20px;"
		"   margin: 0;"
		"	text-align: center;"
		"}"
		"QPushButton:hover {"
		"   background-color: #1e1f22;"
		"}"
	);
	projectButton->setCursor(Qt::PointingHandCursor);
}

QWidget* TopExplorer(ExplorerFiles *projectExplorer, DevelopmentTab *tablDeveloppement) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: #2c2d30;"
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
	<path d="M604.62-64.62q-25.31 0-42.66-17.34-17.34-17.35-17.34-42.66 0-19.92 11.38-35.23 11.38-15.3 28.62-21.69v-247.15q-17.24-6.39-28.62-21.19-11.38-14.81-11.38-34.74 0-25.3 17.34-42.65 17.35-17.35 42.66-17.35 25.3 0 42.65 17.35 17.35 17.35 17.35 42.65 0 19.93-11.39 34.74-11.38 14.8-28.61 21.19v148.07L800-339v-89.69q-17.23-6.39-28.62-21.19Q760-464.69 760-484.62q0-25.3 17.35-42.65 17.34-17.35 42.65-17.35t42.65 17.35Q880-509.92 880-484.62q0 19.93-11.38 34.74-11.39 14.8-28.62 21.19v118.23l-215.38 71.54v57.38q17.23 6.39 28.61 21.69 11.39 15.31 11.39 35.23 0 25.31-17.35 42.66-17.35 17.34-42.65 17.34ZM160-200v-520 520Zm24.62 0q-27.62 0-46.12-18.5Q120-237 120-264.62v-430.76q0-27.62 18.5-46.12Q157-760 184.62-760h199.23l80 80H800q16.08 0 28.04 11.96T840-640H447.77l-80-80H184.62q-10.77 0-17.7 6.92-6.92 6.93-6.92 17.7v430.76q0 10.77 6.92 17.7 6.93 6.92 17.7 6.92h264.61v40H184.62Z"/>
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
	<path d="M264.62-120q-27.62 0-46.12-18.5Q200-157 200-184.62v-590.76q0-27.62 18.5-46.12Q237-840 264.62-840H580l180 180v280h-40v-260H560v-160H264.62q-9.24 0-16.93 7.69-7.69 7.69-7.69 16.93v590.76q0 9.24 7.69 16.93 7.69 7.69 16.93 7.69H620v40H264.62ZM878-93.46l-138-138v118.23h-40V-300h186.77v40H767.54l138 138L878-93.46ZM240-160v-640 640Z"/>
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
	<path d="M720-148.46 851.54-280 824-307.54l-84 84V-419h-40v195.46l-84-84L588.46-280 720-148.46ZM580-20v-40h280v40H580ZM244.62-180q-26.08 0-45.35-19.27Q180-218.54 180-244.62v-550.76q0-26.08 19.27-45.35Q218.54-860 244.62-860H520l220 220v125.62h-40V-620H500v-200H244.62q-9.24 0-16.93 7.69-7.69 7.69-7.69 16.93v550.76q0 9.24 7.69 16.93 7.69 7.69 16.93 7.69h240v40h-240ZM220-220v-600 600Z"/>
	</svg>
	)", projectSaveButton);
	QObject::connect(projectSaveButton, &Button::clicked, [tablDeveloppement]() {
		//save(tablDeveloppement->dreamMountain->codeEditorInput, tablDeveloppement->dreamMountain->currentPath);
	});
	layoutExplorerProjectActionButtons->addWidget(projectSaveButton);
	///
	layoutExplorerProjectActionButtons->addStretch();

	///
	Button *editorCodeToggleViewButton = new Button("Source");
	editorCodeToggleViewButton->setStyleSheet(
		"QPushButton {"
		"   color: white;"
		"   background-color: #25282d;"
		"   padding: 8px 16px;"
		"	border-top-right-radius: 0px;"
	    "	border-bottom-right-radius: 0px;"
	    "	border-top-left-radius: 4px;"
	    "	border-bottom-left-radius: 4px;"
		"   margin: 0;"
		"	text-align: center;"
		"}"
		"QPushButton:hover {"
		"   background-color: #4a4b4e;"
		"}"
	);
	QObject::connect(editorCodeToggleViewButton, &Button::clicked, [tablDeveloppement]() {
		//save(tablDeveloppement->dreamMountain->codeEditorInput, tablDeveloppement->dreamMountain->currentPath);
	});
	editorCodeToggleViewButton->setCursor(Qt::PointingHandCursor);
	layoutExplorerProjectActionButtons->addWidget(editorCodeToggleViewButton);
	///
	Button *webViewANDeditorCodeToggleViewButton = new Button("Source | Visual");
	webViewANDeditorCodeToggleViewButton->setStyleSheet(
		"QPushButton {"
		"   color: white;"
		"   background-color: #25282d;"
		"   padding: 8px 16px;"
		"	border-radius: 0px;"
		"   margin: 0;"
		"	text-align: center;"
		"}"
		"QPushButton:hover {"
		"   background-color: #4a4b4e;"
		"}"
	);
	QObject::connect(webViewANDeditorCodeToggleViewButton, &Button::clicked, [tablDeveloppement]() {
		//save(tablDeveloppement->dreamMountain->codeEditorInput, tablDeveloppement->dreamMountain->currentPath);
	});
	webViewANDeditorCodeToggleViewButton->setCursor(Qt::PointingHandCursor);
	layoutExplorerProjectActionButtons->addWidget(webViewANDeditorCodeToggleViewButton);
	///
	Button *webViewToggleViewButton = new Button("Visual");
	webViewToggleViewButton->setStyleSheet(
		"QPushButton {"
		"   color: white;"
		"   background-color: #25282d;"
		"   padding: 8px 16px;"
		"	border-top-right-radius: 4px;"
	    "	border-bottom-right-radius: 4px;"
	    "	border-top-left-radius: 0px;"
	    "	border-bottom-left-radius: 0px;"
		"   margin: 0;"
		"	text-align: center;"
		"}"
		"QPushButton:hover {"
		"   background-color: #4a4b4e;"
		"}"
	);
	QObject::connect(webViewToggleViewButton, &Button::clicked, [tablDeveloppement]() {
		//save(tablDeveloppement->dreamMountain->codeEditorInput, tablDeveloppement->dreamMountain->currentPath);
	});
	webViewToggleViewButton->setCursor(Qt::PointingHandCursor);
	layoutExplorerProjectActionButtons->addWidget(webViewToggleViewButton);
	///
	return newBloc;
}

DreamMountain::DreamMountain() {
	blueColor = "#3477f7";
	windowBackgoundColor = "#2c2d30";
	contenaireBackgoundColor = "#1e1f22";
	inputBackgoundColor = "#1e1f22";
	borderColor = "#5c5d63";

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
	//projectExplorer->explorerListFiles(dir.filePath("project/").toUtf8().constData());
	projectExplorer->explorerListFiles("/Applications", "Applications");

	mainSection->addWidget(projectExplorer);
	mainSection->addWidget(tablDeveloppement);

	bodySection->addWidget(actionBar);
	bodySection->addWidget(mainSection);

	mainWindow->addWidget(bodySection);

	QObject::connect(codeEditorInput, &QPlainTextEdit::textChanged, [this]() {
		vueWeb->setHtml(codeEditorInput->toPlainText());
	});
}

void DreamMountain::setCurrentPath(QString path) {
	qDebug() << path;
	currentPath = path;
	window.setWindowTitle("DreamMountain : InDevelopment : "+currentPath);
}