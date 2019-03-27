#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T10:16:13
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QAssembler_console
CONFIG   += console
CONFIG   -= app_bundle

CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    assemblycode.cpp \
    machinecode.cpp \
    r_type.cpp \
    i_type.cpp \
    j_type.cpp \
    assembler.cpp

HEADERS += \
    assemblycode.h \
    machinecode.h \
    r_type.h \
    i_type.h \
    j_type.h \
    assembler.h
