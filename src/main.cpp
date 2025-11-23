#include "DreamMountain.h"

#include <QApplication>
#include <QWidget>
/*
QWidget* actionNavBar(QPlainTextEdit *codeEditorInput, ExplorerFiles *projectExplorer) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
	);
	newBloc->setFixedHeight(32);

	QHBoxLayout *layout = new HorizontalBoxLayout(newBloc);

	layout->addStretch();

	return newBloc;
}*/

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	new DreamMountain();

	/*QWidget window;
	DevelopmentTab *tablDeveloppement = nullptr;
	ExplorerFiles *projectExplorer = nullptr;

	TextEdit *codeEditorInput = nullptr;
	QWebEngineView *vueWeb = nullptr;

	QVBoxLayout *mainWindow = new VerticalBoxLayout(&window);

	tablDeveloppement = new DevelopmentTab(codeEditorInput, vueWeb, Qt::Horizontal);
	projectExplorer = new ExplorerFiles(codeEditorInput, vueWeb, tablDeveloppement);

	QWidget *actionBar = actionNavBar(codeEditorInput, projectExplorer);

	QSplitter *mainSection = new Splitter(Qt::Horizontal);
	QSplitter *bodySection = new Splitter(Qt::Vertical);

	mainSection->addWidget(projectExplorer);
	mainSection->addWidget(tablDeveloppement);

	bodySection->addWidget(actionBar);
	bodySection->addWidget(mainSection);

	mainWindow->addWidget(bodySection);
	
	QObject::connect(codeEditorInput, &QPlainTextEdit::textChanged, [codeEditorInput, vueWeb]() {
		vueWeb->setHtml(codeEditorInput->toPlainText());
	});
	//vueWeb->setHtml("<h1>Hello</h1>");

	window.setWindowTitle("Hello World");
	window.resize(windowWidth, windowHeight);
	window.show(); */
	return app.exec();
}