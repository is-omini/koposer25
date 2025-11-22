#ifndef DREAMMOUNTAIN_H
#define DREAMMOUNTAIN_H

#include <QWidget>
#include "interface.h"

class DreamMountain {
public:
	QVector<Button*> tabDevAllButton; // Gere la tabulation en bas à droite
	QVector<Button*> explorerAllButton;

	QString currentPath;
	DreamMountain();

	void setCurrentPath(QString path);
private:
	QWidget window;
};
#endif