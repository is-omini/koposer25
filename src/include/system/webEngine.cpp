#include "webEngine.h"

#include "webEnginePage.h"
#include "../windowDreamMountain.h"

WebEngine::WebEngine(WindowDreamMountain* mainWindow, WebViewDreamMountain* main, QWidget* parent) : QWebEngineView(parent) {
	windowParentApp = mainWindow;
    WebViewDrm = main;
	
	WebEnginePage *page = new WebEnginePage(this);
	setPage(page);
}