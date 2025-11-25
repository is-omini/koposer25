#ifndef TEXTPLAINSYSTSEM_H
#define TEXTPLAINSYSTSEM_H

#include <QPlainTextEdit>
#include <QWidget>

#include "../interfaceDreamMountain.h"

class LineNumberArea;
class CodeEditorDreamMountain;

#include "lineNumberArea.h"

class TextEditor: public QPlainTextEdit {
	Q_OBJECT
public:
	explicit TextEditor(CodeEditorDreamMountain* parentEdit, QWidget *parent = nullptr);

	int lineNumberAreaWidth();

	void updatePosition();

	// SETTER @ GETTER
	int getCursorPosY() { return cursorPosY; }
	int getCursorPosX() { return cursorPosX; }

	LineNumberArea *getLineNumberArea() { return lineNumberArea; };

	QVector<Button*> getContextMenu() {
		return contextMenuButtons;
	}

protected:
	void resizeEvent(QResizeEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;

	/* void mousePressEvent(QMouseEvent *event) override {
		if(event->button() == Qt::RightButton) {
			///QWidget::mousePressEvent(event);
			return;
		}
		QWidget::mousePressEvent(event); // passe l’événement au parent si nécessaire
	} */

private slots:
	void updateLineNumberAreaWidth(int);

	void updateLineNumberArea(const QRect &rect, int dy);
private:
	QVector<Button*> contextMenuButtons;

	LineNumberArea *lineNumberArea;

	CodeEditorDreamMountain* textEditorParent;

	friend class LineNumberArea;

	int cursorPosY;
	int cursorPosX;
};
#endif