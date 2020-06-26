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
    form.cpp \
    modbus.cpp

HEADERS  += serialport.h \
    form.h \
    modbus.h

FORMS += \
    form.ui
