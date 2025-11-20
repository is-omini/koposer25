#include <QWidget>         // Pour QWidget
#include <QLabel>        // Pour qMax
#include <QVBoxLayout>
#include "codeEdit.h"

QPlainTextEdit* CodeEdit(QPlainTextEdit* &editeur, QLabel* &numLinesLabel) {
	QWidget *container = new QWidget();
	QHBoxLayout *layout = new QHBoxLayout(container);
	layout->setContentsMargins(0, 0, 0, 0);

	numLinesLabel = new QLabel();
	numLinesLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);

	editeur = new QPlainTextEdit();

	numLinesLabel->setFont(editeur->font());
	layout->addWidget(numLinesLabel);
	layout->addWidget(editeur);

	return editeur;
}