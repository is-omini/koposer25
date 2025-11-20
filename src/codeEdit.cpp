#include <QWidget>		 // Pour QWidget
#include <QLabel>		// Pour qMax
#include <QVBoxLayout>
#include "codeEdit.h"

QWidget* CodeEdit(QPlainTextEdit* &editeur, QLabel* &numLinesLabel) {
	QWidget *container = new QWidget();
	QHBoxLayout *layout = new QHBoxLayout(container);
	layout->setContentsMargins(0, 0, 0, 0);

	numLinesLabel = new QLabel();
	numLinesLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
	numLinesLabel->setFixedWidth(32);
	numLinesLabel->setStyleSheet("background-color: rgba(31,31,31,1); color: white;");

	editeur = new QPlainTextEdit();

	numLinesLabel->setFont(editeur->font());

	layout->addWidget(numLinesLabel);
	layout->addWidget(editeur);

	return container;  // ✔ on retourne le widget complet
}
