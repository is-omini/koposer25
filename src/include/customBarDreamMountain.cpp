#include "windowDreamMountain.h"
#include "customBarDreamMountain.h"
#include "iconDreamMountain.h"

#include <Qt>
#include <QWidget>

#include <QMouseEvent>
#include <QHBoxLayout>
#include <QPushButton>

QPushButton* CustomBarDreamMountain::AppendButtonList(
	QString string,
	QString Svg,
	int svgSize,
	QString css
){
	QPushButton *newButton = new QPushButton(string);
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
		pixmap.fill(Qt::transparent);		 // fond transparent
		QPainter painter(&pixmap);
		renderer.render(&painter);
		QIcon icon(pixmap);  // chemin vers ton fichier SVG
		newButton->setIcon(icon);
		newButton->setIconSize(QSize(svgSize, svgSize));
	}

	return newButton;
}

void CustomBarDreamMountain::AppendButtonListLeft(
	QString string,
	QString Svg,
	int svgSize,
	QString css
){
	QPushButton *newButton = new QPushButton(string);
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
		pixmap.fill(Qt::transparent);		 // fond transparent
		QPainter painter(&pixmap);
		renderer.render(&painter);
		QIcon icon(pixmap);  // chemin vers ton fichier SVG
		newButton->setIcon(icon);
		newButton->setIconSize(QSize(svgSize, svgSize));
	}
	leftButtonList.append(newButton);
}

void CustomBarDreamMountain::AppendButtonListRight(
	QString string,
	QString Svg,
	int svgSize,
	QString css
){
	QPushButton *newButton = new QPushButton(string);
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
		pixmap.fill(Qt::transparent);		 // fond transparent
		QPainter painter(&pixmap);
		renderer.render(&painter);
		QIcon icon(pixmap);  // chemin vers ton fichier SVG
		newButton->setIcon(icon);
		newButton->setIconSize(QSize(svgSize, svgSize));
	}

	rightButtonList.append(newButton);
}

void CustomBarDreamMountain::UpdateButtonListRight() {
	for (QPushButton* btn : rightButtonList) {
		btn->setCursor(Qt::PointingHandCursor);
		layoutRightButtonList->addWidget(btn);
	}
	layoutRightButtonList->addStretch();
}

void CustomBarDreamMountain::UpdateButtonListLeft() {
	//QLayoutItem *child;
	//while ((child = layoutLeftButtonList->takeAt(0)) != nullptr) {
	//	// Ne pas supprimer les widgets, juste les retirer du layout
	//	delete child;
	//}

	for (QPushButton* btn : leftButtonList) {
		btn->setCursor(Qt::PointingHandCursor);
		layoutLeftButtonList->addWidget(btn);
	}
	layoutLeftButtonList->addStretch();
}

