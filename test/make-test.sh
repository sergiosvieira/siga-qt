#!/bin/bash

function show_error
{
	echo "Error: Invalid number of parameters"
	echo "Usage: ./make-test.sh <test name>"
}

function create_qt_pro_file
{
	filename=$1/$1.pro
	echo "TEMPLATE = app" > $filename
	echo "TARGET = $1" >> $filename
	echo "INCLUDEPATH += . ../../lib/igloo ../../include" >> $filename
	echo "LIBS += -L../../build -lsiga-qt" >> $filename
	echo "SOURCES += $1-tests.cpp" >> $filename
}

function create_test_file_template
{
	filename=$1/$1-tests.cpp
	echo -e "#include <igloo/igloo_alt.h>\n" > $filename
	echo "using namespace std;" >> $filename
	echo "using namespace igloo;" >> $filename
	echo -e "using namespace SIGA::DS;\n" >> $filename
	echo -e "Describe (Test)\n{" >> $filename
	echo -e "\tIt() {}\n};\n" >> $filename
	echo -e "int main(int argc, char** argv)\n{" >> $filename
	echo "	return TestRunner::RunAllTests(argc, argv);" >> $filename
	echo "}" >> $filename
}

function create_test
{
	if [ -d $1 ]; then
		read -n1 -r -p "Warning: $1 will be destroyed. Press space to continue or any other to skip" key
		if [ "$key" = ' ' ]; then
			rm -rf $1
		fi
	else
		mkdir $1
	fi
	create_qt_pro_file $1
	create_test_file_template $1
}


if [ "$#" -ne 1 ]; then
	show_error
	exit 1
fi

create_test $1
