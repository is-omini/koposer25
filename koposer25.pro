QT += core gui webenginewidgets svg

CONFIG += c++11

TARGET = DreamMoutain

# Dossier de build
DESTDIR = _build/bin          # le binaire final ira dans _build/bin
OBJECTS_DIR = _build/obj      # fichiers objets
MOC_DIR = _build/moc          # fichiers moc
UI_DIR = _build/ui            # fichiers ui compilés
RCC_DIR = _build/rcc          # fichiers rcc compilés

# Sources
SOURCES += src/mainDreamMountain.cpp \
    src/include/windowDreamMountain.cpp \
    src/include/appContentDreamMountain.cpp \
    src/include/codeEditorDreamMountain.cpp \
    src/include/filesExplorerDreamMountain.cpp \
    src/include/webViewDreamMountain.cpp \
    src/include/interfaceDreamMountain.cpp \
    src/include/system/textEditor.cpp \
    src/include/system/lineNumberArea.cpp \
    src/include/system/webEngine.cpp \
    src/include/system/fileSortingAlgorithm.cpp \
    src/include/system/fileEngine.cpp \
    src/include/system/fileExplorerEngine.cpp \
    src/include/customBarDreamMountain.cpp \
    src/include/statutAppBarDreamMountain.cpp

# Headers
HEADERS += src/mainDreamMountain.h \
    src/include/windowDreamMountain.h \
    src/include/customBarDreamMountain.h \
    src/include/statutAppBarDreamMountain.h \
    src/include/appContentDreamMountain.h \
    src/include/codeEditorDreamMountain.h \
    src/include/filesExplorerDreamMountain.h \
    src/include/webViewDreamMountain.h \
    src/include/interfaceDreamMountain.h \
    src/include/system/textEditor.h \
    src/include/system/lineNumberArea.h \
    src/include/system/webEngine.h \
    src/include/system/fileSortingAlgorithm.h \
    src/include/system/fileEngine.h \
    src/include/system/fileExplorerEngine.h \
    src/include/colorDreamMountain.h \
    src/include/iconDreamMountain.h

# Personnalisation macOS
mac {
    QMAKE_BUNDLE_NAME = DreamMoutain
    QMAKE_BUNDLE_IDENTIFIER = com.iamomini.creatdev.DreamMoutain
    ICON = MacOs/icon.icns
    QMAKE_INFO_PLIST = MacOs/Info.plist
}