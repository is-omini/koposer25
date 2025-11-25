#ifndef COLORDRMAPP_H
#define COLORDRMAPP_H

const QString scrollBarInput = R"(
    QPlainTextEdit { line-height: 1.7; }
    QScrollArea {
        background: transparent;
        border: none;
    }

    QScrollBar:vertical {
        background: #1e1f22;
        width: 8px;
        margin: 0px;
    }

    QScrollBar::handle:vertical {
        background: #414245;
        min-height: 30px;
    }

    QScrollBar::handle:vertical:hover {
        background: #5c5d63;
    }

    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
        height: 0px;
    }

    QScrollBar::add-page:vertical,
    QScrollBar::sub-page:vertical {
        background: none;
    }

    /* Scrollbar horizontale */
    QScrollBar:horizontal {
        background: #1e1f22;
        height: 10px;
        margin: 0px;
    }

    QScrollBar::handle:horizontal {
        background: #414245;
        min-width: 30px;
    }

    QScrollBar::handle:horizontal:hover {
        background: #81A1C1;
    }

    QScrollBar::add-line:horizontal,
    QScrollBar::sub-line:horizontal {
        width: 0px;
    }

    QScrollBar::add-page:horizontal,
    QScrollBar::sub-page:horizontal {
        background: none;
    }
)";

const QString scrollBarWindow = R"(
    QPlainTextEdit { line-height: 1.7; }
    QScrollArea {
        background: transparent;
        border: none;
    }

    QScrollBar:vertical {
        background: #2c2d30;
        width: 8px;
        margin: 0px;
    }

    QScrollBar::handle:vertical {
        background: #414245;
        min-height: 30px;
    }

    QScrollBar::handle:vertical:hover {
        background: #5c5d63;
    }

    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
        height: 0px;
    }

    QScrollBar::add-page:vertical,
    QScrollBar::sub-page:vertical {
        background: none;
    }

    /* Scrollbar horizontale */
    QScrollBar:horizontal {
        background: #2c2d30;
        height: 10px;
        margin: 0px;
    }

    QScrollBar::handle:horizontal {
        background: #414245;
        min-width: 30px;
    }

    QScrollBar::handle:horizontal:hover {
        background: #81A1C1;
    }

    QScrollBar::add-line:horizontal,
    QScrollBar::sub-line:horizontal {
        width: 0px;
    }

    QScrollBar::add-page:horizontal,
    QScrollBar::sub-page:horizontal {
        background: none;
    }
)";


const QString styleButonExplorerFileNormal = R"(
    QPushButton {
        background-color: #2c2d30;
        border: 1px solid #2c2d30;
        color: white;
        padding: 8px 10px 8px 10px;
        margin: 0;
        text-align: left;
    }
    QPushButton:hover {
        background-color: rgba(31,31,31,1);
    }
)";

const QString styleButonExplorerFileSelected = R"(
    QPushButton {
        background-color: #44454a;
        border: 1px solid #44454a;
        color: white;
        padding: 8px 10px 8px 10px;
        margin: 0;
        text-align: left;
    }
    QPushButton:hover {
        background-color: #2c2d30);
    }
)";


const QString windowBackgoundColor = "#2c2d30";

const QString colorHighlight = "#5c5d63";
const QString colorBackgroundInput = "#1e1f22";

const QString colorWhite = "#ffffff";

#endif