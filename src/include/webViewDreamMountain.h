#ifndef WEBVIEWDRMAPP_H
#define WEBVIEWDRMAPP_H

#include <QWidget>

#include "webViewVisualConstructDreamMountain.h"

#include "system/webEngine.h"

class WebViewDreamMountain : public QWidget {
public:
	explicit WebViewDreamMountain(QWidget *parent = nullptr);
	~WebViewDreamMountain();

	void setHtmlWeb(QString string);
	QString getHtmlWeb(QString string);

	WVVisualConstructDrM* getWvVisualConstructDrm() { return WvVisualConstructDrm; }
private:
	WebEngine* webEngineSystem;
	WVVisualConstructDrM* WvVisualConstructDrm = nullptr;
};

#endif