CustomBarDreamMountain::CustomBarDreamMountain(WindowDreamMountain *main, QWidget *parent) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setStyleSheet(R"(
		#windowCloseButton,
		#windowMinizeButton,
		#windowFullsizeButton {
			width: 12px;
			height: 12px;
			padding: 0px;

			background-color: #5c5d63;
			border: 1px solid #1e1f22;
			border-radius: 6px;

			font-size: 10px;

			margin-top: 8px;
			margin-bottom: 8px;
		}

		#windowCloseButton:hover { background-color: #FF5F57; border: 1px solid #CC4C46; }
		#windowMinizeButton:hover { background-color: #FEBC2E;  border: 1px solid #CB9725; }
		#windowFullsizeButton:hover { background-color: #28C840; border: 1px solid #20A033; }
	)");

	windowParentApp = main;

	// widgetCustomeBarButton

	QHBoxLayout *layoutCustomeBarContent = new QHBoxLayout(this);
	layoutCustomeBarContent->setContentsMargins(4,4,4,4);
	layoutCustomeBarContent->setSpacing(8);

	widgetLeftButtonList = new QWidget();
	widgetLeftButtonList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layoutLeftButtonList = new QHBoxLayout(widgetLeftButtonList);
	layoutLeftButtonList->setContentsMargins(0,0,0,0);
	layoutLeftButtonList->setSpacing(8);

	widgetCustomeBarButtonWindow = new QWidget();
	layoutCustomeBarButtonWindow = new QHBoxLayout(widgetCustomeBarButtonWindow);
	layoutCustomeBarButtonWindow->setContentsMargins(8,0,0,0);
	// setContentsMargins(left, top, right, bottom);
	layoutCustomeBarButtonWindow->setSpacing(8);
	layoutLeftButtonList->addWidget(widgetCustomeBarButtonWindow);

	layoutCustomeBarContent->addWidget(widgetLeftButtonList);


	QPushButton *windowCloseButton = new QPushButton();
	windowCloseButton->setObjectName("windowCloseButton");
	QObject::connect(windowCloseButton, &QPushButton::clicked, [this]() { window()->close(); });
	layoutCustomeBarButtonWindow->addWidget(windowCloseButton);

	QPushButton *windowMinizeButton = new QPushButton();
	windowMinizeButton->setObjectName("windowMinizeButton");
	QObject::connect(windowMinizeButton, &QPushButton::clicked, [this]() {  window()->showMinimized(); });
	layoutCustomeBarButtonWindow->addWidget(windowMinizeButton);

	QPushButton *windowFullsizeButton = new QPushButton();
	windowFullsizeButton->setObjectName("windowFullsizeButton");
	QObject::connect(windowFullsizeButton, &QPushButton::clicked, [this]() {
		QWidget *w = window();
		if (w->windowState() & Qt::WindowFullScreen) {
			w->setWindowState(Qt::WindowNoState);
		} else {
			w->setWindowState(Qt::WindowFullScreen);
		}
	});
	layoutCustomeBarButtonWindow->addWidget(windowFullsizeButton);
	//layoutCustomeBarButtonWindow->addStretch();

	///


	layoutCustomeBarContent->addStretch();

	widgetRightButtonList = new QWidget();
	widgetRightButtonList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layoutRightButtonList = new QHBoxLayout(widgetRightButtonList);
	layoutRightButtonList->setContentsMargins(12,0,0,0);
	layoutRightButtonList->setSpacing(0);
	layoutCustomeBarContent->addWidget(widgetRightButtonList);

	QPushButton* sourceBn = AppendButtonList(
		"Source",
		nullptr,
		12,
		R"(
		QPushButton {
			background-color: #25282d;
			color: #fff;
			padding: 8px 16px;
			border-top-left-radius: 5px;
			border-bottom-left-radius: 5px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		}
		)"
	);
	rightButtonList.append(sourceBn);
	QPushButton* visualBn = AppendButtonList(
		"Source",
		nullptr,
		12,
		R"(
		QPushButton {
			background-color: #25282d;
			color: #fff;
			padding: 8px 16px;
			border-top-right-radius: 5px;
			border-bottom-right-radius: 5px;
			margin: 0;
			text-align: center;
		}
		QPushButton:hover {
			background-color: #4a4b4e;
		}
		)"
	);
	rightButtonList.append(visualBn);


	QPushButton* test1 = AppendButtonList(
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
	leftButtonList.append(test1);
	CustomBarDreamMountain::UpdateButtonListRight();

	adjustSize();
}

void CustomBarDreamMountain::mousePressEvent(QMouseEvent *event) {
	if(event->button() == Qt::LeftButton) {

	windowMove = true;
	windowMovePosition = event->globalPosition().toPoint() - window()->frameGeometry().topLeft();
	event->accept();

	}
}

void CustomBarDreamMountain::mouseMoveEvent(QMouseEvent *event) {
	if(windowMove && (event->buttons() & Qt::LeftButton)) {
	window()->move(event->globalPosition().toPoint() - windowMovePosition);
	event->accept();
	}
}

void CustomBarDreamMountain::mouseReleaseEvent(QMouseEvent *event) {
	Q_UNUSED(event)
	windowMove = false;
}


void CustomBarDreamMountain::hideCustumeBar() {
	windowParentApp->hideRedoundWindowBorder();
	this->widgetCustomeBarButtonWindow->hide();
}
void CustomBarDreamMountain::showCustumeBar() {
	windowParentApp->showRedoundWindowBorder();
	this->widgetCustomeBarButtonWindow->show();
}
