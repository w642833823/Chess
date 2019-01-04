#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T21:27:52
#
#-------------------------------------------------

QT       += core gui
QT       += widgets gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MYChess
TEMPLATE = app


SOURCES += main.cpp\
    board.cpp \
    stone.cpp \
    Network.cpp

HEADERS  += \
    board.h \
    stone.h \
    Network.h

FORMS    += mainwindow.ui
