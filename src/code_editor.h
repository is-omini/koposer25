#ifndef CODE_EDITOR_H
#define CODE_EDITOR_H

#include <QWidget>
#include <QPlainTextEdit>

#include <QTextBlock>
#include <QPainter>
#include "interface.h"

class TextEdit;

class LineNumberArea : public QWidget {
public:
    int lineNumberWidth;
    explicit LineNumberArea(TextEdit *editor);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    TextEdit *textEdit;
    QWidget *overlay;
};

class EditorCode : public QWidget {
    Q_OBJECT
public:
    explicit EditorCode(
        TextEdit* &codeEditorInput,
        QWidget *parent = nullptr
    );

    void updatePosition();

    TextEdit* codeEditor;
    QWidget* overlay;
    VerticalBoxLayout* listAuto;
    
    int cursorPosY;
    int cursorPosX;
};

class TextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    LineNumberArea *lineNumberArea;

    explicit TextEdit(EditorCode* editorContenaire, QWidget *parent = nullptr) : QPlainTextEdit(parent) {
        lineNumberArea = new LineNumberArea(this);
        connect(this, &QPlainTextEdit::blockCountChanged, this, &TextEdit::updateLineNumberAreaWidth);
        connect(this, &QPlainTextEdit::updateRequest, this, &TextEdit::updateLineNumberArea);
        updateLineNumberAreaWidth(0);

        editor = editorContenaire;
    }

    int lineNumberAreaWidth() {
        int digits = QString::number(blockCount()).length();
        return 3 + 32 + fontMetrics().horizontalAdvance('9') * digits;
    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        QPlainTextEdit::resizeEvent(event);
        QRect cr = contentsRect();
        lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
    }

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int) {
        setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
    }

    void updateLineNumberArea(const QRect &rect, int dy) {
        if(dy)
            lineNumberArea->scroll(0, dy);
        else
            lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }

private:
    EditorCode *editor;

    friend class LineNumberArea;
};

#endif