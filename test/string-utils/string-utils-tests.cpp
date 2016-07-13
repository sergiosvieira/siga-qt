#include <igloo/igloo_alt.h>
#include <string>

#include "utils/string-utils.h"

using namespace std;
using namespace igloo;
using namespace SIGA::DS;

Describe (StringUtilsTest)
{
    //Test TRIM
    It(Trim_Left)
    {
        string input(" left");
        StringUtils::trim(input);
        Assert::That(input, Equals("left"));
    }
    It(Trim_Right)
    {
        string input("right ");
        StringUtils::trim(input);
        Assert::That(input, Equals("right"));
    }
    It(Trim_BothLeftRight)
    {
        string input(" trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim"));
    }
    It(Trim_BothBetweenLeftRight)
    {
        string input(" trim trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(Trim_BothBetweenLeft)
    {
        string input("trim trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(Trim_BothBetweenRight)
    {
        string input(" trim trim");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(Trim_BothBetweenThree)
    {
        string input(" t h r e e ");
        StringUtils::trim(input);
        Assert::That(input, Equals("t h r e e"));
    }

    //Test SPLIT
    It(Split_SimpleTest)
    {
        string input("first");
        vector<std::string> result;
        StringUtils::split(result, input, ";");

        Assert::That(result.size(), Equals(1));
        Assert::That(result[0], Equals("first"));
    }
    It(Split_SingleComma)
    {
        string input("first;");
        vector<std::string> result;
        StringUtils::split(result, input, ";");

        Assert::That(result.size(), Equals(1));
        Assert::That(result[0], Equals("first"));
    }
    It(Split_SingleElements)
    {
        std::string input("first,second,");
        std::vector<std::string> result;
        StringUtils::split(result, input, ",");

        Assert::That(result.size(), Equals(2));
        Assert::That(result[0], Equals("first"));
        Assert::That(result[1], Equals("second"));
    }
    It(Split_SingleElementsHifen)
    {
        std::string input("first-second-three-four");
        std::vector<std::string> result;
        StringUtils::split(result, input, "-");

        Assert::That(result.size(), Equals(4));
        Assert::That(result[0], Equals("first"));
        Assert::That(result[1], Equals("second"));
        Assert::That(result[2], Equals("three"));
        Assert::That(result[3], Equals("four"));
    }

    //Test Replace
    It(Replace_Single){
        string input("The quick brown fox jumps over the lazy dog");
        string from("brown");
        string to("red");

        bool result = StringUtils::replace(input, from, to);

        Assert::That(result, true);
        Assert::That(input, Equals("The quick red fox jumps over the lazy dog"));
    }
    It(Replace_ReplaceTextNotFound)
    {
        string input("The quick brown fox jumps over the lazy dog");
        string from("red");
        string to("brow");

        bool result = StringUtils::replace(input, from, to);

        Assert::That(result, true);
        Assert::That(input, Equals("The quick red fox jumps over the lazy dog"));
    }
    It(Replace_TwoReplacements)
    {
        string input("The quick brown fox jumps over the quick dog");
        string from("quick");
        string to("lazy");

        bool result = StringUtils::replace(input, from, to);

        Assert::That(result, true);
        Assert::That(input, Equals("The lazy brown fox jumps over the lazy dog"));
    }

    //Test CreateLayername
    It(CreateLayername)
    {
        std::string input("shapefile.shp");
        std::string result;

        StringUtils::createsLayerName(result, input.c_str());

        Assert::That(result, "shapefile_layer");
    }

    //Normalizer Text
    It(NormalizeLowercase)
    {
        std::string input("âàáãäêèéëîìíïôòóõöûùúüç");
        std::string result;

        StringUtils::normalize(result, input);

        Assert::That(result, "aaaaaeeeeiiiiooooouuuuc");
    }
    It(NormalizeUppercase)
    {
        std::string input("ÂÀÁÃÄÊÈÉËÎÌÍÏÔÒÒÔÖÛÙÚÜÇ");
        std::string result;

        StringUtils::normalize(result, input);

        Assert::That(result, "AAAAAEEEEIIIIOOOOOUUUUC");

    }

};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
