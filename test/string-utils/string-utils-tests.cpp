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
    //End TRIM
};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
