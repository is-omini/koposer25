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
    p.setColor(QPalette::Highlight, QColor("#5c5d63"));
    p.setColor(QPalette::HighlightedText, QColor("#ffffff"));
    codeEditorInput->setPalette(p);

    HtmlHighlighter *highlighter = new HtmlHighlighter(codeEditorInput->document());

    codeEditorInput->setTabStopDistance(32);

    // Widget superposé
    overlay = new QWidget(this);
    overlay->setStyleSheet(
        "background-color: #2c2d30;"
    );
    //overlay->setGeometry(56, 50, 250, 32);

    listAuto = new VerticalBoxLayout(overlay);
    overlay->setLayout(listAuto);

    layout->addWidget(codeEditorInput);
    overlay->adjustSize();
    overlay->raise();
    overlay->hide();

    codeEditor = codeEditorInput;
};

void EditorCode::updatePosition() {
    overlay->move(cursorPosX + codeEditor->lineNumberArea->lineNumberWidth, cursorPosY + 8);
}

ButtonSvg *addButtonToSubMenu(
    VerticalBoxLayout* &layout,
    QWidget* &overlay,
    QString texteButton,
    QString texteButtonInsertEvent
) {
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->setParent(nullptr);
            delete child->widget();
        }
        delete child;
    }
    ButtonSvg *newButton = new ButtonSvg(texteButton, R"(
    <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
    <path d="M280-200v-80h284q63 0 109.5-40T720-420q0-60-46.5-100T564-560H312l104 104-56 56-200-200 200-200 56 56-104 104h252q97 0 166.5 63T800-420q0 94-69.5 157T564-200H280Z"/>
    </svg>
    )", 20, overlay);
    newButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(0, 120, 212, 0.3);"
        "   border: 1px solid rgba(0, 120, 212, 1.0);"
        "   color: white;"
        "   padding: 8px 8px;"
        "   margin: 0;"
        "   text-align: left;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(0, 120, 212, 0.8);"
        "}"
    );
    layout->addWidget(newButton);
    overlay->adjustSize();
    overlay->show();

    return newButton;
}

