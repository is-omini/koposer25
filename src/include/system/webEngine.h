#ifndef WEBENGINESYSTSEM_H
#define WEBENGINESYSTSEM_H

class WindowDreamMountain;
class WebViewDreamMountain;

#include <QWebEngineView>

class WebEngine: public QWebEngineView {
public:
	explicit WebEngine(WindowDreamMountain* mainWindow, WebViewDreamMountain* main, QWidget* parent = nullptr);

	// Zoomer (augmenter)
	void zoomIn() {
		qreal currentZoom = zoomFactor();
		setZoomFactor(currentZoom + 0.01);
	}

	// Dézoomer (diminuer)
	void zoomOut() {
		qreal currentZoom = zoomFactor();
		setZoomFactor(currentZoom - 0.01);
	}

	qreal zoomCurrent() {
		return zoomFactor();
	}

	WebViewDreamMountain* getWebViewDrm() { return WebViewDrm; }
private:
	WebViewDreamMountain *WebViewDrm;
	WindowDreamMountain* windowParentApp;
};

#endif