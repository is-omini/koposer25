#include "fileEngine.h"

FileEngine::FileEngine(std::string filePath) {
	currentFilePath = filePath;
}

char* FileEngine::read() {
	FILE *file = fopen(currentFilePath.c_str(), "r");
	if (!file) {
		printf("Impossible d'ouvrir le fichier : %s\n", currentFilePath.c_str());
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

std::string FileEngine::mimeFromExtension() {
	std::string filePath = currentFilePath.c_str();

	size_t pos = filePath.rfind('.');
	if(pos == std::string::npos) return "application/octet-stream";

	std::string ext = filePath.substr(pos);
	auto it = mimeMap.find(ext);
	if(it != mimeMap.end()) return it->second;
	return "application/octet-stream";
}