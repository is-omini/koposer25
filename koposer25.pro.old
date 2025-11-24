QT += core gui webenginewidgets svg

CONFIG += c++11

TARGET = DreamMoutain

# Dossier de build
DESTDIR = build/bin          # le binaire final ira dans build/bin
OBJECTS_DIR = build/obj      # fichiers objets
MOC_DIR = build/moc          # fichiers moc
UI_DIR = build/ui            # fichiers ui compilés
RCC_DIR = build/rcc          # fichiers rcc compilés

# Sources
SOURCES += src/DreamMountain.cpp \
    src/main.cpp \
    src/interface.cpp \
    src/explorer_files.cpp \
    src/file.cpp \
    src/html_color_syntax.cpp \
    src/code_editor.cpp \
    src/web_view.cpp \
    src/development_tab.cpp

# Headers
HEADERS += src/DreamMountain.h \
    src/ui_styles.h \
    src/interface.h \
    src/explorer_files.h \
    src/file.h \
    src/code_editor.h \
    src/web_view.h \
    src/development_tab.h \
    src/html_color_syntax.h

# Personnalisation macOS
mac {
    QMAKE_BUNDLE_NAME = DreamMoutain
    QMAKE_BUNDLE_IDENTIFIER = com.iamomini.creatdev.DreamMoutain
    ICON = MacOs/icon.icns
    QMAKE_INFO_PLIST = MacOs/Info.plist
}