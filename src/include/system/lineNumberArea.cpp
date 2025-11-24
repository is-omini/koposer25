#include "lineNumberArea.h"
#include "../colorDreamMountain.h"

#include <QPainter>
#include <QTextBlock>

LineNumberArea::LineNumberArea(TextEditor *editor, QWidget *parent) : QWidget(parent), textEdit(editor) {}

void LineNumberArea::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.fillRect(event->rect(), QColor(colorBackgroundInput));

	QTextBlock block = textEdit->firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)textEdit->blockBoundingGeometry(block).translated(textEdit->contentOffset()).top();
	int bottom = top + (int)textEdit->blockBoundingRect(block).height();

	while(block.isValid() && top <= event->rect().bottom()) {
		if(block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(QColor("#4d4e51"));
			lineNumberWidth = qMax(32, width()-16);
			painter.drawText(0, top, lineNumberWidth, textEdit->fontMetrics().height(), Qt::AlignRight, number);
		}
		block = block.next();
		top = bottom;
		bottom = top + (int)textEdit->blockBoundingRect(block).height();
		++blockNumber;
	}
}