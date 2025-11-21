#include <QFileDialog>	// Pour QFileDialog::getSaveFileName
#include <QFile>		  // Pour QFile
#include <QTextStream>	// Pour QTextStream
#include <QIODevice>	  // Pour QIODevice::WriteOnly | QIODevice::Text

#include "file.h"


#include <iostream>
#include <string>
using namespace std;

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

char* read(const char *path) {
	FILE *file = fopen(path, "r");
	if (!file) {
		printf("Impossible d'ouvrir le fichier : %s\n", path);
		return NULL;
	}

	// Aller à la fin pour connaître la taille
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allouer la mémoire pour le contenu
	char *buffer = (char *)malloc(size + 1);
	if (!buffer) {
		fclose(file);
		return NULL;
	}

	// Lire le fichier en une fois
	fread(buffer, 1, size, file);
	buffer[size] = '\0';  // Terminaison de chaîne

	fclose(file);

	return buffer;
}