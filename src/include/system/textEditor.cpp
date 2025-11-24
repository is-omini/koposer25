#include "textEditor.h"

#include "../codeEditorDreamMountain.h"
#include "../iconDreamMountain.h"

#include <QRect>
#include <QRegularExpression>
#include <QPushButton>

TextEditor::TextEditor(CodeEditorDreamMountain* parentEdit, QWidget *parent) : QPlainTextEdit(parent) {
	textEditorParent = parentEdit;
	lineNumberArea = new LineNumberArea(this, this);
	connect(this, &QPlainTextEdit::blockCountChanged, this, &TextEditor::updateLineNumberAreaWidth);
	connect(this, &QPlainTextEdit::updateRequest, this, &TextEditor::updateLineNumberArea);
	updateLineNumberAreaWidth(0);
}


int TextEditor::lineNumberAreaWidth() {
	int digits = QString::number(blockCount()).length();
	return 3 + 32 + fontMetrics().horizontalAdvance('9') * digits;
}

void TextEditor::resizeEvent(QResizeEvent *event) {
	QPlainTextEdit::resizeEvent(event);
	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}
void TextEditor::updateLineNumberAreaWidth(int) {
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}
void TextEditor::updateLineNumberArea(const QRect &rect, int dy) {
	if(dy) lineNumberArea->scroll(0, dy);
	else lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
}

void TextEditor::keyPressEvent(QKeyEvent *event) {
	textEditorParent->clearOverlay();
	QRect cursRect = cursorRect();
	QPoint cursorPos = cursRect.bottomRight();

	cursorPosY = cursorPos.y();
	cursorPosX = cursorPos.x();
	textEditorParent->updatePosition();

	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::LineUnderCursor);
	QString currentLine = cursor.selectedText();

	int key = event->key();
	QString text = event->text();

	if(!text.isEmpty()) {
		QRegularExpression regex("<(h[1-6]|p|div|span|html)>");
		QRegularExpressionMatch match = regex.match(currentLine+text);

		QRegularExpression regexGetBaseExiste("<(h[1-6]|p|div|span|html)>(.*?)</\\1>");
		QRegularExpressionMatch matchExisteBase = regexGetBaseExiste.match(currentLine+text);

		if (match.hasMatch() && !matchExisteBase.hasMatch()) {
			int matchLength = match.capturedLength();
			QString tag = match.captured(1);
			QString newtext = (currentLine).replace(QString("<%1>").arg(tag), "");
			QString messButton = QString("Insert \"<%1>%2</%1>\"").arg(tag, newtext+text);
			if(tag == "html") messButton = "<html>....</html>";
			QPushButton *newButton = textEditorParent->createButtonToOverlay(
				messButton,
				iconFolder,
				16
			);
			textEditorParent->appendButtonToOverlay(newButton);

			if (key == Qt::Key_Tab || key == Qt::Key_Return || key == Qt::Key_Enter) {
				cursor.removeSelectedText();
				if(tag == "html") cursor.insertText("<!DOCTYPE html>\n<html>\n<head>\n\t<meta charset=\"utf-8\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<title></title>\n\t<style>* { margin: 0; padding: 0; box-sizing: border-box; }</style>\n</head>\n<body>\n\n</body>\n</html>");
				else cursor.insertText(QString("<%1>%2</%1>").arg(tag, newtext));
				setTextCursor(cursor);
				textEditorParent->clearOverlay();
				QPlainTextEdit::keyPressEvent(event);
				return;
			}
		} else if (!matchExisteBase.hasMatch()) {
			QString messButton = QString("Insert \"<p>%1</p>\"").arg(currentLine+text);
			QPushButton *newButton = textEditorParent->createButtonToOverlay(
				messButton,
				iconFolder,
				16
			);
			textEditorParent->appendButtonToOverlay(newButton);
		}
	}


	QPlainTextEdit::keyPressEvent(event);
}