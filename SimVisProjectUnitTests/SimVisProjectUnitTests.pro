#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T09:17:26
#
#-------------------------------------------------

QT       += quick testlib

QT       -= gui
CONFIG += c++11

TARGET = tst_simvisprojectunittests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_simvisprojectunittests.cpp \
           ../SimVisProject/ghostbox.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
