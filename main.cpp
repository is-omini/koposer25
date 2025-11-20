#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QSplitter>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <Qt>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWebEngineView>

#define windowWidth 1080
#define windowHeight 720


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

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	QMainWindow window;
	window.setWindowTitle("Éditeur de texte simple");

	QSplitter *splitter = new QSplitter(Qt::Horizontal);

	//QTextEdit *bloc1 = new QTextEdit();
	QTextEdit *editorTxt = new QTextEdit();

	// ICI Affiche le code html

	QWebEngineView *bloc3 = new QWebEngineView();
	bloc3->setHtml("<html><body><h1>Hello HTML moderne!</h1></body></html>");


	/* AJoute un bouton & detecte le click (Connect) */
	QPushButton *saveButton = new QPushButton("Sauvegarder");
	QObject::connect(saveButton, &QPushButton::clicked, [editorTxt]() {
		saveFileTexte(editorTxt);
	});
	
	splitter->addWidget(saveButton);
	splitter->addWidget(editorTxt);
	splitter->addWidget(bloc3);

	window.setCentralWidget(splitter);

	window.resize(windowWidth, windowHeight);
	window.show();

	return app.exec();
}