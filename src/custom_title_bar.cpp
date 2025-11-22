#include "custom_title_bar.h"

CustomTitleBar::CustomTitleBar(QWidget *parent) : QWidget(parent) {
	setFixedHeight(30); // hauteur de la barre
	setStyleSheet("background-color: #2E86C1; color: white; border-radius: 42px;");

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setContentsMargins(5, 0, 5, 0);

	// Boutons
	QPushButton *minBtn = new QPushButton("_", this);
	QPushButton *maxBtn = new QPushButton("□", this);
	QPushButton *closeBtn = new QPushButton("X", this);

	minBtn->setFixedSize(30, 20);
	maxBtn->setFixedSize(30, 20);
	closeBtn->setFixedSize(30, 20);

	minBtn->setStyleSheet("background-color: #3498DB; color: white;");
	maxBtn->setStyleSheet("background-color: #3498DB; color: white;");
	closeBtn->setStyleSheet("background-color: #E74C3C; color: white;");

	layout->addWidget(closeBtn);
	layout->addWidget(maxBtn);
	layout->addWidget(minBtn);
	layout->addStretch();

	// Titre
	title = new QLabel("Fenêtre Personnalisée", this);
	layout->addWidget(title);

	// Connections
	connect(minBtn, &QPushButton::clicked, parent, &QWidget::showMinimized);
	connect(maxBtn, &QPushButton::clicked, [parent](){
		if(parent->isMaximized())
			parent->showNormal();
		else
			parent->showMaximized();
	});
	connect(closeBtn, &QPushButton::clicked, parent, &QWidget::close);
}

void CustomTitleBar::mousePressEvent(QMouseEvent *event) {
	if(event->button() == Qt::LeftButton) {
		dragging = true;
		dragPosition = event->globalPosition().toPoint() - parentWidget()->frameGeometry().topLeft();
		event->accept();
	}
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event) {
	if(dragging && (event->buttons() & Qt::LeftButton)) {
		parentWidget()->move(event->globalPosition().toPoint() - dragPosition);
		event->accept();
	}
}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent *event) {
	Q_UNUSED(event)
	dragging = false;
}