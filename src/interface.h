#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

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
    explicit Button(const QString &text, QWidget *parent = nullptr);
};