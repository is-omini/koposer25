#include "webViewVisualConstructDreamMountain.h"
#include "interfaceDreamMountain.h"
#include "windowDreamMountain.h"


#include <QWidget>
#include <QScrollArea>
#include <QString>

#include <QHBoxLayout>

WVVisualConstructDrM::WVVisualConstructDrM(WindowDreamMountain *main,QWidget* parent) : QWidget(parent) {
	windowParentApp = main;
	setStyleSheet("background-color: #2c2d30; color: #fff;");

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	QWidget* wis1 = new QWidget();
	//wis1->setFixedHeight(32);
	wis1->setStyleSheet(R"(
		QPushButton {
			background-color: transparent;
			border: none;
			text-align: left;
			border-bottom: solid 1px blue;
			border-radius: 4px;
			padding: 8px 14px;
		}

		QPushButton:hover {
			background-color: #1e1f22;
		}
	)");

	QHBoxLayout* layoutConteneur_ = new QHBoxLayout(wis1);
	layoutConteneur_->setContentsMargins(4,4,4,4);
	layoutConteneur_->setSpacing(0);

	Button *error = new Button("Error", nullptr, 0);
	layoutConteneur_->addWidget(error);
	error->setCursor(Qt::PointingHandCursor);

	Button *warning = new Button("Warning", nullptr, 0);
	layoutConteneur_->addWidget(warning);
	warning->setCursor(Qt::PointingHandCursor);

	Button *logs = new Button("Logs", nullptr, 0);
	layoutConteneur_->addWidget(logs);
	logs->setCursor(Qt::PointingHandCursor);

	layoutConteneur_->addStretch();

	Button *zoomInt = new Button("100%", nullptr, 0);
	zoomInt->setCursor(Qt::PointingHandCursor);

	Button *zoom = new Button("", R"(<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M460-460H240v-40h220v-220h40v220h220v40H500v220h-40v-220Z"/></svg>)", 16);
	zoom->setCursor(Qt::PointingHandCursor);
	wis1->setStyleSheet(R"(
		QPushButton {
			background-color: transparent;
			border: none;
			text-align: left;
			border-bottom: solid 1px blue;
			border-radius: 4px;
			padding: 8px;
		}

		QPushButton:hover {
			background-color: #1e1f22;
		}
	)");
	zoom->connect(zoom, &Button::clicked, [=](){
    	windowParentApp->getAppContentDreamMountain()->getWebViewAppDreamMountain()->getWebEngineSystem()->zoomIn();
		qreal currentZoom = windowParentApp->getAppContentDreamMountain()->getWebViewAppDreamMountain()->getWebEngineSystem()->zoomCurrent();
		QString currentZoomString = QString::number(currentZoom * 100) + "%";
		zoomInt->setText(currentZoomString);
	});

	Button *unZoom = new Button("", R"(<svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M240-460v-40h480v40H240Z"/></svg>)", 16);
	unZoom->setCursor(Qt::PointingHandCursor);
	unZoom->connect(unZoom, &Button::clicked, [=](){
		windowParentApp->getAppContentDreamMountain()->getWebViewAppDreamMountain()->getWebEngineSystem()->zoomOut();
		qreal currentZoom = windowParentApp->getAppContentDreamMountain()->getWebViewAppDreamMountain()->getWebEngineSystem()->zoomCurrent();
		QString currentZoomString = QString::number(currentZoom * 100) + "%";
		zoomInt->setText(currentZoomString);
	});
	wis1->setStyleSheet(R"(
		QPushButton {
			background-color: transparent;
			border: none;
			text-align: left;
			border-bottom: solid 1px blue;
			border-radius: 4px;
			padding: 8px;
		}

		QPushButton:hover {
			background-color: #1e1f22;
		}
	)");

	
	zoomInt->connect(zoomInt, &Button::clicked, [=]() {
    	QString btnText = zoomInt->text();   // Toujours lire depuis l'objet

		qreal currentZoom = windowParentApp->getAppContentDreamMountain()
			->getWebViewAppDreamMountain()
			->getWebEngineSystem()
			->zoomCurrent();

		int webEngineWidth = windowParentApp->getAppContentDreamMountain()
				->getWebViewAppDreamMountain()
				->getWebEngineSystem()->width(); 

		int webEngineheight = windowParentApp->getAppContentDreamMountain()
				->getWebViewAppDreamMountain()
				->getWebEngineSystem()->height(); 

		QString currentZoomString = QString::number(currentZoom * 100) + "%";

		qDebug()
		<< "height"
		<<  QString::number((webEngineheight/(currentZoom)), 'f', 0)

		<< "width"
		<<  QString::number((webEngineWidth/(currentZoom)), 'f', 0);

		//qDebug() << btnText << "==" << currentZoomString;
		if (btnText == currentZoomString) btnText = QString::number((webEngineWidth/(currentZoom)), 'f', 0)+"x"+QString::number((webEngineheight/(currentZoom)), 'f', 0);
		else btnText = currentZoomString;

		zoomInt->setText(btnText);
	});



	layoutConteneur_->addWidget(zoom);
	layoutConteneur_->addWidget(zoomInt);
	layoutConteneur_->addWidget(unZoom);

	QWidget* wis2 = new QWidget();
	QVBoxLayout *layout_ = new QVBoxLayout(wis2);
	layout_->setContentsMargins(0,0,0,0);
	//setContentsMargins(left, top, right, bottom)
	layout_->setSpacing(0);

	QScrollArea* scroll = new QScrollArea(wis2);
	scroll->setWidgetResizable(true);
	scroll->setFrameShape(QFrame::NoFrame);

	QWidget* contenaireExplorere = new QWidget(scroll);
	contenaireExplorere->setObjectName("contenaireExplorere");

	layoutConteneur = new QVBoxLayout(contenaireExplorere);
	layoutConteneur->setContentsMargins(4,4,4,0);
	layoutConteneur->setSpacing(2);

	layoutConteneur->addStretch();

	scroll->setWidget(contenaireExplorere);
	layout_->addWidget(scroll);

	layout->addWidget(wis1);
	layout->addWidget(wis2);
}