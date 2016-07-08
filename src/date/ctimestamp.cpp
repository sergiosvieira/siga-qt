
#include <assert.h>
#include <time.h>
#include "../../include/date/ctimestamp.h"

#define MILLISECONDSPERDAY (86400*1000)

CTimestamp::CTimestamp(Int64 extendedJD)
: CDate(Int32(extendedJD / MILLISECONDSPERDAY)), CTime(Int32(extendedJD % MILLISECONDSPERDAY))
{
}

CTimestamp::CTimestamp(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second, Int32 millisecond)
: CDate(year, month, day), CTime(hour, minute, second, millisecond)
{
}

CTimestamp::CTimestamp(Int32 year, Int32 yearDay, Int32 hour, Int32 minute, Int32 second, Int32 millisecond)
: CDate(year, yearDay), CTime(hour, minute, second, millisecond)
{
}

CTimestamp::CTimestamp(const CDate & date)
: CDate(date), CTime()
{
}

CTimestamp::CTimestamp(const CDate & date, const CTime & time)
: CDate(date), CTime(time)
{
}

// Description: Test if dates equal

bool CTimestamp::operator==(const CTimestamp & compare) const {
	return CDate::operator ==(compare) && CTime::operator ==(compare);
}

// Description: Test if one date less than

bool CTimestamp::operator<(const CTimestamp & compare) const {
	return
		CDate::operator <(compare)
			? true
			: CTime::operator <(compare);
}

// Description: Add milli-seconds to timestamp and return new timestamp
// Arguments:
//	timestampOffset - number of milli-seconds to add to timestamp (can be negative)

CTimestamp CTimestamp::operator+(Int64 timestampOffset) const {
	return CTimestamp(GetExtendedJulianDay() + timestampOffset);
}

// Description: Subraction operators
// Arguments:
//	timestampOffset - Number of milli-seconds to subtract from timestamp (can be negative)
//	otherTimestamp - Date to subtract. Returns number of milli-seconds between timestamps

CTimestamp CTimestamp::operator-(Int64 timestampOffset) const {
	return CTimestamp(GetExtendedJulianDay() - timestampOffset);
}

Int64 CTimestamp::operator-( const CTimestamp & otherTimestamp) const {
	return GetExtendedJulianDay() - otherTimestamp.GetExtendedJulianDay();
}

// Description: Add given number of milli-seconds to current timestamp
// Arguments:
//	timestampOffset - Number of milli-seconds to add to current timestamp (can be negative)

CTimestamp& CTimestamp::operator+=(Int64 timestampOffset) {
	*this = *this + timestampOffset;
	return *this;
}

// Description: Subtract given number of milli-seconds from current timestamp
// Arguments:
//	timestampOffset - Number of milli-seconds to subtract from timestamp (can be negative)

CTimestamp& CTimestamp::operator-=(Int64 timestampOffset) {
	*this = *this - timestampOffset;
	return *this;
}

// Description: Return Julian day number * MILLISECONDSPERDAY + time

Int64 CTimestamp::GetExtendedJulianDay() const {
	return Int64(GetJulianDay()) * MILLISECONDSPERDAY + GetMilliSecondsPastMidnight();
}


