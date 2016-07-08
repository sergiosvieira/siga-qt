
#include <assert.h>
#include "../../include/date/cdatecalc.h"

// Table which maps month number to non-leap number of days in that month
const static Int32 s_DaysPerMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//---------------------------------------------------------------------------
// Pivot year used for 2 digit - 4 digit conversions
//
static Int32 s_PivotYear = 38;

//---------------------------------------------------------------------------

void CDateCalc::SetPivotYear( Int32 pivotYear )
{
	s_PivotYear = pivotYear;
}

//---------------------------------------------------------------------------

Int32 CDateCalc::GetPivotYear()
{
	return s_PivotYear;
}

//---------------------------------------------------------------------------

Int32 CDateCalc::EnsureYearWithCentury( Int32 year )
{
	if (year < 100) {
		year += 1900 + 100*(year < s_PivotYear);
	}

	return year;
}

//---------------------------------------------------------------------------

Int32 CDateCalc::CalcJulianPeriod(Int32 year, Int32 month, Int32 day)
{
	assert(day >= 1 && day <= DaysInMonth(month, IsLeapYear(year) ? true : false));
	// This magical calculation taken from:
	//	http://www.faqs.org/faqs/calendars/faq/part2/
	UInt32 a = (14-month)/12;
	UInt32 y = EnsureYearWithCentury(year)+4800-a;
	UInt32 m = month + 12*a - 3;

	return day + (153*m+2)/5 + y*365 + y/4 - y/100 + y/400 - 32045;
}

Int32 CDateCalc::CalcJulianPeriod(Int32 year, Int32 dayOfYear)
{
	// A modification of the calculation above
	UInt32 y = 	EnsureYearWithCentury(year)+4799;
	return dayOfYear + y*365 + y/4 - y/100 + y/400 - 31739;
}

//---------------------------------------------------------------------------

void CDateCalc::CalculateDate(Int32 julianPeriod, DateS & dateDetails, bool wantWeekDetails)
{
	// This magical calculation taken from:
	//	http://www.faqs.org/faqs/calendars/faq/part2/
	Int32 a = julianPeriod + 32044;
	Int32 b = (4*a+3)/146097;
	Int32 c = a - (b*146097)/4;

	Int32 d = (4*c+3)/1461;
	Int32 e = c - (1461*d)/4;
	Int32 m = (5*e+2)/153;

	Int32 Day = e - (153*m+2)/5 + 1;
	Int32 Month = m + 3 - 12*(m/10);
	Int32 Year = b*100 + d - 4800 + m/10;

	// This formula derived from above JD calculation for 1-Jan-XXXX
	Int32 y = Year+4799;
	Int32 DayOfYear = julianPeriod - (y*365 + y/4 - y/100 + y/400 - 31739);

	// Standard leap year formula
	Int32 IsLeapYear = (Year % 4 == 0) & ((Year % 100 != 0) | (Year % 400 == 0));

	// Fill struct
	dateDetails.m_Year = Year;
	dateDetails.m_DayOfYear = DayOfYear;
	dateDetails.m_Month = Month;
	dateDetails.m_Day = Day;
	dateDetails.m_IsLeapYear = IsLeapYear;

	if (wantWeekDetails) {
		// This magical calculation taken from:
		//	http://www.faqs.org/faqs/calendars/faq/part3/
		Int32 d4 = (julianPeriod+31741 - (julianPeriod % 7)) % 146097 % 36524 % 1461;
		Int32 L  = d4/1460;
		Int32 d1 = ((d4-L) % 365) + L;
		Int32 WeekNumber = d1/7+1;

		Int32 WeekDay = julianPeriod%7 + 1;

		// Week number 1 and 52/52 of a year may actually be in the
		//	previous/next year. Adjust the year number for those cases
		Int32 WeekYear = Year + ((WeekNumber == 1) & (Month == 12)) - ((WeekNumber > 51) & (Month == 1));

		dateDetails.m_DayOfWeek = WeekDay;
		dateDetails.m_WeekOfYear = WeekNumber;
		dateDetails.m_YearForWeekOfYear = WeekYear;
	}

}

//---------------------------------------------------------------------------

Int32 CDateCalc::DaysInMonth(Int32 month, bool isLeapYear)
{
	return (s_DaysPerMonth[month] + ((month)==2 && (isLeapYear)));
}

//---------------------------------------------------------------------------

Int32 CDateCalc::IsLeapYear(Int32 year)
{
	return (year % 4 == 0) & ((year % 100 != 0) | (year % 400 == 0));
}

