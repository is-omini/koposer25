#include "windowDreamMountain.h"
#include "colorDreamMountain.h"
#include "customBarDreamMountain.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QEvent>

#include <QSettings>

#include <QCloseEvent>

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

		if (CustomWindowBarDreamMountain ) {
			if(isFull) CustomWindowBarDreamMountain->hideCustumeBar();
			else CustomWindowBarDreamMountain->showCustumeBar();
		}
	}
	QMainWindow::changeEvent(event);
}

void WindowDreamMountain::closeEvent(QCloseEvent *event) {
    saveWindowGeometry();
    QMainWindow::closeEvent(event);
}

WindowDreamMountain::~WindowDreamMountain() {
    saveWindowGeometry();
}

void WindowDreamMountain::saveWindowGeometry() {
    QSettings settings("VotreEntreprise", "DreamMountain");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("position", pos());
    settings.setValue("size", size());
    settings.setValue("size", size());

	settings.setValue("filesExplorer/currentPath", currentProjectPath);

	qDebug() << currentProjectPath;
}

void WindowDreamMountain::loadWindowGeometry() {
    QSettings settings("VotreEntreprise", "DreamMountain");
    setCurrentProjectPath(settings.value("filesExplorer/currentPath").toString());
    currentProjectPath = settings.value("filesExplorer/currentPath").toString();
    std::string stdCurrentPath = currentProjectPath.toStdString();

    if(stdCurrentPath.empty()) stdCurrentPath = "/Users/julie/Documents/project-dev/";
    appContentDreamMountain->getFileExplorerAppDreamMountain()->updateListFilesPoject(stdCurrentPath);
    
    if (settings.contains("geometry")) {
        restoreGeometry(settings.value("geometry").toByteArray());
        restoreState(settings.value("windowState").toByteArray());
        if (settings.value("isMaximized", false).toBool()) {
            showMaximized();
        }
    } else {
        // Valeurs par défaut si première ouverture
        resize(1280, 800);
        // Centrer la fenêtre
        QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }
}







WindowDreamMountain::WindowDreamMountain(QWidget *parent) : QMainWindow(parent) {
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

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
	MainWindowDreamMountain->addWidget(appContentDreamMountain);

	loadWindowGeometry();
	show();
}