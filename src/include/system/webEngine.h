#ifndef WEBENGINESYSTSEM_H
#define WEBENGINESYSTSEM_H

class WebViewDreamMountain;

#include <QWebEngineView>

class WebEngine: public QWebEngineView {
public:
	explicit WebEngine(WebViewDreamMountain* main, QWidget* parent = nullptr);

	// Zoomer (augmenter)
	void zoomIn() {
		qreal currentZoom = zoomFactor();
		setZoomFactor(currentZoom + 0.1);
	}

	// Dézoomer (diminuer)
	void zoomOut() {
		qreal currentZoom = zoomFactor();
		setZoomFactor(currentZoom - 0.1);
	}

	qreal zoomCurrent() {
		return zoomFactor();
	}

	WebViewDreamMountain* getWebViewDrm() { return WebViewDrm; }
private:
	WebViewDreamMountain *WebViewDrm;
};

#endif