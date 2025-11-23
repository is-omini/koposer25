#include "code_editor.h"
#include "interface.h"

#include "html_color_syntax.h"

#include "ui_styles.h"

#include <QRect>

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
            lineNumberWidth = qMax(32, width()-16);
            painter.drawText(0, top, lineNumberWidth, textEdit->fontMetrics().height(),
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
    codeEditorInput = new TextEdit(this);
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

    // Widget superposé
    overlay = new QWidget(this);
    overlay->setStyleSheet(
        "background-color: #2c2d30;"
    );
    overlay->setGeometry(56, 50, 250, 32);

    VerticalBoxLayout* listAuto = new VerticalBoxLayout(overlay);
    ButtonSvg *test = new ButtonSvg("Insert string  \"<h1>Hello World</h1>\"", R"(
    <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
    <path d="M280-200v-80h284q63 0 109.5-40T720-420q0-60-46.5-100T564-560H312l104 104-56 56-200-200 200-200 56 56-104 104h252q97 0 166.5 63T800-420q0 94-69.5 157T564-200H280Z"/>
    </svg>
    )", 20);
    test->setStyleSheet(
        "ButtonSvg {"
        "   background-color: rgba(0, 120, 212, 0.3);"
        "   border: 1px solid rgba(0, 120, 212, 1.0);"
        "   color: white;"
        "   padding: 8px 8px;"
        "   margin: 0;"
        "   text-align: left;"
        "}"
        "ButtonSvg:hover {"
        "   background-color: rgba(0, 120, 212, 0.8);"
        "}"
    );//test
    test->connect(test, &QPushButton::clicked, [=](){
        QTextCursor cursor = codeEditorInput->textCursor();
        cursor.select(QTextCursor::LineUnderCursor);
        QString currentLine = cursor.selectedText();
        cursor.removeSelectedText();
        cursor.insertText("<h1>"+currentLine+"</h1>\n");
        codeEditorInput->setTextCursor(cursor);
    });

    listAuto->addWidget(test);

    layout->addWidget(codeEditorInput);
    overlay->raise();

    codeEditor = codeEditorInput;
};

void EditorCode::updatePosition() {
    qDebug() << cursorPosX;

    overlay->move(cursorPosX + codeEditor->lineNumberArea->lineNumberWidth, cursorPosY + 8);
}

void TextEdit::keyPressEvent(QKeyEvent *event) {
    // Comportement normal : on laisse Qt insérer le texte
    QRect cursRect = cursorRect();
    QPoint cursorPos = cursRect.bottomRight();
    this->editor->cursorPosY = cursorPos.y();
    this->editor->cursorPosX = cursorPos.x();
    this->editor->updatePosition();

    int key = event->key();
    if (key != Qt::Key_Tab) {
        QPlainTextEdit::keyPressEvent(event);
        return;
    }
    QTextCursor cursor = textCursor();
    //QString txt = toPlainText();
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