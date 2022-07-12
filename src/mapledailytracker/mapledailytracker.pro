QT       += core gui widgets

TARGET = mapledailytracker
TEMPLATE = app

RC_ICONS += MapleTracker.ico
ICON = MapleTracker.icns

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++20

SOURCES += \
        character.cpp \
        characterdialog.cpp \
        filemanager.cpp \
        logger.cpp \
        main.cpp \
        maintenancetool.cpp \
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
    logger.h \
    maintenancetool.h \
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
    trackerwidget.h \

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

INCLUDEPATH += "../external/spdlog/include"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    vendor/spdlog/fmt/bundled/fmt.license.rst

RESOURCES += \
    resources.qrc
