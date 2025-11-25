#ifndef CONTEXTMENUDRMAPP_H
#define CONTEXTMENUDRMAPP_H

class WindowDreamMountain;

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>

#include "interfaceDreamMountain.h"
#include "colorDreamMountain.h"
#include "iconDreamMountain.h"

class ContextMenuDreamMountain : public QWidget {
public:
	explicit ContextMenuDreamMountain(WindowDreamMountain *main, QWidget *parent = nullptr);

	void clearOverlay();
	bool getContextMenu(QWidget* widget, QPoint localPos);
	
private:
	void updateListOverlay(QVector<Button*> contextMenu);

	QVBoxLayout* contextMenuDreamMountainList;
	int hSize = 0;
};

#endif