#include "webViewDreamMountain.h"

#include <QVBoxLayout>

WebViewDreamMountain::WebViewDreamMountain(QWidget *parent) : QWidget(parent) {
	setStyleSheet(
		"background-color: white;"
	);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	webEngineSystem = new WebEngine(this);

	layout->addWidget(webEngineSystem);
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