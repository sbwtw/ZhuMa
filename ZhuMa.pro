#-------------------------------------------------
#
# Project created by QtCreator 2014-07-28T23:00:28
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZhuMa
TEMPLATE = app


SOURCES += main.cpp\
        zhuma.cpp \
    metrobutton.cpp \
    luqucheck.cpp \
    login.cpp \
    chengjicheck.cpp \
    helper.cpp \
    kechengbiaocheck.cpp \
    displaykechengbiao.cpp \
    displaykechengbiaomodel.cpp \
    aboutwidget.cpp \
    feedback.cpp \
    cetcheck.cpp

HEADERS  += zhuma.h \
    metrobutton.h \
    luqucheck.h \
    login.h \
    chengjicheck.h \
    helper.h \
    kechengbiaocheck.h \
    displaykechengbiao.h \
    displaykechengbiaomodel.h \
    aboutwidget.h \
    feedback.h \
    cetcheck.h

FORMS    += zhuma.ui \
    luqucheck.ui \
    login.ui \
    chengjicheck.ui \
    kechengbiaocheck.ui \
    displaykechengbiao.ui \
    feedback.ui \
    cetcheck.ui \
    aboutwidget.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    ZhuMaResource.qrc

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    android/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

DEFINES += VERSION=\\\"1.3\\\"
