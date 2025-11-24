#ifndef UI_STYLE_H
#define UI_STYLE_H
const QString scrollBarInput = R"(
    QPlainTextEdit { line-height: 1.7; }

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
#endif