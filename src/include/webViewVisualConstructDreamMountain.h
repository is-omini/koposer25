#ifndef WEBVIEWVISUALCONSTRUCTDRMAPP_H
#define WEBVIEWVISUALCONSTRUCTDRMAPP_H


#include "interfaceDreamMountain.h"
#include "system/terminal.h"

class WindowDreamMountain;

#include <QWidget>
#include <QString>
#include <QVBoxLayout>

#include <iostream>
#include <string>
#include <regex>
#include <vector>

class WVVisualConstructDrM : public QWidget {
public:
	explicit WVVisualConstructDrM(WindowDreamMountain *main,QWidget* parent = nullptr);

	void addLine(QString string) {
		//qDebug() << string;
		Button *btn = new Button(string, nullptr, 0);
		QString colorText = "#ffffff"; // ou toute autre couleur
		if(string.contains("ERROR")) colorText = "#FF5F57";
		if(string.contains("WARNING")) colorText = "#FEBC2E";

		QString colorHover = "#1e1f22"; // ou toute autre couleur
		if(string.contains("ERROR")) colorHover = "#521D1A";
		if(string.contains("WARNING")) colorHover = "#52411A";

		btn->setStyleSheet(QString(R"(
			QPushButton {
				background-color: transparent;
				color: %1;
				border: none;
				text-align: left;
				border-radius: 4px;
				padding: 8px 14px;
			}
			QPushButton:hover {
				background-color: %2;
			}
		)").arg(colorText, colorHover));
		layoutConteneur->addWidget(btn);
	}

	void getHtmlElement(std::string html) {
		qDebug() << html;
		auto tags = listHtmlTags(html);

		for (const auto& t : tags) {
			Debug() << t;
		}
	}

	std::vector<std::string> listHtmlTags(const std::string& html) {
	    std::regex tagRegex("<\\/?([a-zA-Z0-9-]+)[^>]*>");
	    std::smatch match;
	    std::string text = html;
	    std::vector<std::string> result;

	    while (std::regex_search(text, match, tagRegex)) {
	        std::string fullTag = match[0];
	        std::string tagName = match[1];

	        if(tagName != "script") {

	        if (fullTag[1] == '/') {
	            // Balise fermante
	            result.push_back("-" + tagName);
	        } else {
	            // Balise ouvrante
	            result.push_back(tagName);
	        }
	        	
	        }

	        text = match.suffix().str();
	    }

	    return result;
	}

	void clearLine() {
		//qDebug() << "CLEAR";

		if (layoutConteneur) {
			QLayoutItem *child;
			while ((child = layoutConteneur->takeAt(0)) != nullptr) {
				if (child->widget()) {
					delete child->widget();
				}
				delete child;
			}
		}

		layoutConteneur->addStretch();
	}
private:
	QVBoxLayout* layoutConteneur;

	WindowDreamMountain* windowParentApp;
};

#endif