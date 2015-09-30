#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T23:10:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = qres
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS+= -luser32

SOURCES += main.cpp \
    windowmover.cpp

HEADERS += \
    windowmover.h
