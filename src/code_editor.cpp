#include "code_editor.h"
#include "interface.h"

#include "html_color_syntax.h"

LineNumberArea::LineNumberArea(TextEdit *editor) : QWidget(editor), textEdit(editor) {}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), QColor("#1e1f22"));

    QTextBlock block = textEdit->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)textEdit->blockBoundingGeometry(block).translated(textEdit->contentOffset()).top();
    int bottom = top + (int)textEdit->blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom()) {
        if(block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor("#4d4e51"));
            painter.drawText(0, top, qMax(32, width()-16), textEdit->fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int)textEdit->blockBoundingRect(block).height();
        ++blockNumber;
    }
}

EditorCode::EditorCode(
    TextEdit* &codeEditorInput,
    QWidget *parent
) : QWidget(parent)
{
    setStyleSheet(
        "background-color: #1e1f22;"
        "color: white;"
    );
    QVBoxLayout *layout = new VerticalBoxLayout(this);
    codeEditorInput = new TextEdit();
    codeEditorInput->setStyleSheet("QPlainTextEdit { line-height: 1.7; }");

    QFont f = codeEditorInput->font();
    f.setPointSizeF(16); // Augmente la hauteur de ligne
    f.setLetterSpacing(QFont::PercentageSpacing, 105); // Légère augmentation
    codeEditorInput->setFont(f);

    QPalette p = codeEditorInput->palette();
    p.setColor(QPalette::Highlight, QColor("#25282d"));
    p.setColor(QPalette::HighlightedText, QColor("#ffffff"));
    codeEditorInput->setPalette(p);

    HtmlHighlighter *highlighter = new HtmlHighlighter(codeEditorInput->document());

    codeEditorInput->setTabStopDistance(32);
    layout->addWidget(codeEditorInput);

    codeEditor = codeEditorInput;
};