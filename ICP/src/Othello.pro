#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T16:49:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Othello
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stone.cpp \
    board.cpp \

HEADERS  += mainwindow.h \
    stone.h \
    board.h \
    save.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

CONFIG += c++11
