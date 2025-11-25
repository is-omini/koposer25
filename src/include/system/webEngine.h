#ifndef WEBENGINESYSTSEM_H
#define WEBENGINESYSTSEM_H

class WebViewDreamMountain;

#include <QWebEngineView>

class WebEngine: public QWebEngineView {
public:
	explicit WebEngine(WebViewDreamMountain* main, QWidget* parent = nullptr);

	WebViewDreamMountain* getWebViewDrm() { return WebViewDrm; }
private:
	WebViewDreamMountain *WebViewDrm;
};

#endif