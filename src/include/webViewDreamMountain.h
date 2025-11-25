#ifndef WEBVIEWDRMAPP_H
#define WEBVIEWDRMAPP_H

#include <QWidget>

#include "webViewVisualConstructDreamMountain.h"

#include "system/webEngine.h"

class WindowDreamMountain;

class WebViewDreamMountain : public QWidget {
public:
	explicit WebViewDreamMountain(WindowDreamMountain *main,QWidget *parent = nullptr);
	~WebViewDreamMountain();

	void setHtmlWeb(QString string);
	QString getHtmlWeb(QString string);

	WVVisualConstructDrM* getWvVisualConstructDrm() { return WvVisualConstructDrm; }
	WebEngine* getWebEngineSystem() { return webEngineSystem; }
private:
	WebEngine* webEngineSystem;
	WVVisualConstructDrM* WvVisualConstructDrm = nullptr;

	WindowDreamMountain* windowParentApp;
};

#endif