#include "webEngine.h"

#include "webEnginePage.h"

#include "../webViewDreamMountain.h"
#include "../windowDreamMountain.h"

WebEngine::WebEngine(WindowDreamMountain* mainWindow, WebViewDreamMountain* main, QWidget* parent) : QWebEngineView(parent) {
	WebViewDrm = main;
	windowParentApp = mainWindow;
	
	WebEnginePage *page = new WebEnginePage(this);
	setPage(page);

	connect(this, &QWebEngineView::loadFinished, [=](bool ok){
		this->page()->toHtml([=](const QString &html){
			WebViewDrm
			->getWvVisualConstructDrm()
			->getHtmlElement(html.toStdString());
		});
	});
}