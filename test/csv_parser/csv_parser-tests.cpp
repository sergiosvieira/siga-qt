#include <igloo/igloo_alt.h>
#include <vector>
#include "parsers/csv_parser.hpp"

using namespace std;
using namespace igloo;

Describe (CSVTest)
{
    It(LoadInputFileFromTextFileWithoutNewLine)
    {
        csv_parser p;
        p.init("input01.csv");
        vector<int> cols = {10, 10, 9, 9, 10};
        int i = 0;
        while (p.has_more_rows())
        {
            csv_row row = p.get_row();
            Assert::That(row.size(), Equals(cols[i++]));
        }
        Assert::That(p.get_record_count(), Equals(5));
    }
    It(LoadInputFileFromTextFileWithNewLine)
    {
        csv_parser p;
        p.init("input01.csv");
        vector<int> cols = {10, 10, 9, 9, 10};
        int i = 0;
        while (p.has_more_rows())
        {
            csv_row row = p.get_row();
            Assert::That(row.size(), Equals(cols[i++]));
        }
        Assert::That(p.get_record_count(), Equals(5));
    }
    It(LoadInputFileFromEmptyTextFile)
    {
        csv_parser p;
        p.init("input03.csv");
        while (p.has_more_rows())
        {
            csv_row row = p.get_row();
        }
        Assert::That(p.get_record_count(), Equals(1));
    }
    It(LoadInputFileFromTextFileWithFiveLineBreaks)
    {
        csv_parser p;
        p.init("input04.csv");
        while (p.has_more_rows())
        {
            csv_row row = p.get_row();
            Assert::That(row.size(), Equals(0));
        }
        Assert::That(p.get_record_count(), Equals(5));
    }
    It(LoadInputFileFromTextFileWithMixedLineBreaksAndRowsWithDifferentCols)
    {
        csv_parser p;
        p.init("input05.csv");
        vector<int> cols = {0, 2, 1, 3, 4, 0, 0, 2, 3};
        int i = 0;
        while (p.has_more_rows())
        {
            csv_row row = p.get_row();
            Assert::That(row.size(), Equals(cols[i++]));
        }
        Assert::That(p.get_record_count(), Equals(9));
    }
    It(IgnoreComments)
    {
        csv_parser p;
        p.init("input06.csv");
        char *comments[] = {"#\0", "//\0"};
        p.set_ignore_comments(2, comments);// it must be called after init method!!!
        vector<int> cols = {0, 0, 10, 10, 0, 9, 9, 10};
        int i = 0;
        while (p.has_more_rows())
        {
            csv_row row = p.get_row();
            Assert::That(row.size(), Equals(cols[i++]));
        }
        Assert::That(p.get_record_count(), Equals(6));
    }
    It(SkipLines)
    {
        csv_parser p;
        p.set_skip_lines(4);// Skip lines must be before init method!!!
        p.init("input07.csv");
        csv_row row = p.get_row();
        Assert::That(row.size(), Equals(5));
    }
    It(TestDelimiters)
    {
        csv_parser p;
        p.init("input08.csv");
        char *comments[] = {"#\0", "//\0"};
        p.set_ignore_comments(2, comments);// it must be called after init method!!!
        std::vector<int> delimiters = {',', ';', '\t', ' '};
        p.set_field_term_char_vector(delimiters.size(),
                                     delimiters.data());// it must be called after init method!!!

        while (p.has_more_rows())
        {
            csv_row row = p.get_row();
            Assert::That(row.size(), Is().EqualTo(3).Or().EqualTo(0));
        }
        Assert::That(p.get_record_count(), Equals(5));
    }
};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
