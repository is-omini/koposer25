#ifndef CUSTOMBARDRMAPP_H
#define CUSTOMBARDRMAPP_H

class WindowDreamMountain;

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>

class CustomBarDreamMountain : public QWidget {
public:
	QPushButton* sourceBnC;

	explicit CustomBarDreamMountain(WindowDreamMountain *main, QWidget *parent = nullptr);

	void hideCustumeBar();
	void showCustumeBar();

	void UpdateButtonListRight();
	void UpdateButtonListCenter();
	void UpdateButtonListLeft();
	QPushButton* AppendButtonList(
		QString string = nullptr,
		QString Svg = nullptr,
		int svgSize = 12,
		QString css = nullptr
	);

	void appendLeftButtonList(QPushButton* btn) {
		leftButtonList.append(btn);
	};

	void AppendButtonListRight(QString string = nullptr, QString Svg = nullptr, int svgSize = 12, QString css = nullptr);
	void AppendButtonListLeft(QString string = nullptr, QString Svg = nullptr, int svgSize = 12, QString css = nullptr);
private:
	bool windowMove;
	QPoint windowMovePosition;

	QHBoxLayout *layoutCustomeBarButton;
	QWidget *widgetCustomeBarButton;

	QHBoxLayout *layoutCustomeBarButtonWindow;
	QWidget *widgetCustomeBarButtonWindow;

	QHBoxLayout *layoutRightButtonList;
	QWidget *widgetRightButtonList;

	QHBoxLayout *layoutLeftButtonList;
	QWidget *widgetLeftButtonList;

	QHBoxLayout *layoutCenterButtonList;
	QWidget *widgetCenterButtonList;

	WindowDreamMountain *windowParentApp;

	QList<QPushButton*> rightButtonList;
	QList<QPushButton*> centerButtonList;
	QList<QPushButton*> leftButtonList;
protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
};
#endif