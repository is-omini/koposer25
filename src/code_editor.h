#include <QWidget>
#include <QPlainTextEdit>

class EditorCode : public QWidget {
    Q_OBJECT
public:
    explicit EditorCode(QPlainTextEdit* &codeEditorInput, QWidget *parent = nullptr);
};