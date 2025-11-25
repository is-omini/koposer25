#ifndef APPCONTENTBARDRMAPP_H
#define APPCONTENTBARDRMAPP_H

#include <QMainWindow>
#include <QWidget>

class WindowDreamMountain;
class ContextMenuDreamMountain;

#include "codeEditorDreamMountain.h"
#include "filesExplorerDreamMountain.h"
#include "webViewDreamMountain.h"
#include "statutAppBarDreamMountain.h"
#include "interfaceDreamMountain.h"
#include "colorDreamMountain.h"
#include "iconDreamMountain.h"

#include "system/textEditor.h"

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

	void updatePosition(QPoint localPos);

	CodeEditorDreamMountain *getCodeEditorDreamMountain() { return codeEditorAppDreamMountain; }
	FilesExplorerDreamMountain *getFileExplorerAppDreamMountain() { return fileExplorerAppDreamMountain; }
	StatutAppBarDreamMountain *getStatutAppBarDreamMountain() { return statutAppBarDreamMountain; }
private:
	WebViewDreamMountain *webViewAppDreamMountain;
	CodeEditorDreamMountain *codeEditorAppDreamMountain;
	FilesExplorerDreamMountain *fileExplorerAppDreamMountain;
	StatutAppBarDreamMountain* statutAppBarDreamMountain;

	WindowDreamMountain *windowParentApp;

	//QWidget* contextMenuDreamMountain;
	ContextMenuDreamMountain* contextMenuDreamMountain;
	//QVBoxLayout* contextMenuDreamMountainList;

protected:
	void mousePressEvent(QMouseEvent *event) override;
	/*
		if (event->button() != Qt::RightButton) {
			QWidget::mousePressEvent(event);
			return;
		}

		QPoint localPos = mapFromGlobal(QCursor::pos());
		QWidget* child = childAt(localPos);
		qDebug() << "hello";

		if(!child) {
			qDebug() << child;
			return;
		}

		int hSize = 0;
		QLayoutItem *item;
		while ((item = contextMenuDreamMountainList->takeAt(0)) != nullptr) {
			if (item->widget()) {
				item->widget()->deleteLater();
			}
			delete item;
		}
		
		Button* btn = qobject_cast<Button*>(child);
		TextEditor* text_editor = qobject_cast<TextEditor*>(child);
		//QVector<Button*> contextMenu;
		if(btn) {
			qDebug() << "hello YES";
			QVector<Button*> contextMenu = btn->getContextMenu();

		for (Button* b : contextMenu) {
			Button* newBtn = new Button(b->text(), b->getSvg(), b->iconSize().width(), contextMenuDreamMountain);
			newBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			contextMenuDreamMountainList->addWidget(newBtn);
			hSize += newBtn->height();
		}
		}
		if(text_editor) {
			qDebug() << "hello YES";
			QVector<Button*> contextMenu = text_editor->getContextMenu();

		for (Button* b : contextMenu) {
			Button* newBtn = new Button(b->text(), b->getSvg(), b->iconSize().width(), contextMenuDreamMountain);
			newBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			contextMenuDreamMountainList->addWidget(newBtn);
			hSize += newBtn->height();
		}
		}

		int x = localPos.x();
		int y = localPos.y();

		if(hSize < 10) hSize = 100;

		contextMenuDreamMountain->move(x, y);
		contextMenuDreamMountain->setFixedHeight(hSize);
		contextMenuDreamMountain->show();
		contextMenuDreamMountain->adjustSize();
		contextMenuDreamMountain->update();   // force un repaint
		contextMenuDreamMountain->repaint(); 
	} */
};

#endif