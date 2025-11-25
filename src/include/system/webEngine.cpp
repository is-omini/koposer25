#include "webEngine.h"

#include "webEnginePage.h"

WebEngine::WebEngine(QWidget* parent) : QWebEngineView(parent) {
	WebEnginePage *page = new WebEnginePage(this);
	setPage(page);
}