#include "webViewVisualConstructDreamMountain.h"


#include <QWidget>
#include <QScrollArea>

WVVisualConstructDrM::WVVisualConstructDrM(QWidget* parent) : QWidget(parent) {
	setStyleSheet("background-color: #2c2d30; color: #fff;");

	qDebug() << "HEllow";

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	QWidget* wis1 = new QWidget();
	wis1->setFixedHeight(32);

	QWidget* wis2 = new QWidget();

	QVBoxLayout *layout_ = new QVBoxLayout(wis2);
	layout_->setContentsMargins(0,0,0,0);
	layout_->setSpacing(0);

	QScrollArea* scroll = new QScrollArea(wis2);
	scroll->setWidgetResizable(true);
	scroll->setFrameShape(QFrame::NoFrame);

	QWidget* contenaireExplorere = new QWidget(scroll);
	contenaireExplorere->setObjectName("contenaireExplorere");

	layoutConteneur = new QVBoxLayout(contenaireExplorere);
	layoutConteneur->setContentsMargins(0,0,0,0);
	layoutConteneur->setSpacing(2);

	layoutConteneur->addStretch();

	scroll->setWidget(contenaireExplorere);
	layout_->addWidget(scroll);

	layout->addWidget(wis1);
	layout->addWidget(wis2);
}