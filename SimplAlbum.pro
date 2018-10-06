QT += core gui widgets

TARGET = SimplAlbum
TEMPLATE = app

SOURCES += \
    main.cpp\
    MainContent.cpp \
    MainWindow.cpp \
    Image/Image.cpp \
    Image/ImagePath.cpp \
    Image/ImageThumb.cpp \
    Qt/QFlowLayout.cpp \

HEADERS += \
    MainContent.h \
    MainWindow.h \
    Image/Image.h \
    Image/ImagePath.h \
    Image/ImageThumb.h \
    Qt/QFlowLayout.h \

FORMS += \
    MainWindow.ui

RESOURCES += \
    Resources/Resources.qrc

DISTFILES +=

RC_FILE += \
    Resources/Resources.rc
