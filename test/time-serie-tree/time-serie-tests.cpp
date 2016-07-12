#include "data-structures/time-serie-tree.h"
#include <igloo/igloo_alt.h>
#include <tuple>

using namespace std;
using namespace igloo;
using namespace SIGA::DS;


Describe (TimeSerieTreeClassTest)
{
    It(InsertValueInYearlyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::YEARLY_TYPE);
        int stationID = 1;
        CDate date{1978, 01, 31};
        float value = 10.f;
        tree.setDateValue(date, stationID, value);
        tuple<float, float, float> result = tree.dateValues(date, stationID);
        // Day
        Assert::That(std::get<0>(result), Is().EqualToWithDelta(0.0273973, 0.001));
        // Month
        Assert::That(std::get<1>(result), Is().EqualToWithDelta(0.833f, 0.001));
        // Year
        Assert::That(std::get<2>(result), Equals(10.f));
    }
    It(InsertValueInMonthlyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::MONTHLY_TYPE);
        int stationID = 1;
        CDate date{1978, 01, 31};
        float value = 10.f;
        tree.setDateValue(date, stationID, value);
        tuple<float, float, float> result = tree.dateValues(date, stationID);
        // Day
        Assert::That(tree.dayValue(date, stationID), Is().EqualToWithDelta(0.3225f, 0.001));
        // Month
        Assert::That(tree.monthValue(date, stationID), Is().EqualToWithDelta(10.f, 0.001));
        // Year
        Assert::That(tree.yearValue(date, stationID), Is().EqualToWithDelta(10.f, 0.001));
    }
    It(InsertValueInDailyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::DAILY_TYPE);
        int stationID = 1;
        CDate date{1978, 01, 31};
        float value = 10.f;
        tree.setDateValue(date, stationID, value);
        tuple<float, float, float> result = tree.dateValues(date, stationID);
        // Day
        Assert::That(tree.dayValue(date, stationID), Equals(10.f));
        // Month
        Assert::That(tree.monthValue(date, stationID), Equals(10.f));
        // Year
        Assert::That(tree.yearValue(date, stationID), Equals(10.f));
    }
};


int main(int argc, char** argv)
{
    return TestRunner::RunAllTests(argc, argv);
}
