TEMPLATE = subdirs
SUBDIRS = SimVis SimVisProject \
    SimVisProjectUnitTests
CONFIG += ordered
SimVisProject.depends = SimVis
SimVisProjectUnitTests.depends = SimVisProject

