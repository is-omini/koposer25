#ifndef CODE_EDITOR_H
#define CODE_EDITOR_H

#include <QWidget>
#include <QPlainTextEdit>

class EditorCode : public QWidget {
    Q_OBJECT
public:
    explicit EditorCode(QPlainTextEdit* &codeEditorInput, QWidget *parent = nullptr);
};
#endif