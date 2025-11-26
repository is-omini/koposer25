#include "webViewDreamMountain.h"

#include <QEventLoop>
#include <QVBoxLayout>
#include <QWidget>
#include <QSplitter>
#include "windowDreamMountain.h"

#include <QWebChannel>
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

	// Création du pont et du canal de communication
	bridge = new WebChannelBridge(this);
	QWebChannel *channel = new QWebChannel(this);
	channel->registerObject(QStringLiteral("bridge"), bridge);
	webEngineSystem->page()->setWebChannel(channel);

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
	currentHtml = html;
	webEngineSystem->setHtml(html, baseUrl);

	// Script pour rendre le contenu éditable et notifier les changements
	QString script = R"(
		document.body.contentEditable = true;
		// Écoute les changements dans le body
		document.body.addEventListener('input', function() {
			// Envoie le HTML mis à jour au C++ via le WebChannel
			new QWebChannel(qt.webChannelTransport, function(channel) {
				channel.objects.bridge.htmlChanged(document.documentElement.outerHTML);
			});
		});
	)";
	webEngineSystem->page()->runJavaScript(script);

	// Connecter le signal du pont au signal de cette classe
	connect(bridge, &WebChannelBridge::htmlChanged, this, [this](const QString &html) {
		currentHtml = html;
		emit htmlChanged(html);
	});
}
QString WebViewDreamMountain::getHtmlWebForUpdate() {
	return currentHtml;
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