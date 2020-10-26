TEMPLATE = app
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += D:\Armadillo\armadillo-9.200-RC1\include
DEPENDPATH += D:\Armadillo\armadillo-9.200-RC1\include

LIBS += -LD:\Armadillo\armadillo-9.200-RC1\examples\lib_win64 \
 -lblas_win64_MT \
 -llapack_win64_MT


SOURCES += \
        main.cpp \
    wanderer.cpp \
    solver.cpp \
    solar_sysytem.cpp

HEADERS += \
    wanderer.h \
    solver.h \
    solar_system.h
DISTFILES +=
