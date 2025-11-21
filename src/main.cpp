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
	newBloc->setFixedHeight(48);

	QHBoxLayout *layout = new HorizontalBoxLayout(newBloc);
	Button *openButton = new Button("Ouvrir");
	QObject::connect(openButton, &Button::clicked, [codeEditorInput]() {
		open(codeEditorInput);
	});
	layout->addWidget(openButton);
	layout->addStretch();

	return newBloc;
}

QWidget* VerticalBloc_B(QPlainTextEdit* &codeEditorInput) {
	QWidget *newBloc = new EditorCode(codeEditorInput);

	return newBloc;
}

QWidget* webRenderViewer(QWebEngineView* &webView, QPlainTextEdit* codeEditorInput) {
	QWidget *newBloc = new WebViewer(webView, codeEditorInput);

    /* QWidget *newBloc = new QWidget();
    newBloc->setStyleSheet("background-color: lightyellow; border: none;");
    
    QVBoxLayout *layout = new VerticalBoxLayout(newBloc);

    webView = new QWebEngineView();
    webView->setHtml("<h1>Hello World</h1>");
    //webView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(webView, &QWebEngineView::loadFinished, [=](bool){
        webView->page()->runJavaScript("document.body.contentEditable = 'true';");
    });

    layout->addWidget(webView); */

    return newBloc;
}

QWidget* widget() {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,0.3);"
	);

	return newBloc;
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	QWidget window;

	QPlainTextEdit *codeEditorInput = nullptr;
	QWebEngineView *vueWeb = nullptr;

	QVBoxLayout *mainWindow = new VerticalBoxLayout(&window);

	//QWidget *blocB = VerticalBloc_B(codeEditorInput);
	//QWidget *blocC = webRenderViewer(vueWeb, codeEditorInput);
	QWidget *actionBar = actionNavBar(codeEditorInput);
	QWidget *blocA = explorerFiles(codeEditorInput, vueWeb);

	QSplitter *mainSection = new Splitter(Qt::Horizontal);
	QSplitter *bodySection = new Splitter(Qt::Vertical);

	QSplitter *tablDeveloppement = new DevelopmentTab(codeEditorInput, vueWeb, Qt::Horizontal);

	mainSection->addWidget(blocA);
	mainSection->addWidget(tablDeveloppement);
	//mainSection->addWidget(blocB);
	//mainSection->addWidget(blocC);

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