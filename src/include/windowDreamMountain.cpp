#include "windowDreamMountain.h"
#include "colorDreamMountain.h"
#include "customBarDreamMountain.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QEvent>

WindowDreamMountain::WindowDreamMountain(QWidget *parent) : QMainWindow(parent) {
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	resize(1280, 800);

	centralBackgroundWindow = new QWidget(this);
	centralBackgroundWindow->setObjectName("centralBackgroundWindow");
	centralBackgroundWindow->setStyleSheet("#centralBackgroundWindow { background: "+windowBackgoundColor+"; border-radius: 10px; }");
	setCentralWidget(centralBackgroundWindow);

	QVBoxLayout *MainWindowDreamMountain = new QVBoxLayout(centralBackgroundWindow);
	MainWindowDreamMountain->setContentsMargins(0,0,0,0);
	MainWindowDreamMountain->setSpacing(0);

	CustomWindowBarDreamMountain = new CustomBarDreamMountain(this);
	MainWindowDreamMountain->addWidget(CustomWindowBarDreamMountain);

	appContentDreamMountain = new AppContentDreamMountain(this);
	MainWindowDreamMountain->addWidget(appContentDreamMountain, 1);

	show();
}

void WindowDreamMountain::hideCustomWindowBar() {
	CustomWindowBarDreamMountain->hide();
}

void WindowDreamMountain::hideRedoundWindowBorder() {
	centralBackgroundWindow->setStyleSheet("#centralBackgroundWindow { background: "+windowBackgoundColor+"; border-radius: 0px; }");
}

void WindowDreamMountain::showRedoundWindowBorder() {
	centralBackgroundWindow->setStyleSheet("#centralBackgroundWindow { background: "+windowBackgoundColor+"; border-radius: 10px; }");
}

void WindowDreamMountain::changeEvent(QEvent *event) {
	if (event->type() == QEvent::WindowStateChange) {
		bool isFull = windowState() & Qt::WindowFullScreen;

		if (CustomWindowBarDreamMountain) {
			if(isFull) CustomWindowBarDreamMountain->hideCustumeBar();
			else CustomWindowBarDreamMountain->showCustumeBar();
		}
	}
	QMainWindow::changeEvent(event);
}