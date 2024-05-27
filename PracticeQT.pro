QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basketwindow.cpp \
    calendarwindow.cpp \
    creatfolderwindow.cpp \
    creatwindow.cpp \
    filedisplaywindow.cpp \
    folderwindow.cpp \
    infowindow.cpp \
    main.cpp \
    mainwindow.cpp \
    settingswindow.cpp

HEADERS += \
    basketwindow.h \
    calendarwindow.h \
    creatfolderwindow.h \
    creatwindow.h \
    filedisplaywindow.h \
    folderwindow.h \
    infowindow.h \
    mainwindow.h \
    settingswindow.h

FORMS += \
    basketwindow.ui \
    calendarwindow.ui \
    creatfolderwindow.ui \
    creatwindow.ui \
    filedisplaywindow.ui \
    folderwindow.ui \
    infowindow.ui \
    mainwindow.ui \
    settingswindow.ui

TRANSLATIONS += \
    PracticeQT_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
    RC_ICONS = icon.ico
