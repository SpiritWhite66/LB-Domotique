QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TEST2
TEMPLATE = app

HEADERS += \
    token_gestion.h \
    liste_attente_gestion.hpp \
    protocol.h \
    windows.h

SOURCES += \
    token_gestion.cpp \
    liste_attente_gestion.cpp \
    protocol.cpp \
    main.cpp \
    windows.cpp

include(qextserialport/src/qextserialport.pri)
