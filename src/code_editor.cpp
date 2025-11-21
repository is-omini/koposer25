#include "code_editor.h"
#include "interface.h"

EditorCode::EditorCode(QPlainTextEdit* &codeEditorInput, QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(
        "background-color: rgba(31,31,31,1);"
        "color: white;"
    );

    QVBoxLayout *layout = new VerticalBoxLayout(this);
    codeEditorInput = new QPlainTextEdit();
    // Largeur d'une tabulation en pixels (par exemple 40 pixels)
    codeEditorInput->setTabStopDistance(32);
    layout->addWidget(codeEditorInput);
};