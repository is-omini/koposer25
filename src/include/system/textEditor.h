#ifndef TEXTPLAINSYSTSEM_H
#define TEXTPLAINSYSTSEM_H

#include <QPlainTextEdit>
#include <QWidget>

class LineNumberArea;
class CodeEditorDreamMountain;

#include "lineNumberArea.h"

class TextEditor: public QPlainTextEdit {
public:
	explicit TextEditor(CodeEditorDreamMountain* parentEdit, QWidget *parent = nullptr);

	int lineNumberAreaWidth();

	void updatePosition();

	// SETTER @ GETTER
	int getCursorPosY() { return cursorPosY; }
	int getCursorPosX() { return cursorPosX; }

	LineNumberArea *getLineNumberArea() { return lineNumberArea; };

protected:
	void resizeEvent(QResizeEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;

private slots:
	void updateLineNumberAreaWidth(int);

	void updateLineNumberArea(const QRect &rect, int dy);
private:
	LineNumberArea *lineNumberArea;

	CodeEditorDreamMountain* textEditorParent;

	friend class LineNumberArea;

	int cursorPosY;
	int cursorPosX;
};
#endif