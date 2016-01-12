TEMPLATE = subdirs
SUBDIRS = SimVis SimVisProject
CONFIG += ordered
SimVisProject.depends = SimVis
SimVisProjectTest.depends = SimVisProject

