QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = breasy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webview.cpp

HEADERS  += mainwindow.h \
    webview.h
