#include "webEnginePage.h"

#include "webEngine.h"

#include "../webViewDreamMountain.h"

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
    QString line;
	switch(level) {
        case QWebEnginePage::InfoMessageLevel:
            line = "[INFO] Line: " + QString::number(lineNumber) + " : " + message;
            break;
        case QWebEnginePage::WarningMessageLevel:
            line = "[WARNING] Line: " + QString::number(lineNumber) + " : " + message;
            break;
        case QWebEnginePage::ErrorMessageLevel:
            line = "[ERROR] Line: " + QString::number(lineNumber) + " : " + message;
            break;
         default:
            line = "[DEBUG] Line: " + QString::number(lineNumber) + " : " + message;
            break;
    }
    //qDebug() << line;

    webEngineDrm->getWebViewDrm()->getWvVisualConstructDrm()->addLine(line);
	/*
	qDebug()
		<< "JS Console:" << message
		<< "Line:" << lineNumber
		<< "Source:" << sourceID;
	*/
}

WebEnginePage::WebEnginePage(WebEngine* main, QObject* parent) : QWebEnginePage(parent) {
    webEngineDrm = main;
}


/*
<script>
console.log("Hellow World")
console.warn("Hellow World")
console.error("Hellow World")
</script>
*/