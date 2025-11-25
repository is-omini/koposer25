#include "mainDreamMountain.h"

#include <QApplication>

//WindowDreamMountain *WindowDrMApp;
DreamMountain::DreamMountain(QWidget *parent) : QWidget(parent) {
	WindowDrMApp = new WindowDreamMountain();
}

// GETTER & SETTER
void DreamMountain::setCurrentPath(QString path) { currentPath = path; }
QString DreamMountain::getCurrentPath() { return currentPath; }


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	DreamMountain *dreamMountain = new DreamMountain();
	return app.exec();
}