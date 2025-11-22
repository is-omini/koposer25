#include "DreamMountain.h"

#include "explorer_files.h"
#include "development_tab.h"

#include "interface.h"

#include <QMainWindow>

DreamMountain::DreamMountain() {
	window.setWindowTitle("DreamMountain : InDevelopment");
	window.resize(1280, 800);
	window.show();

	DevelopmentTab *tablDeveloppement;
	ExplorerFiles *projectExplorer;

	TextEdit *codeEditorInput;
	QWebEngineView *vueWeb;
	QVBoxLayout *mainWindow = new VerticalBoxLayout(&window);
	QSplitter *mainSection = new Splitter(Qt::Horizontal); // FileExplorer
	QSplitter *bodySection = new Splitter(Qt::Vertical); // Editeur

	tablDeveloppement = new DevelopmentTab(this, codeEditorInput, vueWeb, Qt::Horizontal);
	projectExplorer = new ExplorerFiles(this, codeEditorInput, vueWeb, tablDeveloppement);
	mainSection->addWidget(projectExplorer);
	mainSection->addWidget(tablDeveloppement);

	//bodySection->addWidget(actionBar);
	bodySection->addWidget(mainSection);

	mainWindow->addWidget(bodySection);
}

void DreamMountain::setCurrentPath(QString path) {
	qDebug() << path;
	currentPath = path;
	window.setWindowTitle("DreamMountain : InDevelopment : "+currentPath);
}