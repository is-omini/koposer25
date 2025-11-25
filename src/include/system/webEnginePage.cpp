#include "webEnginePage.h"

/*
enum JavaScriptConsoleMessageLevel {
    QWebEnginePage::InfoMessageLevel,      // équivalent de console.log
    QWebEnginePage::WarningMessageLevel,   // équivalent de console.warn
    QWebEnginePage::ErrorMessageLevel,     // équivalent de console.error
    QWebEnginePage::DebugMessageLevel      // messages de debug JS (rarement utilisé)
};
*/

void WebEnginePage::javaScriptConsoleMessage(
	JavaScriptConsoleMessageLevel level,
	const QString &message,
	int lineNumber,
	const QString &sourceID)
{
	switch(level) {
        case QWebEnginePage::InfoMessageLevel:
            qDebug() << "[INFO]" << message << "Line:" << lineNumber;
            break;
        case QWebEnginePage::WarningMessageLevel:
            qDebug() << "[WARNING]" << message << "Line:" << lineNumber;
            break;
        case QWebEnginePage::ErrorMessageLevel:
            qDebug() << "[ERROR]" << message << "Line:" << lineNumber;
            break;
         default:
            qDebug() << "[DEBUG]" << message << "Line:" << lineNumber;
            break;
    }
    qDebug() << sourceID;
	/*
	qDebug()
		<< "JS Console:" << message
		<< "Line:" << lineNumber
		<< "Source:" << sourceID;
	*/
}

WebEnginePage::WebEnginePage(QObject* parent) : QWebEnginePage(parent) {}


/*
<script>
console.log("Hellow World")
console.warn("Hellow World")
console.error("Hellow World")
</script>
*/