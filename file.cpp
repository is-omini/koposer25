#include <QTextEdit>      // Pour QTextEdit
#include <QFileDialog>    // Pour QFileDialog::getSaveFileName
#include <QFile>          // Pour QFile
#include <QTextStream>    // Pour QTextStream
#include <QIODevice>      // Pour QIODevice::WriteOnly | QIODevice::Text

void saveFileTexte(QTextEdit *textEdit) {
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