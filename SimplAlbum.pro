QT += core gui widgets

TARGET = SimplAlbum
TEMPLATE = app

SOURCES += \
    main.cpp\
    MainWindow.cpp \
    Content/Content.cpp \
    Content/ContentFull.cpp \
    Content/ContentThumbs.cpp \
    Image/Image.cpp \
    Image/ImagePath.cpp \
    Image/ImageThumb.cpp \
    Qt/QFlowLayout.cpp \
    Qt/EditApps.cpp

HEADERS += \
    MainWindow.h \
    Content/Content.h \
    Content/ContentFull.h \
    Content/ContentThumbs.h \
    Image/Image.h \
    Image/ImagePath.h \
    Image/ImageThumb.h \
    Qt/QFlowLayout.h \
    Qt/EditApps.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    Resources/Resources.qrc

DISTFILES +=

RC_FILE += \
    Resources/Resources.rc
