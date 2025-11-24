#ifndef APPCONTENTBARDRMAPP_H
#define APPCONTENTBARDRMAPP_H

#include <QMainWindow>
#include <QWidget>

class WindowDreamMountain;

#include "codeEditorDreamMountain.h"
#include "filesExplorerDreamMountain.h"
#include "webViewDreamMountain.h"
#include "statutAppBarDreamMountain.h"

class AppContentDreamMountain: public QWidget {
public:
	explicit AppContentDreamMountain(WindowDreamMountain *app, QWidget *parent = nullptr);

	void EditFiles(
		std::string stringsForEdits,
		std::string fileMime,
		std::string filePath,
		std::string fileName,
		int addNewButton = 0
	);

	CodeEditorDreamMountain *getCodeEditorDreamMountain() { return codeEditorAppDreamMountain; }
	FilesExplorerDreamMountain *getFileExplorerAppDreamMountain() { return fileExplorerAppDreamMountain; }
	StatutAppBarDreamMountain *getStatutAppBarDreamMountain() { return statutAppBarDreamMountain; }
private:
	WebViewDreamMountain *webViewAppDreamMountain;
	CodeEditorDreamMountain *codeEditorAppDreamMountain;
	FilesExplorerDreamMountain *fileExplorerAppDreamMountain;
	StatutAppBarDreamMountain* statutAppBarDreamMountain;

	WindowDreamMountain *windowParentApp;
};

#endif