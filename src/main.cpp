#include <QApplication>
#include <QMainWindow>

#include <QTextDocument>
#include <QScrollBar>

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
	newBloc->setFixedHeight(48);

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

void updateLineNumbers(QPlainTextEdit* editor, QLabel* label)
{
	QStringList list;
	int totalLines = editor->document()->blockCount();

	for (int i = 1; i <= totalLines; ++i)
		list << QString::number(i);

	label->setText(list.join("\n"));
}

QWidget* VerticalBloc_B(QPlainTextEdit* &editorTxt) {
	QWidget *newBloc = new QWidget();
	newBloc->setStyleSheet(
		"background-color: rgba(23,23,23,1);"
		"color: white;"
	);

	QVBoxLayout *mainEditor = new QVBoxLayout(newBloc);
	mainEditor->setContentsMargins(0,0,0,0);
	mainEditor->setSpacing(0);

	QWidget *tabBar = new QWidget();
	tabBar->setStyleSheet(
		"background-color: red;"
	);
	tabBar->setFixedHeight(48);

	QLabel *numLinesLabel = nullptr;
	QWidget *editorTxtContenaire = CodeEdit(editorTxt, numLinesLabel);

	mainEditor->addWidget(tabBar);
	mainEditor->addWidget(editorTxtContenaire);

	// Connecter les signaux pour mettre à jour les numéros de ligne
	QObject::connect(
		editorTxt->document(),
		&QTextDocument::blockCountChanged,
		[=]() { updateLineNumbers(editorTxt, numLinesLabel);
	});
	QObject::connect(
		editorTxt,
		&QPlainTextEdit::textChanged,
		[=]() { updateLineNumbers(editorTxt, numLinesLabel);
	});
	QObject::connect(
		editorTxt->verticalScrollBar(),
		&QScrollBar::valueChanged,
		[=]() { updateLineNumbers(editorTxt, numLinesLabel);
	});
	// Initialiser l'affichage
	updateLineNumbers(editorTxt, numLinesLabel);

	/* newBloc->setStyleSheet(
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
	 */

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

	mainSection->setStyleSheet("QSplitter::handle { background: transparent; }");
	bodySection->setStyleSheet("QSplitter::handle { background: transparent; }");

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