void TextEdit::keyPressEvent(QKeyEvent *event) {
    editor->overlay->hide();
    // Comportement normal : on laisse Qt insérer le texte
    QRect cursRect = cursorRect();
    QPoint cursorPos = cursRect.bottomRight();
    this->editor->cursorPosY = cursorPos.y();
    this->editor->cursorPosX = cursorPos.x();
    this->editor->updatePosition();

    QTextCursor cursor = textCursor();
    //QString txt = toPlainText();
    cursor.select(QTextCursor::LineUnderCursor);
    QString currentLine = cursor.selectedText();

    int key = event->key();
    ///if (key == Qt::Key_Space || key == Qt::Key_Return || key == Qt::Key_Enter) editor->overlay->hide();
    ///else editor->overlay->show();
    QString text = event->text();
    
    //else if (!text.isEmpty() && text == ">") editor->overlay->show();
    //else editor->overlay->hide();

    // Détection avec regex

    if(!text.isEmpty()) {
        QRegularExpression regex("<(h[1-6]|p|div|span|html)>");
        QRegularExpressionMatch match = regex.match(currentLine+text);

        QRegularExpression regexGetBaseExiste("<(h[1-6]|p|div|span|html)>(.*?)</\\1>");
        QRegularExpressionMatch matchExisteBase = regexGetBaseExiste.match(currentLine+text);

        if (match.hasMatch() && !matchExisteBase.hasMatch()) {
            int matchLength = match.capturedLength();
            QString tag = match.captured(1);
            QString newtext = (currentLine+text).replace(QString("<%1>").arg(tag), "");
            QString messButton = QString("Insert \"<%1>%2</%1>\"").arg(tag, newtext+text);
            if(tag == "html") messButton = "<html>....</html>";
            ButtonSvg *newButton = addButtonToSubMenu(
                editor->listAuto,
                editor->overlay,
                messButton,
                QString("<%1>%2</%1>").arg(tag, newtext)
            );

            newButton->connect(newButton, &QPushButton::clicked, [this, cursor, tag, newtext]() mutable {
                cursor.removeSelectedText();
                if(tag == "html") cursor.insertText("<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<title></title>\n\t<style>* { margin: 0; padding: 0; box-sizing: border-box; }</style>\n</head>\n<body>\n\n</body>\n</html>");
                else cursor.insertText(QString("<%1>%2</%1>").arg(tag, newtext));
                this->setTextCursor(cursor);

                editor->overlay->hide();
                QLayoutItem *child;
                while ((child = editor->listAuto->takeAt(0)) != nullptr) {
                    if (child->widget()) {
                        child->widget()->setParent(nullptr); // détache du layout
                        delete child->widget();              // supprime le widget
                    }
                    delete child; // supprime le QLayoutItem
                }
            });
            if (key == Qt::Key_Tab || key == Qt::Key_Return || key == Qt::Key_Enter) {
                cursor.removeSelectedText();
                if(tag == "html") cursor.insertText("<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<title></title>\n\t<style>* { margin: 0; padding: 0; box-sizing: border-box; }</style>\n</head>\n<body>\n\n</body>\n</html>");
                else cursor.insertText(QString("<%1>%2</%1>").arg(tag, newtext));
                setTextCursor(cursor);

                editor->overlay->hide();
                QLayoutItem *child;
                while ((child = editor->listAuto->takeAt(0)) != nullptr) {
                    if (child->widget()) {
                        child->widget()->setParent(nullptr); // détache du layout
                        delete child->widget();              // supprime le widget
                    }
                    delete child; // supprime le QLayoutItem
                }
            }
            QPlainTextEdit::keyPressEvent(event);
            return;
        } else if (!matchExisteBase.hasMatch()) {
            QString messButton = QString("Insert \"<p>%1</p>\"").arg(currentLine+text);
            addButtonToSubMenu(
                editor->listAuto,
                editor->overlay,
                messButton,
                QString("<p>%1</p>").arg(currentLine+text)
            );
        }
    }
    
    QPlainTextEdit::keyPressEvent(event);

    /*if (match.hasMatch()) {
        QString tag = match.captured(1);

        addButtonToSubMenu(
            editor->listAuto,
            editor->overlay,
            QString("Insert \"<p>%1\"</p>").arg(currentLine+text),
            QString("<p>%1</p>").arg(currentLine+text)
        );

        /*ButtonSvg *test = new ButtonSvg(QString("Insert \"<%1></%1>\"").arg(tag), R"(
        <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff">
        <path d="M280-200v-80h284q63 0 109.5-40T720-420q0-60-46.5-100T564-560H312l104 104-56 56-200-200 200-200 56 56-104 104h252q97 0 166.5 63T800-420q0 94-69.5 157T564-200H280Z"/>
        </svg>
        )", 20, editor->overlay);
        test->setStyleSheet(
            "QPushButton {"
            "   background-color: rgba(0, 120, 212, 0.3);"
            "   border: 1px solid rgba(0, 120, 212, 1.0);"
            "   color: white;"
            "   padding: 8px 8px;"
            "   margin: 0;"
            "   text-align: left;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(0, 120, 212, 0.8);"
            "}"
        );
        if(tag == "html") {
            test->connect(test, &QPushButton::clicked, [this, cursor]() mutable {
                cursor.removeSelectedText();
                cursor.insertText("<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<title></title>\n\t<style>* { margin: 0; padding: 0; box-sizing: border-box; }</style>\n</head>\n<body>\n\n</body>\n</html>");
                this->setTextCursor(cursor);

                editor->overlay->hide();
                QLayoutItem *child;
                while ((child = editor->listAuto->takeAt(0)) != nullptr) {
                    if (child->widget()) {
                        child->widget()->setParent(nullptr); // détache du layout
                        delete child->widget();              // supprime le widget
                    }
                    delete child; // supprime le QLayoutItem
                }
            });
        } else {
            test->connect(test, &QPushButton::clicked, [this, cursor, tag]() mutable {
                cursor.removeSelectedText();
                cursor.insertText(QString("<%1></%1>").arg(tag));
                cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, tag.length() + 3);
                this->setTextCursor(cursor);

                editor->overlay->hide();
                QLayoutItem *child;
                while ((child = editor->listAuto->takeAt(0)) != nullptr) {
                    if (child->widget()) {
                        child->widget()->setParent(nullptr); // détache du layout
                        delete child->widget();              // supprime le widget
                    }
                    delete child; // supprime le QLayoutItem
                }
            });
        }
        editor->listAuto->addWidget(test);
        editor->overlay->adjustSize();
        editor->overlay->show();*
    }

    if (key != Qt::Key_Tab) {
        QPlainTextEdit::keyPressEvent(event);
        return;
    }

    QPlainTextEdit::keyPressEvent(event);

    if (match.hasMatch()) {
        QString tag = match.captured(1); // Récupère le nom de la balise (h1, h2, etc.)
        int matchLength = match.capturedLength();
        //cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 0);
        cursor.removeSelectedText();
        if(tag == "html") {
            cursor.insertText("<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<title></title>\n\t<style>* { margin: 0; padding: 0; box-sizing: border-box; }</style>\n</head>\n<body>\n\n</body>\n</html>");
            cursor.movePosition(QTextCursor::End);
        } else {
            cursor.insertText(QString("<%1></%1>").arg(tag));
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, tag.length() + 3);
        }
        setTextCursor(cursor);
    } else QPlainTextEdit::keyPressEvent(event);
    */
}