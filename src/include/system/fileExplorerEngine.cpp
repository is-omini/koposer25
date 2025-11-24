#include "fileExplorerEngine.h"
#include "fileEngine.h"
//CC julie
#include <QFileDialog>
#include <QFile>
#include <QString>

void saveFile(WindowDreamMountain* windowParentApp) {
	QString fichierPath = windowParentApp->getCurrentFilePath();
	if (fichierPath.isEmpty()) {
		fichierPath = QFileDialog::getSaveFileName(
			nullptr,
			"Enregistrer fichier", 
			"", 
			"Tous les fichiers (*)"
		);
	}
	qDebug() << fichierPath.isEmpty();
	if (fichierPath.isEmpty()) return;
	qDebug() << "SAVE" << fichierPath.isEmpty();

	QFile fichier(fichierPath);

	QString texte = windowParentApp->getAppContent()->getCodeEditorDreamMountain()->getText();
		
	if (fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&fichier);
		out << texte;
	}

	/*FileEngine *getFile = new FileEngine(fichierPath.toStdString());
	if (getFile->mimeFromExtension().find("text") == std::string::npos) return;
	char *text = getFile->read();
	windowParentApp->getAppContent()->EditFiles(
		text,
		getFile->mimeFromExtension(),
		fichierPath.toStdString(),
		fichierPath.toStdString(),
		1
	);
	free(text);*/
}

void openFolder(WindowDreamMountain* windowParentApp) {
	QString dossier = QFileDialog::getExistingDirectory(
		windowParentApp,
		"Choisir un dossier"
	);
	if (!dossier.isEmpty()) {
		windowParentApp->setCurrentProjectPath(dossier);
		//windowParentApp->oldProjectPath.clear();
		windowParentApp->filesExplorerHistory.clear();
		windowParentApp->filesExplorerHistory.push_back(dossier.toStdString());
		windowParentApp->getAppContent()->getFileExplorerAppDreamMountain()->updateListFilesPoject(
			windowParentApp->getCurrentProjectPath().toStdString() + "/"
		);
	}
}