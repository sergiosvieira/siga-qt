#include <igloo/igloo_alt.h>

#include "converter/converter.h"
#include <string>

using namespace igloo;

Describe (ConverterClassTest)
{
    It(loadTreeTest)
    {
        SIGA::ParserOptions parserOptions;
        SIGA::ConverterOptions converterOptions;
        SIGA::Converter::load("filename.txt",parserOptions, converterOptions);
        SIGA::Converter::loadTree("filename.txt",parserOptions, converterOptions);
    }
};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
