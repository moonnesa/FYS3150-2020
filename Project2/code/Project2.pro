QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

INCLUDEPATH += D:\Armadillo\armadillo-9.200-RC1\include
DEPENDPATH += D:\Armadillo\armadillo-9.200-RC1\include

LIBS += -LD:\Armadillo\armadillo-9.200-RC1\examples\lib_win64 \
 -lblas_win64_MT \
 -llapack_win64_MT


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    all_functions.cpp \
    eigen_valuesandvectors.cpp \
    all_functions.cpp \
    2_e_eigen_valuesandvectors.cpp \
    count_iterations.cpp \
    3d_plot.cpp \
    matrix_size_calculation.cpp \
    unit_test_all.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    all_functions.h \
    all_functions.h
