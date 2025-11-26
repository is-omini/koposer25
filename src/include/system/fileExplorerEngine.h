#ifndef FILEXPLORERENGINESYSTSEM_H
#define FILEXPLORERENGINESYSTSEM_H


#include "../windowDreamMountain.h"

char* readFile(std::string fichierPath);

void saveFile(WindowDreamMountain* windowParentApp);
void openFolder(WindowDreamMountain* windowParentApp);
void backFolderToExplorer(WindowDreamMountain* windowParentApp);

int openFile(WindowDreamMountain* windowParentApp, std::string fichierPath);

std::string getFileMime(std::string filePath);
std::string getFileName(std::string path);

void openExplorerFile(WindowDreamMountain* windowParentApp, std::string StdFilePath, QString QStrFileName);
void openExplorerFolder(
	WindowDreamMountain* windowParentApp,
	std::string currentFolderPath,
	std::string StdFilePath,
	QString QStrFileName,
	QString titleProject
);

#endif