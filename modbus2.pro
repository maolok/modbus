#-------------------------------------------------
#
# Project created by QtCreator 2020-06-04T10:42:03
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modbus2
TEMPLATE = app


SOURCES += main.cpp\
        serialport.cpp \
    principal.cpp \
    form.cpp

HEADERS  += serialport.h \
    principal.h \
    form.h

FORMS += \
    form.ui
