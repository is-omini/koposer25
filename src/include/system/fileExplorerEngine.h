#ifndef FILEXPLORERENGINESYSTSEM_H
#define FILEXPLORERENGINESYSTSEM_H


#include "../windowDreamMountain.h"

void saveFile(WindowDreamMountain* windowParentApp);
void openFolder(WindowDreamMountain* windowParentApp);
void backFolderToExplorer(WindowDreamMountain* windowParentApp);
int openFile(WindowDreamMountain* windowParentApp, std::string fichierPath);

#endif