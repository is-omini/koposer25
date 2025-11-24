#ifndef LINENUMBERAREASYSTSEM_H
#define LINENUMBERAREASYSTSEM_H

class TextEditor;

#include "textEditor.h"

class LineNumberArea : public QWidget {
public:
	int lineNumberWidth;
	explicit LineNumberArea(TextEditor *editor, QWidget *parent = nullptr);
protected:
	void paintEvent(QPaintEvent *event) override;
private:
	TextEditor *textEdit;
	QWidget *overlay;
};
#endif