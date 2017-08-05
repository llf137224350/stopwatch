#-------------------------------------------------
#
# Project created by QtCreator 2017-08-04T10:15:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stopwatch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    utils.cpp \
    myitem.cpp

HEADERS += \
        mainwindow.h \
    utils.h \
    myitem.h
RC_FILE = app.rc

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -g

isEmpty(BINDIR):BINDIR=/usr/bin
isEmpty(APPDIR):APPDIR=/usr/share/applications
isEmpty(ICONSDIR):ICONSDIR=/usr/share/icons/stopwatch

target.path = $$INSTROOT$$BINDIR
desktop.path = $$INSTROOT$$APPDIR
desktop.files = stopwatch.desktop

icons.path = $$INSTROOT$$ICONSDIR
icons.files = app.ico

INSTALLS += target desktop icons
