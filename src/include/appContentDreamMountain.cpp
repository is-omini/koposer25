#include "appContentDreamMountain.h"

#include "windowDreamMountain.h"
#include "iconDreamMountain.h"

#include "contextMenuDreamMountain.h"

#include <QVBoxLayout>
#include <QSplitter>

#include <QWidget>
#include <QApplication>

#include "system/fileExplorerEngine.h"

void AppContentDreamMountain::mousePressEvent(QMouseEvent *event) {
	contextMenuDreamMountain->hide();
    if (event->button() != Qt::RightButton) return;

    QWidget* clickedWidget = QApplication::widgetAt(QCursor::pos());
    if(clickedWidget) {
        contextMenuDreamMountain->getContextMenu(clickedWidget, clickedWidget->mapFromGlobal(QCursor::pos()));
    }
}

void AppContentDreamMountain::EditFiles(
	std::string stringsForEdits,
	std::string fileMime,
	std::string filePath,
	std::string fileName,
	int addNewButton
) {
	qDebug() << fileName;
	if(windowParentApp->getCurrentFilePath() == QString::fromStdString(filePath)) return;

 	if ((fileMime.find("text") == std::string::npos) && (fileMime.find("json") == std::string::npos)) return;

	webViewAppDreamMountain->setHtmlWeb(QString::fromUtf8(stringsForEdits.c_str()));
	codeEditorAppDreamMountain->setText(QString::fromUtf8(stringsForEdits.c_str()));

	windowParentApp->setCurrentFilePath(QString::fromStdString(filePath));

	Button* test_ = getStatutAppBarDreamMountain()->AppendButtonList(
		QString::fromStdString(fileName),
		iconFile,
		16,
		R"(
		#newButton {
			background-color: #25282d;
			color: #fff;
			padding: 8px;
			border-radius: 5px;
			margin: 0;
			text-align: center;
		}
		#newButton:hover {
			background-color: #4a4b4e;
		})"
	);
	if(addNewButton == 0) return;
	if(getStatutAppBarDreamMountain()->isFileStatusBar(filePath)) return;

	test_->attrPath = QString::fromStdString(filePath);
	test_->connect(test_, &Button::clicked, [this, test_, filePath, fileName, fileMime](){
		char *text = readFile(filePath);
		EditFiles(
			text,
			getFileMime(filePath),
			filePath,
			getFileName(filePath)
		);
		free(text);
		windowParentApp->setCurrentFilePath(test_->attrPath);
	});
	getStatutAppBarDreamMountain()->appendLeftButtonList(test_);
	getStatutAppBarDreamMountain()->UpdateButtonListLeft();
}

void AppContentDreamMountain::updatePosition(QPoint localPos) {
	contextMenuDreamMountain->move(mapToGlobal(localPos));
	contextMenuDreamMountain->adjustSize();

	contextMenuDreamMountain->raise();
	contextMenuDreamMountain->show();
}


AppContentDreamMountain::AppContentDreamMountain(WindowDreamMountain *app, QWidget *parent) : QWidget(parent) {
	windowParentApp = app;

	QVBoxLayout *MainAppDreamMountain = new QVBoxLayout(this);
	MainAppDreamMountain->setContentsMargins(0,0,0,0);
	MainAppDreamMountain->setSpacing(0);
	QSplitter *contentAppBarDreamMountain = new QSplitter(Qt::Horizontal);
	contentAppBarDreamMountain->setStyleSheet("QSplitter::handle { background: transparent; }");
	contentAppBarDreamMountain->setContentsMargins(0,0,0,0);
	contentAppBarDreamMountain->setHandleWidth(0);
	contentAppBarDreamMountain->setMinimumWidth(0);


	fileExplorerAppDreamMountain = new FilesExplorerDreamMountain(windowParentApp, contentAppBarDreamMountain);
	codeEditorAppDreamMountain = new CodeEditorDreamMountain(windowParentApp, contentAppBarDreamMountain);
	webViewAppDreamMountain = new WebViewDreamMountain(contentAppBarDreamMountain);

	webViewAppDreamMountain->setHtmlWeb("<h1>Hello World</h1>");
	//fileExplorerAppDreamMountain->updateListFilesPoject("/Users/julie/Documents/project-dev/");

	QObject::connect(codeEditorAppDreamMountain->getSystemEnfant(), &QPlainTextEdit::textChanged, [this]() {
		webViewAppDreamMountain->setHtmlWeb(codeEditorAppDreamMountain->getText());
	});

	statutAppBarDreamMountain = new StatutAppBarDreamMountain(windowParentApp);

	MainAppDreamMountain->addWidget(contentAppBarDreamMountain);
	MainAppDreamMountain->addWidget(statutAppBarDreamMountain);


	// Widget superposé
	contextMenuDreamMountain = new ContextMenuDreamMountain(windowParentApp, this);
	/*contextMenuDreamMountain = new QWidget(this);
	contextMenuDreamMountain->setObjectName("contextMenu");
	contextMenuDreamMountain->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	contextMenuDreamMountain->setStyleSheet(R"(
		#contextMenu {
			background-color: red;
		}

		#contextMenu QPushButton {
			
			border: 1px solid #2c2d30;
			color: white;
			padding: 5px 5px 5px 5px;
			margin: 0;
			text-align: left;
		}
		#contextMenu QPushButton:hover {
			background-color: rgba(31,31,31,0.3);
		}
	)"); //background-color: #2c2d30;

	contextMenuDreamMountainList = new QVBoxLayout(contextMenuDreamMountain);
	contextMenuDreamMountainList->setContentsMargins(0,0,0,0);
	contextMenuDreamMountainList->setSpacing(10);
	contextMenuDreamMountain->setMinimumWidth(200);
	contextMenuDreamMountain->setMinimumHeight(200);

	//contextMenuDreamMountain->adjustSize();*/
}