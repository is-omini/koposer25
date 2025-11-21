#include "interface.h"
#include "file.h"
#include "explorer_files.h"
#include "code_editor.h"

#include <QApplication>
#include <QMainWindow>

#include <QScrollBar>

#include <QWidget>

#include <QSplitter>
#include <QVBoxLayout>

#include <QWebEngineView>
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

QWidget* webRenderViewer(QWebEngineView* &webView) {
    QWidget *newBloc = new QWidget();
    newBloc->setStyleSheet("background-color: lightyellow; border: none;");
    
    QVBoxLayout *layout = new VerticalBoxLayout(newBloc);

    webView = new QWebEngineView();
    webView->setHtml("<h1>Hello World</h1>");
    //webView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QObject::connect(webView, &QWebEngineView::loadFinished, [=](bool){
        webView->page()->runJavaScript("document.body.contentEditable = 'true';");
    });

    layout->addWidget(webView);

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

	QWidget *blocB = VerticalBloc_B(codeEditorInput);
	QWidget *blocC = webRenderViewer(vueWeb);
	QWidget *actionBar = actionNavBar(codeEditorInput);
	QWidget *blocA = explorerFiles(codeEditorInput, vueWeb);

	QSplitter *mainSection = new Splitter(Qt::Horizontal);
	QSplitter *bodySection = new Splitter(Qt::Vertical);

	mainSection->addWidget(blocA);
	mainSection->addWidget(blocB);
	mainSection->addWidget(blocC);

	bodySection->addWidget(actionBar);
	bodySection->addWidget(mainSection);

	mainWindow->addWidget(bodySection);

	codeEditorInput->setPlainText(R"(<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link href="https://fonts.googleapis.com/css2?family=Mulish:ital,wght@0,200..1000;1,200..1000&display=swap" rel="stylesheet">
	<style>
	body {
		font-family: "Mulish", "Arial", sans-serif;
		font-weight: 900;

		background: #000;
		color: #fff;
	}
	@keyframes loos {
		from { transform: rotate(0); }
		to { transform: rotate(360deg); }
	}
	.home {
		display: flex;
		align-items: center;
		justify-content: center;

		position: fixed;
		top: 0;
		left: 0;
		right: 0;
		bottom: 0;
	}

	.home h1 {
		font-size: 64px;

		text-shadow: 0px 0px 8px rgba(0, 0, 0, .2);
	}

	.home span.loading {
		display: block;

		width: 32px;
		height: 32px;
		border-radius: 100%;
		border-top: solid 4px #fff;
		border-left: solid 4px #fff;
		border-right: solid 4px transparent;
		border-bottom: solid 4px #fff;

		margin: 0 auto;
		margin-top: 32px;

		animation: loos 2s linear infinite;
	}
	</style>
</head>
<body>
	<span class="img"></span>
	<div class="home">
		<div>
			<h1 id="welcome">Welcome</h1>
			<span class="loading"></span>
		</div>
	</div>
</body>
</html>)");
	QObject::connect(codeEditorInput, &QPlainTextEdit::textChanged, [codeEditorInput, vueWeb]() {
		vueWeb->setHtml(codeEditorInput->toPlainText());
	});
	vueWeb->setHtml(codeEditorInput->toPlainText());

	window.setWindowTitle("Hello World");
	window.resize(windowWidth, windowHeight);
	window.show();
	return app.exec();
}