TEMPLATE = app
TARGET = string-utils
INCLUDEPATH += . ../../lib/igloo ../../include
LIBS += -L../../build -lsiga-qt
SOURCES += string-utils-tests.cpp
