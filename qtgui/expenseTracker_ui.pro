#-------------------------------------------------
#
# Project created by QtCreator 2016-10-25T11:14:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = expenseTracker_ui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    auxillary.cpp \
    main_classes.cpp

HEADERS  += mainwindow.h \
    auxillary.h \
    main_classes.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
