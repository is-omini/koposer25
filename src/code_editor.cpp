#include "code_editor.h"
#include "interface.h"

#include "html_color_syntax.h"

#include "ui_styles.h"

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
    codeEditorInput->setStyleSheet(scrollBarInput);

    QFont f = codeEditorInput->font();
    f.setPointSizeF(14); // Augmente la hauteur de ligne
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

void TextEdit::keyPressEvent(QKeyEvent *event) {
    // Comportement normal : on laisse Qt insérer le texte
    

    int key = event->key();
    if (key != Qt::Key_Tab) {
        QPlainTextEdit::keyPressEvent(event);
        return;
    }

    //QString txt = toPlainText();
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::LineUnderCursor);
    QString currentLine = cursor.selectedText();

    // Détection avec regex
    QRegularExpression regex("<(h[1-6]|p|div|span|html)>$");
    QRegularExpressionMatch match = regex.match(currentLine);

    if (match.hasMatch()) {
        QString tag = match.captured(1); // Récupère le nom de la balise (h1, h2, etc.)
        int matchLength = match.capturedLength();
        //cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 0);
        cursor.removeSelectedText();
        if(tag == "html") {
            cursor.insertText("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n<title></title>\n</head>\n<body>\n\n\n</body>\n</html>");
            cursor.movePosition(QTextCursor::End);
        } else {
            cursor.insertText(QString("<%1></%1>").arg(tag));
            //cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, tag.length() + 3);
        }
        //cursor.movePosition(QTextCursor::End);
        setTextCursor(cursor);
    } else QPlainTextEdit::keyPressEvent(event);
}