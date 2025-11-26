#ifndef WEBVIEWDRMAPP_H
#define WEBVIEWDRMAPP_H

#include <QWidget>

#include "webChannelBridge.h"
#include "webViewVisualConstructDreamMountain.h"

#include "system/webEngine.h"

class WindowDreamMountain;

class WebViewDreamMountain : public QWidget {
	Q_OBJECT
public:
	explicit WebViewDreamMountain(WindowDreamMountain *main, QWidget *parent = nullptr);
	~WebViewDreamMountain();

	void setHtmlWeb(const QString& html, const QUrl& baseUrl = QUrl());
	void onVisualConstructVisibilityChanged(bool visible);
	QString getHtmlWebForUpdate();
	QString getHtmlWeb();

	WVVisualConstructDrM* getWvVisualConstructDrm() { return WvVisualConstructDrm; }
	WebEngine* getWebEngineSystem() { return webEngineSystem; }

signals:
    void htmlChanged(const QString &html);

private:
	WebEngine* webEngineSystem;
	WVVisualConstructDrM* WvVisualConstructDrm = nullptr;
	WebChannelBridge* bridge;
	QString currentHtml;

	WindowDreamMountain* windowParentApp;
};

#endif