#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T14:42:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ufsspMap
TEMPLATE = app


SOURCES += main.cpp\
        mainmap.cpp \
    upointer.cpp \
    scenetypes.cpp \
    adminform.cpp \
    airobject.cpp \
    graphicsscene.cpp \
    moveitem.cpp \
    sceneitem.cpp \
    targetnumber.cpp \
    referenceairform.cpp

HEADERS  += mainmap.h \
    scenetypes.h \
    upointer.h \
    adminform.h \
    airobject.h \
    graphicsscene.h \
    moveitem.h \
    sceneitem.h \
    targetnumber.h \
    referenceairform.h

FORMS    += mainmap.ui \
    adminform.ui

RESOURCES += \
    src.qrc \
    buttonimage.qrc
