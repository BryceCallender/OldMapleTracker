QT       += core gui widgets

TARGET = MapleDailyTracker
TEMPLATE = app

RC_ICONS += MapleTracker.ico
ICON = MapleTracker.icns

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECAbTED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++20

SOURCES += \
        character.cpp \
        characterdialog.cpp \
        filemanager.cpp \
        main.cpp \
        mainwindow.cpp \
        mapleactiondialog.cpp \
        mapleactionlistwidgetitem.cpp \
        preferences.cpp \
        progress.cpp \
        progresscontent.cpp \
        qmodernprogressbar.cpp \
        resetchecker.cpp \
        trackertabcontent.cpp \
        trackertabwidget.cpp \
        trackerwidget.cpp

HEADERS += \
    characterdialog.h \
    mapleaction.h \
    character.h \
    filemanager.h \
    mapleactiondialog.h \
    mapleactionlistwidgetitem.h \
    preferences.h \
    progress.h \
    progresscontent.h \
    qmodernprogressbar.h \
    resetchecker.h \
    resetdata.h \
    savedata.h \
        mainwindow.h \
    trackertabcontent.h \
    trackertabwidget.h \
    trackerwidget.h

FORMS += \
        characterdialog.ui \
        mainwindow.ui \
        mapleactiondialog.ui \
        preferences.ui \
        progress.ui \
        progresscontent.ui \
        trackertabcontent.ui \
        trackertabwidget.ui \
        trackerwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
