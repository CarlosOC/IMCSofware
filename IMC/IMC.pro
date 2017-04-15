#-------------------------------------------------
#
# Project created by QtCreator 2017-04-06T18:31:27
#
#-------------------------------------------------

QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IMC
TEMPLATE = app


SOURCES += main.cpp\
        imcsoftware.cpp \
    agregarcliente.cpp \
    dialoglistaclientes.cpp \
    dialogbuscarcliente.cpp \
    dialogficha.cpp \
    console.cpp \
    settingsdialog.cpp

HEADERS  += imcsoftware.h \
    agregarcliente.h \
    dialoglistaclientes.h \
    dialogbuscarcliente.h \
    dialogficha.h \
    console.h \
    settingsdialog.h

FORMS    += imcsoftware.ui \
    agregarcliente.ui \
    dialoglistaclientes.ui \
    dialogbuscarcliente.ui \
    dialogficha.ui \
    settingsdialog.ui
