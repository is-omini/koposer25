#ifndef WEBENGINEPAGESYSTSEM_H
#define WEBENGINEPAGESYSTSEM_H

#include <QWebEnginePage>

class WebEnginePage : public QWebEnginePage {
	Q_OBJECT
public:
	explicit WebEnginePage(QObject* parent = nullptr);

protected:
	void javaScriptConsoleMessage(
		JavaScriptConsoleMessageLevel level,
		const QString &message,
		int lineNumber,
		const QString &sourceID) override;
};

#endif