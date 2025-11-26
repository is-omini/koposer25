#include "fileExplorerEngine.h"
//CC julie

#include <unordered_map>


#include <QFileDialog>
#include <QFile>
#include <QString>

#include <iostream>
#include <string>
using namespace std;

const std::unordered_map<std::string,std::string> mimeMap = {
	{".cpp", "text/plain"},
	{".h", "text/plain"},
	{".htacess", "text/plain"},
	{".gitignore", "text/plain"},
	{".gitattributes", "text/plain"},
	{".gitignore", "text/plain"},
	{".scss", "text/plain"},
	{".sass", "text/plain"},
	{".ts", "text/plain"},

	{".txt", "text/plain"},
	{".log", "text/plain"},
	{".ini", "text/plain"},
	{".bat", "text/plain"},
	{".sh", "text/plain"},
	{".tex", "text/plain"},
	{".csv", "text/csv"},
	{".htm", "text/html"},
	{".html", "text/html"},
	{".css", "text/css"},
	{".js", "text/javascript"},
	{".mjs", "text/javascript"},
	{".ts", "text/typescript"},
	{".md", "text/markdown"},
	{".yaml", "text/yaml"},
	{".yml", "text/yaml"},
	{".rtf", "text/rtf"},
	{".xml", "text/xml"},
	{".json", "application/json"},
	//{".json", "text/json"}
};

std::string getFileMime(std::string filePath) {
	size_t pos = filePath.rfind('.');
	if(pos == std::string::npos) return "application/octet-stream";

	std::string ext = filePath.substr(pos);
	auto it = mimeMap.find(ext);
	if(it != mimeMap.end()) return it->second;
	return "application/octet-stream";
}

std::string getFileName(std::string path) {
	size_t pos = path.find_last_of("/\\");
	std::string filename = path;
	if (pos != std::string::npos) {
		filename = path.substr(pos + 1);
	}

	return filename;
}

char* readFile(std::string fichierPath) {
	FILE *file = fopen(fichierPath.c_str(), "r");
	if (!file) {
		printf("Impossible d'ouvrir le fichier : %s\n", fichierPath.c_str());
		return NULL;
	}

	// Aller à la fin pour connaître la taille
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allouer la mémoire pour le contenu
	char *buffer = (char *)malloc(size + 1);
	if (!buffer) {
		fclose(file);
		return NULL;
	}

	// Lire le fichier en une fois
	fread(buffer, 1, size, file);
	buffer[size] = '\0';  // Terminaison de chaîne

	fclose(file);

	return buffer;
}

int openFile(WindowDreamMountain* windowParentApp, std::string fichierPath) {
	FILE *file = fopen(fichierPath.c_str(), "r");
	if (!file) {
		qDebug() << "Impossible d'ouvrir le fichier : " << fichierPath;
		return 0;
	}

	// Aller à la fin pour connaître la taille
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allouer la mémoire pour le contenu
	char *buffer = (char *)malloc(size + 1);
	if (!buffer) {
		fclose(file);
		qDebug() << "Erreur d'allocation : " << fichierPath;
		return 0;
	}
	// Lire le fichier en une fois
	fread(buffer, 1, size, file);
	buffer[size] = '\0';  // Terminaison de chaîne
	windowParentApp->getAppContent()->EditFiles(
		buffer,
		getFileMime(fichierPath), //"text/plain", //getFile->mimeFromExtension(),
		fichierPath,
		getFileName(fichierPath),
		1
	);
	fclose(file);

	return 1;
}

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

	if (fichierPath.isEmpty()) return;
	QFile fichier(fichierPath);
	QString texte = windowParentApp->getAppContent()->getCodeEditorDreamMountain()->getText();
	if (fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&fichier);
		out << texte;
	}
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
		windowParentApp->updateListFilesExplorerDreamMountain(
			windowParentApp->getCurrentProjectPath().toStdString() + "/"
		);
	}
}

void backFolderToExplorer(WindowDreamMountain* windowParentApp) {
	if (windowParentApp->filesExplorerHistory.size() < 1) return;
	if (windowParentApp->filesExplorerHistory.size() > 1) windowParentApp->filesExplorerHistoryPop();

	std::string previous = windowParentApp->filesExplorerHistoryGetLast();
	windowParentApp->currentPath = QString::fromStdString(previous);

	windowParentApp->updateListFilesExplorerDreamMountain(
		previous + "/", windowParentApp->porjectName
	);
}


void openExplorerFile(WindowDreamMountain* windowParentApp, std::string StdFilePath, QString QStrFileName) {
	openFile(windowParentApp, StdFilePath);
	windowParentApp->setCurrentFilePath(QStrFileName);
}

void openExplorerFolder(
	WindowDreamMountain* windowParentApp,
	std::string currentFolderPath,
	std::string StdFilePath,
	QString QStrFileName,
	QString titleProject
) {
	windowParentApp->filesExplorerHistoryPush(currentFolderPath);

	QDir dir(QStrFileName);
	if(dir.exists()) windowParentApp->updateListFilesExplorerDreamMountain(StdFilePath, titleProject);
}