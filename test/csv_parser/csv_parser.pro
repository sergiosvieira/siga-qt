TEMPLATE = app
TARGET = csv_parser
INCLUDEPATH += . ../../lib/igloo ../../include
LIBS += -L../../build -lsiga-qt
SOURCES += csv_parser-tests.cpp
