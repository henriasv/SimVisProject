TEMPLATE = app
CONFIG += c++11

QT += qml quick widgets opengl openglextensions

QMAKE_CXXFLAGS += -frounding-math

SOURCES += main.cpp \
    mysimulator.cpp \
    ../LammpsIO/lammpsframe.cpp \
    ../LammpsIO/lammpsio.cpp \
    ../LammpsIO/vec3/vec3.cpp

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
    ../LammpsIO/vec3/vec3.h

unix|win32: LIBS += -lCGAL -lgmp
