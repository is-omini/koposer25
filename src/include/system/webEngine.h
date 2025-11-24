#ifndef WEBENGINESYSTSEM_H
#define WEBENGINESYSTSEM_H

#include <QWebEngineView>

class WebEngine: public QWebEngineView {
public:
	explicit WebEngine(QWidget* parent = nullptr);
};

#endif