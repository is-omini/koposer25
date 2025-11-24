#ifndef WEBVIEWDRMAPP_H
#define WEBVIEWDRMAPP_H

#include <QWidget>

#include "system/webEngine.h"

class WebViewDreamMountain : public QWidget {
public:
	explicit WebViewDreamMountain(QWidget *parent = nullptr);
	~WebViewDreamMountain();

	void setHtmlWeb(QString string);
private:
	WebEngine* webEngineSystem;
};

#endif