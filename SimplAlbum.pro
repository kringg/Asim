#-------------------------------------------------
#
# Project created by QtCreator 2018-06-03T22:04:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplAlbum
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MainContent.cpp \
    Qt/QFlowLayout.cpp \
    Qt/QThumbnail.cpp \
    Image.cpp \
    Config.cpp

HEADERS  += MainWindow.h \
    MainContent.h \
    Qt/QFlowLayout.h \
    Qt/QThumbnail.h \
    Image.h \
    Config.h

FORMS    += MainWindow.ui
