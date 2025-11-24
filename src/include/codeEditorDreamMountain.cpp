#include "codeEditorDreamMountain.h"
#include "colorDreamMountain.h"
#include "iconDreamMountain.h"

#include <QVBoxLayout>

#include <QPushButton>
#include <QSvgRenderer>
#include <QPainter>

CodeEditorDreamMountain::CodeEditorDreamMountain(QWidget *parent) : QWidget(parent) {
	setStyleSheet(
		"background-color: "+colorBackgroundInput+";"
		"color: white;"
	);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	textEditorSystem = new TextEditor(this);
	textEditorSystem->setStyleSheet(scrollBarInput);

	QFont textEditorFont = textEditorSystem->font();
	textEditorFont.setPointSizeF(14);
	textEditorFont.setLetterSpacing(QFont::PercentageSpacing, 105);
	textEditorSystem->setFont(textEditorFont);

	QPalette textEditorPaeltte = textEditorSystem->palette();
	textEditorPaeltte.setColor(QPalette::Highlight, QColor(colorHighlight));
	textEditorPaeltte.setColor(QPalette::HighlightedText, QColor(colorWhite));
	textEditorSystem->setPalette(textEditorPaeltte);

	textEditorSystem->setTabStopDistance(32);

	layout->addWidget(textEditorSystem);

	// Widget superposé
	menuDeroulantCodeEditor = new QWidget(this);
	menuDeroulantCodeEditor->setStyleSheet(
		"background-color: #2c2d30;"
	);

	menuDeroulantCodeEditorList = new QVBoxLayout(menuDeroulantCodeEditor);
	menuDeroulantCodeEditorList->setContentsMargins(0,0,0,0);
	menuDeroulantCodeEditorList->setSpacing(0);
	menuDeroulantCodeEditor->setMinimumWidth(200);

	menuDeroulantCodeEditor->adjustSize();
	menuDeroulantCodeEditor->raise();
	menuDeroulantCodeEditor->hide();
}

void CodeEditorDreamMountain::updatePosition() {
	menuDeroulantCodeEditor->move(textEditorSystem->getCursorPosX() + textEditorSystem->getLineNumberArea()->lineNumberWidth, textEditorSystem->getCursorPosY() + 8);
}

void CodeEditorDreamMountain::clearOverlay() {
	menuDeroulantCodeEditor->hide();
	QLayoutItem *child;
	while ((child = menuDeroulantCodeEditorList->takeAt(0)) != nullptr) {
		if (child->widget()) {
			child->widget()->setParent(nullptr);
			delete child->widget();
		}
		delete child;
	}
	menuDeroulantCodeEditor->adjustSize();
}

QPushButton* CodeEditorDreamMountain::createButtonToOverlay(
	QString string,
	QString Svg,
	int svgSize,
	QString css
) {
	clearOverlay();
	QPushButton *newButton = new QPushButton(string);
	newButton->setObjectName("newButton");
	if(!css.isEmpty()) newButton->setStyleSheet(css);
	else {
		newButton->setStyleSheet(
			"#newButton {"
			"	color: white;"
			"	padding: 8px;"
			"	margin: 0;"
			"	text-align: left;"
			"}"
			"#newButton:hover {"
			"	background-color: #4a4b4e;"
			"}"
		);
	} 
	if(!Svg.isEmpty()) {
		QSvgRenderer renderer(Svg.toUtf8());
		QPixmap pixmap(svgSize, svgSize);
		pixmap.fill(Qt::transparent);
		QPainter painter(&pixmap);
		renderer.render(&painter);
		QIcon icon(pixmap);
		newButton->setIcon(icon);
		newButton->setIconSize(QSize(svgSize, svgSize));
	}

	return newButton;
}