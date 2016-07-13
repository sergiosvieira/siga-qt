#include <igloo/igloo_alt.h>
#include <string>

#include "utils/string-utils.h"

using namespace std;
using namespace igloo;
using namespace SIGA::DS;

Describe (StringUtilsTest)
{
    It(RemoveSpaceUsingTrimLeft)
    {
        string input(" left");
        StringUtils::trim(input);
        Assert::That(input, Equals("left"));
    }
    It(RemoveSpaceUsingTrimRight)
    {
        string input("right ");
        StringUtils::trim(input);
        Assert::That(input, Equals("right"));
    }
    It(RemoveSpaceUsingTrimBothLeftRight)
    {
        string input(" trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim"));
    }
    It(RemoveSpaceUsingTrimBothBetweenLeftRight)
    {
        string input(" trim trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(RemoveSpaceUsingTrimBothBetweenLeft)
    {
        string input("trim trim ");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
    It(RemoveSpaceUsingTrimBothBetweenRight)
    {
        string input(" trim trim");
        StringUtils::trim(input);
        Assert::That(input, Equals("trim trim"));
    }
};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
