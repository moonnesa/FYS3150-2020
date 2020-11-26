TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += D:\Armadillo\armadillo-9.200-RC1\include
DEPENDPATH += D:\Armadillo\armadillo-9.200-RC1\include

LIBS += -LD:\Armadillo\armadillo-9.200-RC1\examples\lib_win64 \
 -lblas_win64_MT \
 -llapack_win64_MT

SOURCES += main.cpp \
    lib.cpp \
    ising.cpp


HEADERS += ising.h \
    lib.h
DISTFILES +=
