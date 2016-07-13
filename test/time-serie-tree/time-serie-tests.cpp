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
    It(InsertTwoValuesInYearlyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::YEARLY_TYPE);
        int stationID = 1;
        CDate date{1978, 01, 31};
        float value = 10.f;
        tree.setDateValue(date, stationID, value);
        date += 1;
        // When a yearly period type, only will be considered the last value inserted
        tree.setDateValue(date, stationID, 20.f);
        date -= 1;
        // Day
        Assert::That(tree.dayValue(date, stationID), Is().EqualToWithDelta(0.05479f, 0.001));
        // Month
        Assert::That(tree.monthValue(date, stationID), Is().EqualToWithDelta(1.666f, 0.001));
        // Year
        Assert::That(tree.yearValue(date, stationID), Equals(20.f));
    }
    It(InsertValueInMonthlyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::MONTHLY_TYPE);
        int stationID = 1;
        CDate date{1978, 01, 31};
        float value = 10.f;
        tree.setDateValue(date, stationID, value);
        // Day
        Assert::That(tree.dayValue(date, stationID), Is().EqualToWithDelta(0.3225f, 0.001));
        // Month
        Assert::That(tree.monthValue(date, stationID), Is().EqualToWithDelta(10.f, 0.001));
        // Year
        Assert::That(tree.yearValue(date, stationID), Is().EqualToWithDelta(10.f, 0.001));
    }
    It(InsertTwoValuesInMonthlyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::MONTHLY_TYPE);
        int stationID = 1;
        CDate date1{1978, 01, 01};
        CDate date2{1978, 02, 01};
        tree.setDateValue(date1, stationID, 10.f);
        tree.setDateValue(date2, stationID, 20.f);
        // Day
        Assert::That(tree.dayValue(date1, stationID), Is().EqualToWithDelta(0.3225f, 0.001));
        // Month
        Assert::That(tree.monthValue(date1, stationID), Is().EqualToWithDelta(10.0f, 0.001));
        // Year
        Assert::That(tree.yearValue(date1, stationID), Equals(30.f));
    }
    It(InsertValueInDailyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::DAILY_TYPE);
        int stationID = 1;
        CDate date{1978, 01, 31};
        float value = 10.f;
        tree.setDateValue(date, stationID, value);
        // Day
        Assert::That(tree.dayValue(date, stationID), Equals(10.f));
        // Month
        Assert::That(tree.monthValue(date, stationID), Equals(10.f));
        // Year
        Assert::That(tree.yearValue(date, stationID), Equals(10.f));
    }
    It(InsertTwoValuesInDailyTimeSerieTree)
    {
        TimeSerieTree tree(1978, PeriodType::DAILY_TYPE);
        int stationID = 1;
        CDate date1{1978, 01, 01};
        CDate date2{1978, 01, 02};
        tree.setDateValue(date1, stationID, 10.f);
        tree.setDateValue(date2, stationID, 20.f);
        // Day
        Assert::That(tree.dayValue(date1, stationID), Is().EqualToWithDelta(10.f, 0.001));
        Assert::That(tree.dayValue(date2, stationID), Is().EqualToWithDelta(20.f, 0.001));
        // Month
        Assert::That(tree.monthValue(date1, stationID), Equals(30.0f));
        // Year
        Assert::That(tree.yearValue(date1, stationID), Equals(30.f));
    }
    It(WhenInsertAInvalidDateInYearlyTimeSerie)
    {
        TimeSerieTree tree(1978, PeriodType::YEARLY_TYPE);
        int stationID = 1;
        CDate date1{1979, 01, 01};
        AssertThrows(std::invalid_argument, tree.setDateValue(date1, stationID, 10.f));
    }
    It(WhenInsertAInvalidDateInMonthlyTimeSerie)
    {
        TimeSerieTree tree(1978, PeriodType::MONTHLY_TYPE);
        int stationID = 1;
        CDate date1{1979, 01, 01};
        AssertThrows(std::invalid_argument, tree.setDateValue(date1, stationID, 10.f));
    }
    It(WhenInsertAInvalidDateInDailyTimeSerie)
    {
        TimeSerieTree tree(1978, PeriodType::DAILY_TYPE);
        int stationID = 1;
        CDate date1{1979, 01, 01};
        AssertThrows(std::invalid_argument, tree.setDateValue(date1, stationID, 10.f));
    }
};


int main(int argc, char** argv)
{
    return TestRunner::RunAllTests(argc, argv);
}
