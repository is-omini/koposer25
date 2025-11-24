#ifndef FILEENGINESYSTEM_H
#define FILEENGINESYSTEM_H

#include <unordered_map>

#include <iostream>
#include <string>
using namespace std;


const std::unordered_map<std::string,std::string> mimeMap = {
	{".cpp", "text/plain"},
	{".h", "text/plain"},
	{".htacess", "text/plain"},
	{".gitignore", "text/plain"},
	{".gitattributes", "text/plain"},
	{".gitignore", "text/plain"},
	{".scss", "text/plain"},
	{".sass", "text/plain"},
	{".ts", "text/plain"},

	{".txt", "text/plain"},
	{".log", "text/plain"},
	{".ini", "text/plain"},
	{".bat", "text/plain"},
	{".sh", "text/plain"},
	{".tex", "text/plain"},
	{".csv", "text/csv"},
	{".htm", "text/html"},
	{".html", "text/html"},
	{".css", "text/css"},
	{".js", "text/javascript"},
	{".mjs", "text/javascript"},
	{".ts", "text/typescript"},
	{".md", "text/markdown"},
	{".yaml", "text/yaml"},
	{".yml", "text/yaml"},
	{".rtf", "text/rtf"},
	{".xml", "text/xml"},
	{".json", "application/json"},
	//{".json", "text/json"}
};

class FileEngine
{
public:
	FileEngine(std::string filePath);

	char* read();

	std::string mimeFromExtension();
private:
	std::string currentFilePath;
};
#endif