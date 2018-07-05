#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T14:14:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrugioGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
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
    namespaces/Command.cpp \
    namespaces/Drugio.cpp \
    namespaces/ReturnStructures.cpp \
    namespaces/Time.cpp \
    main 2.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
        mainwindow.h \
    namespaces/includes/Actions.hpp \
    namespaces/includes/Command.hpp \
    namespaces/includes/DBConfig.hpp \
    namespaces/includes/Time.hpp \
    resources/sqlite_modern_cpp/lists/error_codes.h \
    resources/sqlite_modern_cpp/utility/function_traits.h \
    resources/sqlite_modern_cpp/utility/uncaught_exceptions.h \
    resources/sqlite_modern_cpp/utility/utf16_utf8.h \
    resources/sqlite_modern_cpp/errors.h \
    resources/sqlite_modern_cpp/log.h \
    resources/sqlite_modern_cpp/sqlcipher.h \
    resources/sqlite_modern_cpp/type_wrapper.h \
    resources/sqlite_modern_cpp.h \
    mainwindow.h

FORMS += \
        mainwindow.ui \
    mainwindow.ui

DISTFILES += \
    logs/logs.sql \
    logs/debug.db \
    logs/logs.db

SUBDIRS += \
    DrugioGUI.pro
