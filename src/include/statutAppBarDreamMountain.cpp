#include "statutAppBarDreamMountain.h"
#include "windowDreamMountain.h"
#include "colorDreamMountain.h"
#include "iconDreamMountain.h"

#include <QScrollArea>

Button* StatutAppBarDreamMountain::AppendButtonList(
	QString string,
	QString Svg,
	int svgSize,
	QString css
){
	Button *newButton = new Button(string);
	newButton->setObjectName("newButton");
	if(!css.isEmpty()) newButton->setStyleSheet(css);
	else {
		newButton->setStyleSheet(
			"#newButton {"
			"	background-color: #25282d;"
			"	color: white;"
			"	padding: 8px 16px;"
			"	margin: 0;"
			"	text-align: center;"
			"}"
			"#newButton:hover {"
			"	background-color: #4a4b4e;"
			"}"
		);
	} 
	if(!Svg.isEmpty()) {
		QSvgRenderer renderer(Svg.toUtf8());
		QPixmap pixmap(svgSize, svgSize);
		pixmap.fill(Qt::transparent);         // fond transparent
		QPainter painter(&pixmap);
		renderer.render(&painter);
		QIcon icon(pixmap);  // chemin vers ton fichier SVG
		newButton->setIcon(icon);
		newButton->setIconSize(QSize(svgSize, svgSize));
	}

	return newButton;
}

void StatutAppBarDreamMountain::UpdateButtonListRight() {
	for (Button* btn : rightButtonList) {
		btn->setCursor(Qt::PointingHandCursor);
		layoutRightStatutAppBarButtonList->addWidget(btn);
	}

	adjustSize();
}

void StatutAppBarDreamMountain::UpdateButtonListLeft() {
	for (QPushButton* btn : leftButtonList) {
		btn->setCursor(Qt::PointingHandCursor);
		layoutLeftStatutAppBarButtonList->addWidget(btn);
	}

}

StatutAppBarDreamMountain::StatutAppBarDreamMountain(WindowDreamMountain *main, QWidget *parent) : QWidget(parent) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	windowParentApp = main;

	QHBoxLayout *layoutStatutAppBarContent = new QHBoxLayout(this);
	layoutStatutAppBarContent->setContentsMargins(4,4,4,4);
	layoutStatutAppBarContent->setSpacing(0);

	widgetLeftStatutAppBarButtonList = new QWidget();
	widgetLeftStatutAppBarButtonList->setStyleSheet("background-color: "+windowBackgoundColor+";");
	widgetLeftStatutAppBarButtonList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	layoutLeftStatutAppBarButtonList = new QHBoxLayout(widgetLeftStatutAppBarButtonList);
	layoutLeftStatutAppBarButtonList->setContentsMargins(0,0,0,0);
	layoutLeftStatutAppBarButtonList->setSpacing(0);

	//widgetRightStatutAppBarButtonList = new QWidget();
	//widgetRightStatutAppBarButtonList->setStyleSheet("background-color: red;");
	//layoutRightStatutAppBarButtonList = new QHBoxLayout(widgetRightStatutAppBarButtonList);
	//layoutRightStatutAppBarButtonList->setContentsMargins(0,0,0,0);
	//layoutRightStatutAppBarButtonList->setSpacing(0);

	QScrollArea* scroll = new QScrollArea(this);
    scroll->setFixedHeight(32); 
	///scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // vertical invisible
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // horizontal invisible
	scroll->setWidgetResizable(true);
	scroll->setFrameShape(QFrame::NoFrame);
	scroll->setStyleSheet(scrollBarWindow);
	scroll->setWidget(widgetLeftStatutAppBarButtonList);
	scroll->adjustSize();

	Button* test3 = AppendButtonList(
		nullptr,
		iconFile,
		16,
		R"(
		QPushButton {
			background-color: #25282d;
			color: #fff;
			padding: 8px;
			border-radius: 5px;
			height: 16px;
			width: 16px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		})"
	);
	leftButtonList.append(test3);
	UpdateButtonListLeft();

	//layoutStatutAppBarContent->addWidget(widgetLeftStatutAppBarButtonList);
	//layoutStatutAppBarContent->addWidget(scroll, 1);
	layoutStatutAppBarContent->addWidget(scroll, 1);

	layoutLeftStatutAppBarButtonList->addStretch();
}