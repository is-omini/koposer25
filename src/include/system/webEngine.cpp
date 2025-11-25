#include "webEngine.h"

#include "webEnginePage.h"

WebEngine::WebEngine(WebViewDreamMountain* main, QWidget* parent) : QWebEngineView(parent) {
	WebViewDrm = main;
	
	WebEnginePage *page = new WebEnginePage(this);
	setPage(page);
}