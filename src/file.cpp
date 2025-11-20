#include <QPlainTextEdit>      // Pour QTextEdit
#include <QFileDialog>    // Pour QFileDialog::getSaveFileName
#include <QFile>          // Pour QFile
#include <QTextStream>    // Pour QTextStream
#include <QIODevice>      // Pour QIODevice::WriteOnly | QIODevice::Text

void save(QPlainTextEdit *textEdit) {
	QString texte = textEdit->toPlainText();

	QString nomFichier = QFileDialog::getSaveFileName(
		nullptr, 
		"Enregistrer fichier", 
		"", 
		"Tous les fichiers (*)"
	);
	if (!nomFichier.isEmpty()) {
		QFile fichier(nomFichier);
		if (fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream out(&fichier);
			out << texte;
		}
	}
}

void open(QPlainTextEdit *textEdit) {
	QString nomFichier = QFileDialog::getOpenFileName(
		nullptr,
		"Ouvrir fichier",
		"",
		"Tous les fichiers (*)"
	);
	if (!nomFichier.isEmpty()) {
		QFile fichier(nomFichier);
		if (fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&fichier);
			QString contenu = in.readAll();
			textEdit->setPlainText(contenu);
		}
	}
}