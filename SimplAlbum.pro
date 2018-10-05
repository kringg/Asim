#-------------------------------------------------
#
# Project created by QtCreator 2018-06-03T22:04:27
#
#-------------------------------------------------

QT += core gui widgets

TARGET = SimplAlbum
TEMPLATE = app

SOURCES += \
    Image.cpp \
    ImagePath.cpp \
    main.cpp\
    MainContent.cpp \
    MainWindow.cpp \
    Qt/QFlowLayout.cpp \
    Qt/QThumbnail.cpp \

HEADERS += \
    Image.h \
    ImagePath.h \
    MainContent.h \
    MainWindow.h \
    Qt/QFlowLayout.h \
    Qt/QThumbnail.h \

FORMS += \
    MainWindow.ui

RESOURCES += \
    Resources/Resources.qrc

DISTFILES +=

RC_FILE += \
    Resources/Resources.rc
