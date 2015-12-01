TEMPLATE = app
CONFIG += c++11

QT += qml quick widgets opengl openglextensions



SOURCES += main.cpp \
    ../voronoi-md-analysis/LammpsIO/vec3/vec3.cpp \
    ../voronoi-md-analysis/LammpsIO/lammpsframe.cpp \
    ../voronoi-md-analysis/LammpsIO/lammpsio.cpp \
    ../voronoi-md-analysis/voro/src/c_loops.cc \
    ../voronoi-md-analysis/voro/src/cell.cc \
    ../voronoi-md-analysis/voro/src/common.cc \
    ../voronoi-md-analysis/voro/src/container.cc \
    ../voronoi-md-analysis/voro/src/container_prd.cc \
    ../voronoi-md-analysis/voro/src/pre_container.cc \
    ../voronoi-md-analysis/voro/src/unitcell.cc \
    ../voronoi-md-analysis/voro/src/v_base.cc \
    ../voronoi-md-analysis/voro/src/v_base_wl.cc \
    ../voronoi-md-analysis/voro/src/v_compute.cc \
    ../voronoi-md-analysis/voro/src/voro++.cc \
    ../voronoi-md-analysis/voro/src/wall.cc \
    ../voronoi-md-analysis/polygon.cpp \
    ../voronoi-md-analysis/sphere.cpp \
    ../voronoi-md-analysis/triangle.cpp \
    ../voronoi-md-analysis/voronoifracturetracer.cpp \
    mysimulator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
include(../SimVis/library_deployment.pri)

HEADERS += \
    mysimulator.h \
    ../voronoi-md-analysis/LammpsIO/vec3/vec3.h \
    ../voronoi-md-analysis/LammpsIO/lammpsframe.h \
    ../voronoi-md-analysis/LammpsIO/lammpsio.h \
    ../voronoi-md-analysis/voro/src/c_loops.hh \
    ../voronoi-md-analysis/voro/src/cell.hh \
    ../voronoi-md-analysis/voro/src/common.hh \
    ../voronoi-md-analysis/voro/src/config.hh \
    ../voronoi-md-analysis/voro/src/container.hh \
    ../voronoi-md-analysis/voro/src/container_prd.hh \
    ../voronoi-md-analysis/voro/src/pre_container.hh \
    ../voronoi-md-analysis/voro/src/rad_option.hh \
    ../voronoi-md-analysis/voro/src/unitcell.hh \
    ../voronoi-md-analysis/voro/src/v_base.hh \
    ../voronoi-md-analysis/voro/src/v_compute.hh \
    ../voronoi-md-analysis/voro/src/voro++.hh \
    ../voronoi-md-analysis/voro/src/wall.hh \
    ../voronoi-md-analysis/voro/src/worklist.hh \
    ../voronoi-md-analysis/polygon.h \
    ../voronoi-md-analysis/sphere.h \
    ../voronoi-md-analysis/triangle.h \
    ../voronoi-md-analysis/voronoifracturetracer.h
