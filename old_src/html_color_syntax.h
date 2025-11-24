#ifndef HTMLCOLORSYNTAX_H
#define HTMLCOLORSYNTAX_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

class HtmlHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    explicit HtmlHighlighter(QTextDocument *parent);

protected:
    void highlightBlock(const QString &text) override;

private:
    QRegularExpression tagPattern, attrPattern, valuePattern, commentPattern;
    QVector<QTextCharFormat> tagFormats, attrFormats, valueFormats, commentFormats;
};
#endif