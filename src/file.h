#ifndef FILE_H
#define FILE_H

#include <QPlainTextEdit> 

void save(QPlainTextEdit *textEdit, const QString &path = QString());
void open(QPlainTextEdit *textEdit);
char* read(const char *path);
#endif