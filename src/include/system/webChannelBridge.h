#ifndef WEBCHANNELBRIDGE_H
#define WEBCHANNELBRIDGE_H

#include <QObject>

class WebChannelBridge : public QObject
{
    Q_OBJECT
public:
    explicit WebChannelBridge(QObject *parent = nullptr);

signals:
    void htmlChanged(const QString &html);
};

#endif // WEBCHANNELBRIDGE_H