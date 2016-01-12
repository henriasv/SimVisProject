TEMPLATE = app
CONFIG += c++11

QT += qml quick widgets opengl openglextensions

QMAKE_CXXFLAGS += -frounding-math

SOURCES += main.cpp \
    mysimulator.cpp \
    ../LammpsIO/lammpsframe.cpp \
    ../LammpsIO/lammpsio.cpp \
    ../LammpsIO/vec3/vec3.cpp \
    triangle.cpp \
    analysisstep.cpp \
    figure.cpp \
    graph.cpp \
    linegraph.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
include(../SimVis/library_deployment.pri)

HEADERS += \
    mysimulator.h \
    ../LammpsIO/lammpsframe.h \
    ../LammpsIO/lammpsio.h \
    ../LammpsIO/vec3/vec3.h \
    triangle.h \
    analysisstep.h \
    figure.h \
    graph.h \
    linegraph.h

unix|win32: LIBS += -lCGAL -lgmp
unix|win32: INCLUDEPATH += /usr/local/Cellar/cgal/4.6.3/include /usr/local/Cellar/boost/1.58.0/include /usr/local/Cellar/gmp/6.0.0a/include /usr/local/Cellar/mpfr/3.1.3/include
unix|win32: LIBS += -L/usr/local/Cellar/cgal/4.6.3/lib -L/usr/local/Cellar/boost/1.58.0/lib -L/usr/local/Cellar/gmp/6.0.0a/lib -L/usr/local/Cellar/mpfr/3.1.3/lib
