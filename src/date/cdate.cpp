
#include <assert.h>
#include <regex>
#include "../../include/date/cdate.h"
#include "../../include/date/cdatecalc.h"
#include <set>
#include <sstream>
#include <iomanip>

#if defined(_MSC_VER)
#pragma warning(disable: 4127)
#endif

// Macro to ensure internal representation is as Julian day
#define REPASJD(obj) \
do { \
	if ((obj).m_Date <  0) \
		(obj).InternalToJD(); \
} while (0)

// Macro to ensure internal representation is as date components
#define REPASDATE(obj) \
do { \
	if ((obj).m_Date >= 0) \
		(obj).InternalToDate(); \
} while (0)

#define BITOFFSETYEAR 0
#define BITSIZEYEAR 10
#define BITOFFSETWEEKOFYEAR 10
#define BITSIZEWEEKOFYEAR 6
#define BITOFFSETDAY 16
#define BITSIZEDAY 5
#define BITOFFSETDAYOFWEEK 21
#define BITSIZEDAYOFWEEK 3
#define BITOFFSETMONTH 24
#define BITSIZEMONTH 4
#define BITOFFSETWEEKYEARDIF 28
#define BITSIZEWEEKYEARDIF 2
#define BITOFFSETISLEAPYEAR 30
#define BITSIZEISLEAPYEAR 1

// We're using 10 bits to store the year (1024 years). Set the minimum year
#define MINIMUMYEAR 1500

// Macro to extract bitfield component at offset of length from v
#define GETCOMPONENT(v, offset, length) ( (v)>>(offset) & ((1<<(length))-1) )

using std::regex;
using std::string;
using std::sregex_token_iterator;

