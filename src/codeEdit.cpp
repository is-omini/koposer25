class CodeEdit : public QPlainTextEdit {
	Q_OBJECT
public:
	CodeEdit(QWidget *parent = nullptr) : QPlainTextEdit(parent), zoneNumeros(new ZoneNumerosLigne(this)) {
		
	}
};