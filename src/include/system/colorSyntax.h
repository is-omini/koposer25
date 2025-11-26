#ifndef COLORSYNTAXSYSTEM_H
#define COLORSYNTAXSYSTEM_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

#include <QCoreApplication>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class HtmlHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    explicit HtmlHighlighter(QTextDocument *parent);

    void openFileSyntaxDrm(QString path) {
        QFile file(path);

        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Unable to open:" << path;
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();

        // --- Keywords ---
        for (const QJsonValue &k : obj["keywords"].toArray())
            keywords.append(k.toString());

        // --- Comments ---
        QJsonObject commentObj = obj["comments"].toObject();
        QJsonObject blockObj = commentObj["block"].toObject();

        commentStart = blockObj["start"].toString();
        commentEnd   = blockObj["end"].toString();

        // --- Strings ---
        QJsonArray delims = obj["strings"].toObject()["delimiters"].toArray();
        for (const QJsonValue &d : delims)
            stringDelimiters.append(d.toString());

        // --- Extensions ---
        for (const QJsonValue &ext : obj["file_extensions"].toArray())
            extensions.append(ext.toString());
    }

protected:
    void highlightBlock(const QString &text) override;

private:
    QStringList keywords;

    QString commentStart;
    QString commentEnd;
    QStringList stringDelimiters;
    QStringList extensions;
    QString name;

    //QRegularExpression tagPattern, attrPattern, valuePattern, commentPattern;
    //QVector<QTextCharFormat> tagFormats, attrFormats, valueFormats, commentFormats;
};
#endif