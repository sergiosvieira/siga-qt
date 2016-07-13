#include <igloo/igloo_alt.h>
#include <string>

#include "utils/string-utils.h"

using namespace std;
using namespace igloo;
using namespace SIGA::DS;

Describe (StringUtilsTest)
{
    //Test TRIM
    It(RemoveSpaceUsingTrim_Left)
    {
        string input(" left");
        StringUtils::trim(input);
        Assert::That(input, Equals("left"));
    }
    It(RemoveSpaceUsingTrim_Right)
    {
        string input("right ");
        StringUtils::trim(input);
        Assert::That(input, Equals("right"));
    }
    It(RemoveSpaceUsingTrim_BothLeftRight)
    {
        string input(" trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim"));
    }
    It(RemoveSpaceUsingTrim_BothBetweenLeftRight)
    {
        string input(" trim trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(RemoveSpaceUsingTrim_BothBetweenLeft)
    {
        string input("trim trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(RemoveSpaceUsingTrim_BothBetweenRight)
    {
        string input(" trim trim");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(RemoveSpaceUsingTrim_BothBetweenThree)
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

};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
