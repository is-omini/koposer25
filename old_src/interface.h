#ifndef INTERFACE_H
#define INTERFACE_H
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSvgRenderer>
#include <QPainter>

class Splitter : public QSplitter {
    Q_OBJECT
public:
    explicit Splitter(Qt::Orientation orientation, QWidget *parent = nullptr);
};

class VerticalBoxLayout : public QVBoxLayout {
    Q_OBJECT
public:
    explicit VerticalBoxLayout(QWidget *parent = nullptr);
};

class HorizontalBoxLayout : public QHBoxLayout {
    Q_OBJECT
public:
    explicit HorizontalBoxLayout(QWidget *parent = nullptr);
};

class Button : public QPushButton {
    Q_OBJECT
public:
    QString attrID;
    QString attrPath;
    
    explicit Button(const QString &text = nullptr, QWidget *parent = nullptr);

    //void addSvg(const QString &text, QString svgBalise, int size = 8, QWidget *parent);

    void setSvg(QString svg, int w = 0, int h = 0);
};

class ButtonSvg : public QPushButton {
    Q_OBJECT
public:
    QString attrID;
    QString attrPath;
    
    explicit ButtonSvg(const QString &text = nullptr, QString svgBalise = nullptr, int size = 8, QWidget *parent = nullptr);
};
#endif