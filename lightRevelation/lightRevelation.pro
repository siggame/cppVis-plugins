INCLUDEPATH += ../interfaces \
 ../common/ 

DEPENDPATH += ../common/ 

TEMPLATE = lib
TARGET = lightRevelation
SOURCES = *.cpp
HEADERS += *.h

CONFIG += debug plugin 
QT += opengl
debug:DEFINES += __DEBUG__
QT+= opengl

DESTDIR = ../plugins/
