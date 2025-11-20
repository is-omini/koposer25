#include <QApplication>
#include <QMainWindow>

#include <QWidget>

#include <QSplitter>
#include <QVBoxLayout>

#include <QWebEngineView>
#include <QLabel>
#include <Qt>

#include "file.h"
#include "button.h"
#include "codeEdit.h"

#define windowWidth 1080
#define windowHeight 720

QWidget* VerticalBloc_TOP(QPlainTextEdit *editorTxt) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
	);
	newBloc->setFixedHeight(64);

	QHBoxLayout *layout = new QHBoxLayout(newBloc);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	Button *saveButton = new Button("Sauvegarder");
	QObject::connect(saveButton, &Button::clicked, [editorTxt]() {
		save(editorTxt);
	});
	Button *openButton = new Button("Ouvrir");
	QObject::connect(openButton, &Button::clicked, [editorTxt]() {
		open(editorTxt);
	});
	layout->addWidget(saveButton);
	layout->addWidget(openButton);
	layout->addStretch(); // Ajoute un espace flexible pour pousser les boutons à gauche
	return newBloc;
}

QWidget* VerticalBloc_A() {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
		"border: none;"
	);
	newBloc->setFixedWidth(240);
	return newBloc;
}

QWidget* VerticalBloc_B(QPlainTextEdit* &editorTxt) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
		"color: #fff;"
		"border: none;"
	);
	QVBoxLayout *layout = new QVBoxLayout(newBloc);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	QLabel *numLinesLabel = nullptr;
	QWidget *editorTxtContenaire = CodeEdit(editorTxt, numLinesLabel);
	layout->addWidget(editorTxtContenaire);

	return newBloc;
}


QWidget* VerticalBloc_C(QWebEngineView* &webView) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet("background-color: lightyellow;border: none;");
	
	QVBoxLayout *layout = new QVBoxLayout(newBloc);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	webView = new QWebEngineView();
	webView->setHtml("<h1>Hello World</h1>");
	layout->addWidget(webView);

	return newBloc;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget window;

	QPlainTextEdit *editorA = nullptr;
	QWebEngineView *vueWeb = nullptr;

	QVBoxLayout *mainWindow = new QVBoxLayout(&window);

	QWidget *blocA = VerticalBloc_A();
	QWidget *blocB = VerticalBloc_B(editorA);
	QWidget *blocC = VerticalBloc_C(vueWeb);
	QWidget *actionBar = VerticalBloc_TOP(editorA);

	QSplitter *mainSection = new QSplitter(Qt::Horizontal);
	QSplitter *bodySection = new QSplitter(Qt::Vertical);

	mainSection->addWidget(blocA);
	mainSection->addWidget(blocB);
	mainSection->addWidget(blocC);
	mainSection->setContentsMargins(0,0,0,0);
	mainSection->setHandleWidth(0);

	bodySection->addWidget(actionBar);
	bodySection->addWidget(mainSection);
	bodySection->setContentsMargins(0,0,0,0);
	bodySection->setHandleWidth(0);

	mainWindow->setContentsMargins(0,0,0,0);
	mainWindow->setSpacing(0);
	mainWindow->addWidget(bodySection);


	QObject::connect(editorA, &QPlainTextEdit::textChanged, [editorA, vueWeb]() {
		vueWeb->setHtml(editorA->toPlainText());
	});
	vueWeb->setHtml(editorA->toPlainText());

	window.setWindowTitle("Fenêtre 4 blocs fixes");
	window.resize(windowWidth, windowHeight);
	window.show();

	return app.exec();
}