// Table which maps month number to non-leap year day number of the first day of that month
const static Int32 s_YearDayFromMonth[] = { 0, 1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

CDate::CDate(Int32 year, Int32 month, Int32 day)
{
	m_Date = (Int32)CDateCalc::CalcJulianPeriod(year, month, day);
}

CDate::CDate(Int32 year, Int32 dayOfYear)
{
	m_Date = (Int32)CDateCalc::CalcJulianPeriod(year, dayOfYear);
}

CDate::CDate(const std::string& a_dateString, const std::string& a_dateFormatString)
{
	*this = FromStringWithFormat(a_dateString, a_dateFormatString);
}

CDate CDate::GetSystemDate()
{
	// TODO: Get this to work
	return 0;//CDate(Int32(time(0) / 86400));
}

bool CDate::operator==(const CDate & compare) const
{
	// Ensure the internal representation of both objects is as days
	REPASJD(*this); REPASJD(compare);
	// Simple day compare
	return m_Date == compare.m_Date;
}

bool CDate::operator!=(const CDate& otherDate) const
{
	// Ensure the internal representation of both objects is as days
	REPASJD(*this); 
	REPASJD(otherDate);
	// Simple day compare
	return m_Date != otherDate.m_Date;
}

bool CDate::operator<(const CDate & compare) const
{
	// Ensure the internal representation of both objects is as days
	REPASJD(*this); REPASJD(compare);
	// Simple day compare
	return m_Date < compare.m_Date;
}

CDate CDate::operator+( Int32 dateOffset) const
{
	return CDate(GetJulianDay() + dateOffset);
}

CDate CDate::operator-( Int32 dateOffset) const
{
	return CDate(GetJulianDay() - dateOffset);
}

Int32 CDate::operator-( const CDate& otherDate) const
{
	// Ensure the internal representation of both objects is as days
	REPASJD(*this); REPASJD(otherDate);

	return m_Date - otherDate.m_Date;
}

// Description: Self addition operator

CDate& CDate::operator+=( Int32 dateOffset)
{
	REPASJD(*this);
	m_Date += dateOffset;
	assert(m_Date >= 0);
	return *this;
}

// Description: Self subtraction operator

CDate& CDate::operator-=( Int32 dateOffset)
{
	REPASJD(*this);
	m_Date -= dateOffset;
	assert(m_Date >= 0);
	return *this;
}

// Description: Returns the year represented by this date (1500-2500)

Int32 CDate::GetYear() const
{
	REPASDATE(*this);
	Int32 Year = GETCOMPONENT(m_Date, BITOFFSETYEAR, BITSIZEYEAR) + MINIMUMYEAR;
	assert(Year >= MINIMUMYEAR && Year <= MINIMUMYEAR + 100000);
	return Year;
}

// Description: Returns the quarter represented by this date (1-4)

Int32 CDate::GetQuarter() const
{
	REPASDATE(*this);
	Int32 Quarter = GETCOMPONENT(m_Date, BITOFFSETMONTH, BITSIZEMONTH) / 3;
	assert(Quarter >= 1 && Quarter <= 4);
	return Quarter;
}

// Description: returns the month in the year represented by this date (1-12)

Int32 CDate::GetMonth() const
{
	REPASDATE(*this);
	Int32 Month = GETCOMPONENT(m_Date, BITOFFSETMONTH, BITSIZEMONTH);
	assert(Month >= 1 && Month <= 12);
	return Month;
}

// Description: returns the day in the month represented by this date (1-31)

Int32 CDate::GetDay() const
{
	REPASDATE(*this);
	Int32 Day = GETCOMPONENT(m_Date, BITOFFSETDAY, BITSIZEDAY);
	assert(Day >= 1 && Day <= CDateCalc::DaysInMonth(GetMonth(), GETCOMPONENT(m_Date, BITOFFSETISLEAPYEAR, BITSIZEISLEAPYEAR) ? true : false));
	return Day;
}

// Description: returns the day of the year represented by this date (1-365, 366 if leap year)

Int32 CDate::GetDayOfYear() const
{
	REPASDATE(*this);
	Int32 Month = GETCOMPONENT(m_Date, BITOFFSETMONTH, BITSIZEMONTH); // 1 - 12
	Int32 DayOfYear = s_YearDayFromMonth[Month]
		+ GETCOMPONENT(m_Date, BITOFFSETDAY, BITSIZEDAY)
		+ (GETCOMPONENT(m_Date, BITOFFSETISLEAPYEAR, BITSIZEISLEAPYEAR) & (Month > 2)) - 1;
	assert(DayOfYear >= 1 && DayOfYear <= 365 + GETCOMPONENT(m_Date, BITOFFSETISLEAPYEAR, BITSIZEISLEAPYEAR));
	return DayOfYear;
}

// Description: returns the week of the year reprsented by this date (1-52)

Int32 CDate::GetWeekOfYear() const
{
	REPASDATE(*this);
	Int32 WeekOfYear = GETCOMPONENT(m_Date, BITOFFSETWEEKOFYEAR, BITSIZEWEEKOFYEAR);
	assert(WeekOfYear >= 1 && WeekOfYear <= 53);
	return WeekOfYear;
}

// Description: Returns the year of for the current week of the year. This
//	may be different to GetYear() for certain cross-over days.
//	See CDate class description for more details

Int32 CDate::GetYearForWeekOfYear() const
{
	REPASDATE(*this);
	Int32 Year = GETCOMPONENT(m_Date, BITOFFSETYEAR, BITSIZEYEAR) + MINIMUMYEAR;
	Int32 YearOffset = GETCOMPONENT(m_Date, BITOFFSETWEEKYEARDIF, BITSIZEWEEKYEARDIF) - 1;
	assert(YearOffset >= -1 && YearOffset <= 1);
	return Year + YearOffset;
}

// Description: Returns the weekday of the week represented by this date (1-7) => (Monday-Sunday)

Int32 CDate::GetDayOfWeek() const
{
	REPASDATE(*this);
	Int32 DayOfWeek = GETCOMPONENT(m_Date, BITOFFSETDAYOFWEEK, BITSIZEDAYOFWEEK);
	assert(DayOfWeek >= 1 && DayOfWeek <= 7);
	return DayOfWeek;
}


// Description: convert to tstring (overrides CBasicTypeBase::ToTString)

std::string replace(std::string& a_string, const std::string& a_from, std::string& a_to)
{
	std::string result = a_string;
	std::size_t pos = a_string.find(a_from);

	if (pos != std::string::npos)
	{				
		result.replace(pos, a_from.size(), a_to);
	}

	return result;
}

std::string CDate::ToString() const
{
	// Use ISO YYYY-MM-DD format
	char DateBuf[12];
	sprintf(DateBuf, "%04i-%02i-%02i", int(GetYear()), int(GetMonth()), int(GetDay()));
	return std::string(DateBuf);
}

std::string CDate::ToStringWithFormat(const std::string& a_format) const
{
	assert(a_format.size() > 0);
	std::string result = a_format;

	regex re("[d]+|[m]+|[y]+");
	sregex_token_iterator reg_end;
	sregex_token_iterator it(a_format.begin(), 
							 a_format.end(), 
							 re, 
							 0);

	if (it == reg_end)
	{
		return std::string("");
	}

	for (; it != reg_end; ++it)
	{
		std::stringstream ss;

		if (it->str() == "dd")
		{
			ss << std::setfill('0') << std::setw(2) << this->GetDay();
            std::string from = ss.str();
            result = replace(result, "dd", from);
		}
		else if (it->str() == "mm")
		{
			ss << std::setfill('0') << std::setw(2) << this->GetMonth();
            std::string from = ss.str();
            result = replace(result, "mm", from);
		}
		else if (it->str() == "yyyy")
		{
            std::string from = std::to_string(this->GetYear());
            result = replace(result, "yyyy", from);
		}
	}


	return result;
}

// Description: Convert from string (ISO 8601 format YYYY-MM-DD)
bool CDate::FromString(const std::string & dateString)
{
	int Year = 0, Month = 0, Day = 0;
	int result = sscanf(dateString.c_str(), "%4i-%2i-%2i", &Year, &Month, &Day);

	if (result == EOF)
	{
		return false;
	}

	// Return false if not valid date format
	if ((Year == 0) | (Month == 0) | (Day == 0))  
	{
		return false;
	}

	*this = CDate(Year, Month, Day);

	return true;
}

#include <locale>
std::string CDate::toLower(const std::string& s)
{
    std::string result;

    std::locale loc;
    for (unsigned int i = 0; i < s.length(); ++i)
    {
        result += std::tolower(s.at(i), loc);
    }
    
    return result;
}

Int32 extract(const std::string& a_string, 
			  const std::string& a_format, 
			  const std::string& a_substring, 
			  int a_size)
{
	Int32 result = 0;
	std::size_t pos = a_format.find(a_substring);

	if (pos != string::npos)
	{
		result = std::atoi(a_string.substr(pos, a_size).c_str());	
	}

	return result;
}

bool CDate::FromStringWithFormat(const std::string& dateString,
							     const std::string& dateFormat)
{
	int dateSize = dateString.size();
	int formatSize = dateFormat.size();

	if (dateSize != formatSize)
	{
		return false;
	}

	/** checks if the commands are valid **/
	regex re("[d]+|[m]+|[y]+");
	sregex_token_iterator reg_end;
	sregex_token_iterator it(dateFormat.begin(), 
							 dateFormat.end(), 
							 re, 
							 0);
	
	if (it == reg_end)
	{
		return false;
	}

	Int32 day = extract(dateString, dateFormat, "dd", 2);
	day = day <= 0 ? 1 : day;
	Int32 month = extract(dateString, dateFormat, "mm", 2);
	Int32 year = extract(dateString, dateFormat, "yyyy", 4);

	*this = CDate(year, month, day);

	return true;
}

// Description: Return Julian day number

Int32 CDate::GetJulianDay() const
{
	REPASJD(*this);
	return m_Date;
}

// Description: Convert internal representation to Julian day number

void CDate::InternalToJD() const
{
	// Should only call this if currently in date representation mode
	assert(m_Date < 0);
	Int32 Year = GETCOMPONENT(m_Date, BITOFFSETYEAR, BITSIZEYEAR) + MINIMUMYEAR;
	Int32 Month = GETCOMPONENT(m_Date, BITOFFSETMONTH, BITSIZEMONTH);
	Int32 Day = GETCOMPONENT(m_Date, BITOFFSETDAY, BITSIZEDAY);
	m_Date = CDateCalc::CalcJulianPeriod(Year, Month, Day);
}

// Description: Convert internal representation to date parts

void CDate::InternalToDate() const
{
	// Should only call this if currently in days representation mode
	assert(m_Date >= 0);

	// Convert to date parts
	CDateCalc::DateS ConvDate;
	CDateCalc::CalculateDate(m_Date, ConvDate);

	// Copy calculated values
	Int32 DateRep =
		  ((ConvDate.m_Year - MINIMUMYEAR) << BITOFFSETYEAR)
		+ ((ConvDate.m_WeekOfYear) << BITOFFSETWEEKOFYEAR)
		+ ((ConvDate.m_Day) << BITOFFSETDAY)
		+ ((ConvDate.m_DayOfWeek) << BITOFFSETDAYOFWEEK)
		+ ((ConvDate.m_Month) << BITOFFSETMONTH)
		+ ((ConvDate.m_YearForWeekOfYear - ConvDate.m_Year + 1) << BITOFFSETWEEKYEARDIF)
		+ ((ConvDate.m_IsLeapYear) << BITOFFSETISLEAPYEAR)
		+ (1 << 31);

	m_Date = DateRep;
}

//! TODO: Rectory this
const std::string CDate::convertDateFormat(const std::string& a_stringDate,
										   const std::string& a_inputFormat,
										   const std::string& a_outputFormat)
{
	int dateSize = a_stringDate.size();
	int intputFormatSize = a_inputFormat.size();

	if (dateSize != intputFormatSize)
	{
		return "error!!!";
	}

	/** checks if the commands are valid **/
	regex re("[d]+|[m]+|[y]+");
	sregex_token_iterator reg_end;
	sregex_token_iterator it(a_inputFormat.begin(),
							 a_inputFormat.end(),
							 re,
							 0);

	if (it == reg_end)
	{
		return "error!!!";
	}

	Int32 day = extract(a_stringDate, a_inputFormat, "dd", 2);
	Int32 month = extract(a_stringDate, a_inputFormat, "mm", 2);
	Int32 year = extract(a_stringDate, a_inputFormat, "yyyy", 4);


	regex rex("[d]+|[m]+|[y]+");
	sregex_token_iterator reg_endx;
	sregex_token_iterator itx(a_outputFormat.begin(),
		a_outputFormat.end(),
		rex,
		0);

	if (itx == reg_endx)
	{
		return std::string("");
	}

	std::string result(a_outputFormat);

	for (; itx != reg_endx; ++itx)
	{
		std::stringstream ss;

		if (itx->str() == "dd")
		{
			ss << std::setfill('0') << std::setw(2) << day;
            std::string from(ss.str());
            result = replace(result, "dd", from);
		}
		else if (itx->str() == "mm")
		{
			ss << std::setfill('0') << std::setw(2) << month;
            std::string from(ss.str());
            result = replace(result, "mm", from);
		}
		else if (itx->str() == "yyyy")
		{
            std::string yearStr = std::to_string(year);
            result = replace(result, "yyyy", yearStr);
		}
	}

	return result;
}
