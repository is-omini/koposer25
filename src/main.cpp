#include <QApplication>
#include <QMainWindow>

#include <QTextEdit>
#include <QWidget>

#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>

#include <QWebEngineView>
#include <Qt>

#include "file.h"

#define windowWidth 1080
#define windowHeight 720

QWidget* VerticalBloc_TOP(QTextEdit *editorTxt) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet("background-color: lightblue;");
	newBloc->setFixedHeight(64);

	QVBoxLayout *layout = new QVBoxLayout(newBloc);
	layout->setContentsMargins(0,0,0,0);

	QPushButton *saveButton = new QPushButton("Sauvegarder");
	QObject::connect(saveButton, &QPushButton::clicked, [editorTxt]() {
		save(editorTxt);
	});

	layout->addWidget(saveButton);

	return newBloc;
}

QWidget* VerticalBloc_A() {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet("background-color: red;");
	newBloc->setFixedWidth(240);

	return newBloc;
}

QWidget* VerticalBloc_B(QTextEdit* &editorTxt) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet("background-color: lightgreen;");

	QVBoxLayout *layout = new QVBoxLayout(newBloc);
	layout->setContentsMargins(0,0,0,0);

	editorTxt = new QTextEdit();
	layout->addWidget(editorTxt);

	return newBloc;
}

QWidget* VerticalBloc_C() {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet("background-color: lightyellow;");
	
	QVBoxLayout *layout = new QVBoxLayout(newBloc);
	layout->setContentsMargins(0,0,0,0);
	QWebEngineView *bloc3 = new QWebEngineView();
	bloc3->setHtml("<html><body><h1>Hello HTML moderne!</h1></body></html>");
	layout->addWidget(bloc3);

	return newBloc;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget window;

	QVBoxLayout *mainWindow = new QVBoxLayout(&window);
	QTextEdit *editorA = nullptr;

	QWidget *blocA = VerticalBloc_A();
	QWidget *blocB = VerticalBloc_B(editorA);
	QWidget *blocC = VerticalBloc_C();
	QWidget *actionBar = VerticalBloc_TOP(editorA);

	QSplitter *mainSection = new QSplitter(Qt::Horizontal);
	QSplitter *bodySection = new QSplitter(Qt::Vertical);

	mainSection->addWidget(blocA);
	mainSection->addWidget(blocB);
	mainSection->addWidget(blocC);
	mainSection->setContentsMargins(0,0,0,0);

	bodySection->addWidget(actionBar);
	bodySection->addWidget(mainSection);
	bodySection->setContentsMargins(0,0,0,0);

	mainWindow->setContentsMargins(0,0,0,0);
	mainWindow->addWidget(bodySection);

	window.setWindowTitle("Fenêtre 4 blocs fixes");
	window.resize(windowWidth, windowHeight);
	window.show();

	return app.exec();
}