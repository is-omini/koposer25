#include <QApplication>
#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QWidget>

class CodeEditor : public QPlainTextEdit
{
public:
    CodeEditor(QWidget *parent = nullptr) : QPlainTextEdit(parent)
    {
        // Crée la zone pour les numéros de lignes
        lineNumberArea = new QWidget(this);
        connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
        connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::updateLineNumberArea);
        connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

        updateLineNumberAreaWidth(0);
        highlightCurrentLine();
    }

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QPlainTextEdit::resizeEvent(event);
        QRect cr = contentsRect();
        lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
    }

    void paintEvent(QPaintEvent *event) override
    {
        QPlainTextEdit::paintEvent(event);
    }

private:
    QWidget *lineNumberArea;

    int lineNumberAreaWidth()
    {
        int digits = 1;
        int max = qMax(1, blockCount());
        while (max >= 10) { max /= 10; digits++; }
        return 3 + fontMetrics().horizontalAdvance('9') * digits;
    }

    void updateLineNumberAreaWidth(int)
    {
        setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
    }

    void updateLineNumberArea(const QRect &rect, int dy)
    {
        if (dy)
            lineNumberArea->scroll(0, dy);
        else
            lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
        if (rect.contains(viewport()->rect()))
            updateLineNumberAreaWidth(0);
    }

    void highlightCurrentLine()
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        if (!isReadOnly()) {
            QTextEdit::ExtraSelection selection;
            QColor lineColor(232, 242, 254);
            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            extraSelections.append(selection);
        }
        setExtraSelections(extraSelections);
    }

    void lineNumberAreaPaintEvent(QPaintEvent *event)
    {
        QPainter painter(lineNumberArea);
        painter.fillRect(event->rect(), QColor(240, 240, 240));

        QTextBlock block = firstVisibleBlock();
        int blockNumber = block.blockNumber();
        int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
        int bottom = top + static_cast<int>(blockBoundingRect(block).height());

        while (block.isValid() && top <= event->rect().bottom()) {
            if (block.isVisible() && bottom >= event->rect().top()) {
                QString number = QString::number(blockNumber + 1);
                painter.setPen(Qt::black);
                painter.drawText(0, top, lineNumberArea->width() - 2, fontMetrics().height(),
                                 Qt::AlignRight, number);
            }
            block = block.next();
            top = bottom;
            bottom = top + static_cast<int>(blockBoundingRect(block).height());
            blockNumber++;
        }
    }

    // On redéfinit l'événement paint pour la zone des numéros de lignes
    bool event(QEvent *e) override
    {
        if (e->type() == QEvent::Paint && sender() == lineNumberArea) {
            lineNumberAreaPaintEvent(static_cast<QPaintEvent*>(e));
        }
        return QPlainTextEdit::event(e);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CodeEditor editor;
    editor.setWindowTitle("Éditeur de texte avec numéros de ligne");
    editor.resize(600, 400);
    editor.show();
    return app.exec();
}
