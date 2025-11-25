#include "contextMenuDreamMountain.h"
#include "windowDreamMountain.h"
#include <QApplication>

ContextMenuDreamMountain::ContextMenuDreamMountain(WindowDreamMountain *main, QWidget *parent): QWidget(parent) {
	setObjectName("contextMenu");
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	setStyleSheet(R"(
		QWidget {
			background-color: #1e1f22;
		}
		QPushButton {
			background-color: #1e1f22;
			border: 1px solid #1e1f22;
			color: white;
			padding: 5px 5px 5px 5px;
			margin: 0;
			text-align: left;
		}
		QPushButton:hover {
			background-color: #2c2d30;
		}
	)");

	contextMenuDreamMountainList = new QVBoxLayout(this);
	contextMenuDreamMountainList->setSpacing(5);
	contextMenuDreamMountainList->setContentsMargins(0,0,0,0);
	this->setLayout(contextMenuDreamMountainList);

	QWidget* manusWidget = new QWidget(this);
	QVBoxLayout* manusLayout = new QVBoxLayout(manusWidget);
	manusLayout->setContentsMargins(0,0,0,0);
	manusLayout->setSpacing(0);

	for (int i = 0; i < 3; ++i) {
		Button* btn = new Button("Teste");
		manusLayout->addWidget(btn);
	}

	contextMenuDreamMountainList->addWidget(manusWidget);

	adjustSize();
	update();

	
	setMinimumWidth(200);
	//setMinimumHeight(20);

	//adjustSize();
	//show();

	raise();
}

void ContextMenuDreamMountain::clearOverlay() {
	hide();
	QLayoutItem *child;
	while ((child = contextMenuDreamMountainList->takeAt(0)) != nullptr) {
		if (child->widget()) {
			child->widget()->setParent(nullptr);
			delete child->widget();
		}
		delete child;
	}
	adjustSize();
}

bool ContextMenuDreamMountain::getContextMenu(QWidget* widget, QPoint localPos) {
	qDebug() << widget;
	Button* btn = qobject_cast<Button*>(widget);
	TextEditor* text_editor = qobject_cast<TextEditor*>(widget);

	clearOverlay();
	hSize = 32;
	if(btn) updateListOverlay(btn->getContextMenu());
	if(text_editor) updateListOverlay(text_editor->getContextMenu());


	///QWidget* clickedWidget = QApplication::widgetAt(QCursor::pos());
	int x = widget->x();
	int y = widget->y();

	QPoint globalPos = QCursor::pos();
	QPoint localPos_ = parentWidget()->mapFromGlobal(globalPos);
	move(localPos_);

	// tmp
	//if(hSize < 10) hSize = 100;
	//move(x, y);

	qDebug() << "height : " << height();
	qDebug() << "width : " << width();


	return true;
}

void ContextMenuDreamMountain::updateListOverlay(QVector<Button*> contextMenu) {
	QWidget* manusWidget = new QWidget(this);
	QVBoxLayout* manusLayout = new QVBoxLayout(manusWidget);
	manusLayout->setContentsMargins(0,0,0,0);
	manusLayout->setSpacing(0);

	for (Button* b : contextMenu) {
		QString svg = b->getSvg();
		if(svg.isEmpty() || svg == nullptr) svg = R"(<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M224.62-160q-27.62 0-46.12-18.5Q160-197 160-224.62V-360h40v135.38q0 9.24 7.69 16.93 7.69 7.69 16.93 7.69H360v40H224.62Zm510.76 0H600v-40h135.38q9.24 0 16.93-7.69 7.69-7.69 7.69-16.93V-360h40v135.38q0 27.62-18.5 46.12Q763-160 735.38-160ZM160-735.38q0-27.62 18.5-46.12Q197-800 224.62-800H360v40H224.62q-9.24 0-16.93 7.69-7.69 7.69-7.69 16.93V-600h-40v-135.38Zm640 0V-600h-40v-135.38q0-9.24-7.69-16.93-7.69-7.69-16.93-7.69H600v-40h135.38q27.62 0 46.12 18.5Q800-763 800-735.38ZM481.54-271.54q13.31 0 22.42-9.11 9.12-9.12 9.12-22.43 0-13.3-9.12-22.42-9.11-9.12-22.42-9.12-13.31 0-22.42 9.12-9.12 9.12-9.12 22.42 0 13.31 9.12 22.43 9.11 9.11 22.42 9.11Zm-20.62-132.23h38.39q1.54-25.54 9.92-42 8.39-16.46 32.31-40.38 30.38-30.39 41.88-51.12 11.5-20.73 11.5-46.11 0-46.31-31.3-75.7-31.31-29.38-80.54-29.38-39.23 0-69.46 19.84-30.24 19.85-47 57.08l36.76 15.46q10.85-25.23 31.5-40.19 20.66-14.96 46.66-14.96 32.84 0 53.81 18.96 20.96 18.96 20.96 49.58 0 18.46-9.12 34.81-9.11 16.34-31.34 36.11-29.93 28.23-42.43 52.15-12.5 23.93-12.5 55.85Z"/></svg>)";
		Button* btn = new Button(b->text(), svg, 24);

		connect(btn, &QPushButton::clicked, this, &QWidget::hide);
		connect(btn, &QPushButton::clicked, b, &QPushButton::clicked);
	    connect(btn, &QPushButton::pressed, b, &QPushButton::pressed);
	    connect(btn, &QPushButton::released, b, &QPushButton::released);
	    connect(btn, &QPushButton::toggled, b, &QPushButton::toggled);

		manusLayout->addWidget(btn);
	}

	contextMenuDreamMountainList->addWidget(manusWidget);

	adjustSize();
	update();
	show();
	//raise();

	/*QWidget* manusWidget = new QWidget(this);
	QVBoxLayout* manusLayout = new QVBoxLayout(manusWidget);
	manusLayout->setContentsMargins(0,0,0,0);
	manusLayout->setSpacing(2);
	for (Button* b : contextMenu) {
		Button* btn = new Button(b->text(), b->getSvg(), b->iconSize().width(), this);
		manusLayout->addWidget(btn);
	}
	contextMenuDreamMountainList->addWidget(manusWidget);*/
}

/*
void contextMenuDreamMountain::test() {
	if (event->button() != Qt::RightButton) {
		QWidget::mousePressEvent(event);
		return;
	}

	QPoint localPos = mapFromGlobal(QCursor::pos());
	QWidget* child = childAt(localPos);
	qDebug() << "hello";

	if(!child) {
		qDebug() << child;
		return;
	}

	int hSize = 0;
	QLayoutItem *item;
	while ((item = contextMenuDreamMountainList->takeAt(0)) != nullptr) {
		if (item->widget()) {
			item->widget()->deleteLater();
		}
		delete item;
	}
	
	Button* btn = qobject_cast<Button*>(child);
	TextEditor* text_editor = qobject_cast<TextEditor*>(child);
	//QVector<Button*> contextMenu;
	if(btn) {
		qDebug() << "hello YES";
		QVector<Button*> contextMenu = btn->getContextMenu();

	for (Button* b : contextMenu) {
		Button* newBtn = new Button(b->text(), b->getSvg(), b->iconSize().width(), contextMenuDreamMountain);
		newBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		contextMenuDreamMountainList->addWidget(newBtn);
		hSize += newBtn->height();
	}
	}

	int x = localPos.x();
	int y = localPos.y();

	if(hSize < 10) hSize = 100;

	move(x, y);
	setFixedHeight(hSize);
	show();
	adjustSize();
	update();   // force un repaint
	repaint(); 
}
*/