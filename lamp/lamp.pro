#-------------------------------------------------
#
# Project created by QtCreator 2015-06-13T14:07:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lamp
TEMPLATE = app

INCLUDEPATH += .\


RESOURCES += \
    lamp.qrc


SOURCES += src/main.cpp \
    src/mainwidget.cpp

HEADERS  += \
    src/mainwidget.h \
    src/lampface.h

FORMS    += \
    _ui/mainWidget.ui


OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
RCC_DIR = tmp/rcc
UI_DIR = _ui_temp
