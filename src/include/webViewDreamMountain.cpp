#include "webViewDreamMountain.h"

#include <QEventLoop>
#include <QVBoxLayout>
#include <QWidget>
#include <QSplitter>
#include "windowDreamMountain.h"

WebViewDreamMountain::WebViewDreamMountain(WindowDreamMountain *main, QWidget *parent) : QWidget(parent) {
	setMinimumWidth(360);
	windowParentApp = main;
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

	webEngineSystem = new WebEngine(windowParentApp, this, splitter);

	WvVisualConstructDrm = new WVVisualConstructDrM(windowParentApp, splitter);
	layout->addWidget(splitter);
	splitter->setSizes({300,150});

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

void WebViewDreamMountain::onVisualConstructVisibilityChanged(bool visible) {
    if (visible) {
        WvVisualConstructDrm->show();
    } else {
        WvVisualConstructDrm->hide();
    }
}

void WebViewDreamMountain::setHtmlWeb(const QString& html, const QUrl& baseUrl){
	webEngineSystem->setHtml(html, baseUrl);
	webEngineSystem->page()->runJavaScript("document.body.contentEditable = true;");
}

QString WebViewDreamMountain::getHtmlWeb(){
    QString html;
    QEventLoop loop;
    webEngineSystem->page()->toHtml([&](const QString &result){ html = result; loop.quit(); });
    loop.exec();
    return html;
}

WebViewDreamMountain::~WebViewDreamMountain() {
	if (webEngineSystem) {
		webEngineSystem->page()->deleteLater();
		webEngineSystem->deleteLater();
	}
}