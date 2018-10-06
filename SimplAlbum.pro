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
    ImageThumb.cpp \
    main.cpp\
    MainContent.cpp \
    MainWindow.cpp \
    Qt/QFlowLayout.cpp \

HEADERS += \
    Image.h \
    ImagePath.h \
    ImageThumb.h \
    MainContent.h \
    MainWindow.h \
    Qt/QFlowLayout.h \

FORMS += \
    MainWindow.ui

RESOURCES += \
    Resources/Resources.qrc

DISTFILES +=

RC_FILE += \
    Resources/Resources.rc
