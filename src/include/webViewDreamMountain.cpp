#include "webViewDreamMountain.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QSplitter>

WebViewDreamMountain::WebViewDreamMountain(QWidget *parent) : QWidget(parent) {
	setMinimumWidth(360);

	setStyleSheet(
		"background-color: white;"
	);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	QSplitter *splitter = new QSplitter(Qt::Vertical);
	splitter->setStyleSheet("QSplitter::handle { background: transparent; }");
	splitter->setContentsMargins(0,0,0,0);
	splitter->setHandleWidth(0);
	splitter->setMinimumWidth(0);

	webEngineSystem = new WebEngine(splitter);

	WvVisualConstructDrm = new WVVisualConstructDrM(splitter);
	layout->addWidget(splitter);

	//QSplitter *splitter = new QSplitter(Qt::Vertical, this);
	//splitter->setStyleSheet("QSplitter::handle { background: transparent; }");
	//splitter->setContentsMargins(0,0,0,0);
	//splitter->setHandleWidth(0);
	//splitter->setMinimumWidth(0);

	//webEngineSystem = new WebEngine(splitter);
	//WvVisualConstructDrm = new WVVisualConstructDrM(splitter);
	//QWidget* WvVisualConstructDrm = new QWidget(splitter);
	//WvVisualConstructDrm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//splitter->addWidget(webEngineSystem);
	//splitter->addWidget(WvVisualConstructDrm);
	//splitter->setSizes({300,200}); // tailles initiales pour splitter
	//WvVisualConstructDrm->setStyleSheet("background-color: black; color: white;");
	//WvVisualConstructDrm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//layout->addWidget(splitter);
}

void WebViewDreamMountain::setHtmlWeb(QString string) {
	webEngineSystem->setHtml(string);
}

WebViewDreamMountain::~WebViewDreamMountain() {
	if (webEngineSystem) {
		webEngineSystem->page()->deleteLater();
		webEngineSystem->deleteLater();
	}
}