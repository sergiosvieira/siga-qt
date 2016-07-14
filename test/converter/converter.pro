TEMPLATE = app
TARGET = converter
INCLUDEPATH += . ../../lib/igloo ../../include
LIBS += -L../../build -lsiga-qt
SOURCES += converter-tests.cpp
