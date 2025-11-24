#include "appContentDreamMountain.h"

#include "windowDreamMountain.h"
#include "iconDreamMountain.h"

#include <QVBoxLayout>
#include <QSplitter>

#include <QWidget>

#include "system/fileEngine.h"

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
	test_->connect(test_, &Button::clicked, [this, test_, filePath, fileName](){
		FileEngine *newGetFile = new FileEngine(test_->attrPath.toStdString());
		char *text = newGetFile->read();
		EditFiles(text, newGetFile->mimeFromExtension(), filePath, fileName);
		free(text);
		delete newGetFile;
	});
	getStatutAppBarDreamMountain()->appendLeftButtonList(test_);
	getStatutAppBarDreamMountain()->UpdateButtonListLeft();
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

	fileExplorerAppDreamMountain = new FilesExplorerDreamMountain(windowParentApp, contentAppBarDreamMountain);
	codeEditorAppDreamMountain = new CodeEditorDreamMountain(contentAppBarDreamMountain);
	webViewAppDreamMountain = new WebViewDreamMountain(contentAppBarDreamMountain);

	webViewAppDreamMountain->setHtmlWeb("<h1>Hello World</h1>");
	//fileExplorerAppDreamMountain->updateListFilesPoject("/Users/julie/Documents/project-dev/");

	QObject::connect(codeEditorAppDreamMountain->getSystemEnfant(), &QPlainTextEdit::textChanged, [this]() {
		webViewAppDreamMountain->setHtmlWeb(codeEditorAppDreamMountain->getText());
	});

	statutAppBarDreamMountain = new StatutAppBarDreamMountain(windowParentApp);

	MainAppDreamMountain->addWidget(contentAppBarDreamMountain);
	MainAppDreamMountain->addWidget(statutAppBarDreamMountain);
}