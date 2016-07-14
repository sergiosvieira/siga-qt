#include <igloo/igloo_alt.h>

#include "converter/parser-options.h"
#include "data-structures/time-serie-tree-loader.h"
#include "parsers/csv_parser.hpp"


using namespace std;
using namespace igloo;
using namespace SIGA::DS;

Describe (TimeSerieTreeLoaderTest)
{
    // temporary
    It(ParserTest)
    {
        ParserOptions parserOptions;
        ConverterOptions convertOptions;
        TimeSerieTreeLoader::load("input01.txt",
                                  parserOptions,
                                  convertOptions);
    }
};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
