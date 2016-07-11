#include "data-structures/time-serie-tree.h"
#include <igloo/igloo_alt.h>
#include <tuple>

using namespace std;
using namespace igloo;
using namespace SIGA::DS;


Describe (TimeSerieTreeClassTest)
{
    It(InsertValueInYearlyTreeTest)
    {
        TimeSerieTree tree(1978, PeriodType::YEARLY_TYPE);
        int stationID = 1;
        CDate date{1978, 01, 31};
        float value = 10.f;
        tree.insertStationID(stationID);
        tree.insertValueOnStation(date, stationID, value);
        tuple<float, float, float> result = tree.valueOnStation(date, stationID);
        // Day
        Assert::That(std::get<0>(result), Equals(value));
        // Month
        Assert::That(std::get<1>(result), Equals(value));
        // Year
        Assert::That(std::get<2>(result), Equals(value));
    }
};


int main(int argc, char** argv)
{
    return TestRunner::RunAllTests(argc, argv);
}
