QT += core testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCDIR = ../../../src/mapledailytracker
INCLUDEPATH += $$INCDIR

HEADERS += $$INCDIR/resetchecker.h
SOURCES += $$INCDIR/resetchecker.cpp

SOURCES +=  tst_resetchecker.cpp
