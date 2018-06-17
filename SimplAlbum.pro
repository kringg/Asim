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
    Qt/QFlowLayout.cpp

HEADERS  += MainWindow.h \
    MainContent.h \
    Qt/QFlowLayout.h

FORMS    += MainWindow.ui
