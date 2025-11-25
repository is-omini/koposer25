#ifndef FILESEXPLORERBARDRMAPP_H
#define FILESEXPLORERBARDRMAPP_H

class WindowDreamMountain;

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSplitter>

class FilesExplorerDreamMountain : public QWidget {
public:
	explicit FilesExplorerDreamMountain(WindowDreamMountain *app, QWidget *parent = nullptr);

	void updateListFilesPoject(std::string path, QString titleProject = nullptr);

	void clearLayoutExplorerListItems();
private:
	QScrollArea *scroll;
	QVBoxLayout *verticalBox = nullptr;
	QWidget *contenaireExplorere = nullptr;

	QVBoxLayout *layoutExplorerListItems = nullptr;


	WindowDreamMountain *windowParentApp;

	QString currentPath;
};

#endif