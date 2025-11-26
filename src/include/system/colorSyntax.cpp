#include "colorSyntax.h"

HtmlHighlighter::HtmlHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    QString path = QCoreApplication::applicationDirPath();
    qDebug() << path;

    openFileSyntaxDrm("src/language/html.syntax-drm");

    // // Balises HTML : bleu
    // QTextCharFormat tagFormat;
    // tagFormat.setForeground(QColor("#559cd6"));
    // tagPattern = QRegularExpression("<[^>]+>");
    // tagFormats.push_back(tagFormat);

    // // Attributs : rouge
    // QTextCharFormat attrFormat;
    // attrFormat.setForeground(QColor("#9cdcfe"));
    // attrPattern = QRegularExpression("\\b\\w+(?==)");
    // attrFormats.push_back(attrFormat);

    // // Valeurs entre guillemets : vert
    // QTextCharFormat valueFormat;
    // valueFormat.setForeground(QColor("#ce9178"));
    // valuePattern = QRegularExpression("\".*?\"");
    // valueFormats.push_back(valueFormat);

    // // Commentaires HTML : gris
    // QTextCharFormat commentFormat;
    // commentFormat.setForeground(QColor("#569CD6"));
    // commentPattern = QRegularExpression("<!--[^>]*-->");
    // commentFormats.push_back(commentFormat);
}

// void HtmlHighlighter::highlightBlock(const QString &text) {
//     // Balises
//     QRegularExpressionMatchIterator i = tagPattern.globalMatch(text);
//     while(i.hasNext()) {
//         QRegularExpressionMatch match = i.next();
//         setFormat(match.capturedStart(), match.capturedLength(), tagFormats[0]);
//     }

//     // Attributs
//     i = attrPattern.globalMatch(text);
//     while(i.hasNext()) {
//         QRegularExpressionMatch match = i.next();
//         setFormat(match.capturedStart(), match.capturedLength(), attrFormats[0]);
//     }

//     // Valeurs
//     i = valuePattern.globalMatch(text);
//     while(i.hasNext()) {
//         QRegularExpressionMatch match = i.next();
//         setFormat(match.capturedStart(), match.capturedLength(), valueFormats[0]);
//     }

//     // Commentaires
//     i = commentPattern.globalMatch(text);
//     while(i.hasNext()) {
//         QRegularExpressionMatch match = i.next();
//         setFormat(match.capturedStart(), match.capturedLength(), commentFormats[0]);
//     }
// }

void HtmlHighlighter::highlightBlock(const QString &text) {
    for (const QString &keyword : keywords) {

        QRegularExpression expr("\\b" + QRegularExpression::escape(keyword) + "\\b");

        QRegularExpressionMatchIterator it = expr.globalMatch(text);
        while (it.hasNext()) {
            QRegularExpressionMatch m = it.next();
            setFormat(m.capturedStart(), m.capturedLength(), QColor("#559cd6"));
        }
    }

    QRegularExpression commentPattern(
        QRegularExpression::escape(commentStart)
        + ".*?"
        + QRegularExpression::escape(commentEnd)
    );

    for (const QString &d : stringDelimiters) {
        QRegularExpression stringPattern(
            QRegularExpression::escape(d) + ".*?" + QRegularExpression::escape(d)
        );

        auto it = stringPattern.globalMatch(text);
        while (it.hasNext()) {
            auto m = it.next();
            setFormat(m.capturedStart(), m.capturedLength(), QColor("red"));
        }
    }
}