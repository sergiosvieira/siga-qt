#include <igloo/igloo_alt.h>
#include <string>

#include "utils/string-utils.h"

using namespace std;
using namespace igloo;
using namespace SIGA::DS;

Describe (StringUtilsTest)
{
    It(RemoveSpaceUsingTrimX)
    {
        //Describle: Remove Space Blank Left or Right position
        string input(" left");
        StringUtils::trim(input);
        Assert::That(input, Equals("left"));
    }
};

int main(int argc, char** argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
