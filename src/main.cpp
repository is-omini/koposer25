#include "interface.h"
#include "file.h"
#include "explorer_files.h"
#include "code_editor.h"
#include "web_view.h"
#include "development_tab.h"

#include <QApplication>
#include <QMainWindow>

#include <QScrollBar>

#include <QWidget>

#include <QSplitter>
#include <QVBoxLayout>

#include <QLabel>
#include <Qt>
#include <QScrollArea>

#define windowWidth 1280
#define windowHeight 800

QWidget* actionNavBar(QPlainTextEdit *codeEditorInput) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
	);
	newBloc->setFixedHeight(32);

	QHBoxLayout *layout = new HorizontalBoxLayout(newBloc);
	Button *openButton = new Button("Ouvrir");
	QObject::connect(openButton, &Button::clicked, [codeEditorInput]() {
		open(codeEditorInput);
	});
	Button *openFOlderButton = new Button("Ouvrir");
	QObject::connect(openFOlderButton, &Button::clicked, [codeEditorInput]() {
		open(codeEditorInput);
	});
	layout->addWidget(openFOlderButton);
	layout->addWidget(openButton);
	layout->addStretch();

	return newBloc;
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	QWidget window;

	QPlainTextEdit *codeEditorInput = nullptr;
	QWebEngineView *vueWeb = nullptr;

	QVBoxLayout *mainWindow = new VerticalBoxLayout(&window);

	DevelopmentTab *tablDeveloppement = new DevelopmentTab(codeEditorInput, vueWeb, Qt::Horizontal);
	QWidget *actionBar = actionNavBar(codeEditorInput);
	QWidget *projectExplorer = new ExplorerFiles(codeEditorInput, vueWeb, tablDeveloppement);

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
	vueWeb->setHtml(codeEditorInput->toPlainText());

	window.setWindowTitle("Hello World");
	window.resize(windowWidth, windowHeight);
	window.show();
	return app.exec();
}