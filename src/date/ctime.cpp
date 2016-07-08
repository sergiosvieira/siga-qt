
#include <assert.h>
#include <stdlib.h>
#include "../../include/date/ctime.h"

#if defined(_MSC_VER)
#pragma warning(disable: 4127)
#endif

// Macro to ensure internal representation is as mill-seconds past midnight
#define REPASMSPM(obj) \
do { \
	if ((obj).m_Time <  0) \
		(obj).InternalToMSPM(); \
} while (0)

// Macro to ensure internal representation is as time components
#define REPASTIME(obj) \
do { \
	if ((obj).m_Time >= 0) \
		(obj).InternalToTime(); \
} while (0)

#define BITOFFSETMILLISECOND 0
#define BITSIZEMILLISECOND 10
#define BITOFFSETSECOND 10
#define BITSIZESECOND 6
#define BITOFFSETMINUTE 16
#define BITSIZEMINUTE 6
#define BITOFFSETHOUR 22
#define BITSIZEHOUR 5

#define MSPERDAY (24*60*60*1000)

// Macro to extract bitfield component at offset of length from v
#define GETCOMPONENT(v, offset, length) ( (v)>>(offset) & ((1<<(length))-1) )

CTime::CTime( Int32 hour, Int32 minute, Int32 second, Int32 millisecond )
{
	m_Time = millisecond + 1000*(second + 60*(minute + 60*hour));
}

CTime CTime::GetSystemTime()
{
	// TODO: Get this to work
	return 0;//CTime(1000*Int32(time(0) % 86400));
}

bool CTime::operator==(const CTime & compare) const
{
	// Ensure the internal representation of both objects is as milli-seconds
	REPASMSPM(*this); REPASMSPM(compare);
	// Simple day compare
	return m_Time == compare.m_Time;
}

bool CTime::operator<(const CTime & compare) const
{
	// Ensure the internal representation of both objects is as milli-seconds
	REPASMSPM(*this); REPASMSPM(compare);
	// Simple milli-second compare
	return m_Time < compare.m_Time;
}

CTime CTime::operator+( Int32 timeOffset) const
{
	CTime ThisTime(*this);
	REPASMSPM(ThisTime);
	ThisTime.m_Time = (ThisTime.m_Time + timeOffset + 2*MSPERDAY) % MSPERDAY;
	assert(ThisTime.m_Time >= 0);
	return ThisTime;
}

CTime CTime::operator-( Int32 timeOffset) const
{
	CTime ThisTime(*this);
	REPASMSPM(ThisTime);
	ThisTime.m_Time = (ThisTime.m_Time - timeOffset + 2*MSPERDAY) % MSPERDAY;
	assert(ThisTime.m_Time >= 0);
	return ThisTime;
}

Int32 CTime::operator-( const CTime& otherTime) const
{
	// Ensure the internal representation of both objects is as milli-seconds
	REPASMSPM(*this); REPASMSPM(otherTime);

	return (m_Time - otherTime.m_Time + 2*MSPERDAY) % MSPERDAY;
}

// Description: Self addition operator

CTime& CTime::operator+=( Int32 timeOffset)
{
	REPASMSPM(*this);
	m_Time = (m_Time + timeOffset + 2*MSPERDAY) % MSPERDAY;
	assert(m_Time >= 0);
	return *this;
}

// Description: Self subtraction operator

CTime& CTime::operator-=( Int32 timeOffset)
{
	REPASMSPM(*this);
	m_Time = (m_Time - timeOffset + 2*MSPERDAY) % MSPERDAY;
	assert(m_Time >= 0);
	return *this;
}

// Description: returns hour of the day (0-23)

Int32 CTime::GetHour() const
{
	REPASTIME(*this);
	Int32 Hour = GETCOMPONENT(m_Time, BITOFFSETHOUR, BITSIZEHOUR);
	assert(Hour >= 0 && Hour < 24);
	return Hour;
}

// Description: returns minute of the hour (0-59)

Int32 CTime::GetMinute() const
{
	REPASTIME(*this);
	Int32 Minute = GETCOMPONENT(m_Time, BITOFFSETMINUTE, BITSIZEMINUTE);
	assert(Minute >= 0 && Minute < 60);
	return Minute;
}

// Description: returns seconds of the minute (0-59)

Int32 CTime::GetSecond() const
{
	REPASTIME(*this);
	Int32 Second = GETCOMPONENT(m_Time, BITOFFSETSECOND, BITSIZESECOND);
	assert(Second >= 0 && Second < 60);
	return Second;
}

// Description: returns mill-seconds of the second (0-999)

Int32 CTime::GetMilliSecond() const
{
	REPASTIME(*this);
	Int32 MilliSecond = GETCOMPONENT(m_Time, BITOFFSETMILLISECOND, BITSIZEMILLISECOND);
	assert(MilliSecond >= 0 && MilliSecond < 1000);
	return MilliSecond;
}


/*
// Description: convert to tstring (overrides CBasicTypeBase::ToTString)

stl::string CTime::ToString() const
{
	// Use ISO YYYY-MM-DD format
	char TimeBuf[12];
	sprintf(TimeBuf, "%04i-%02i-%02i", int(GetYear()), int(GetMonth()), int(GetDay()));
	return stl::string(TimeBuf);
}

// Description: Convert from string (ISO 8601 format YYYY-MM-DD)

void CTime::FromString(const stl::string & timeString)
{
	int Year = 0, Month = 0, Day = 0;
	sscanf(timeString.c_str(), "%i-%i-%i", &Year, &Month, &Day);

	// Return false if not valid time format
	if ((Year == 0) | (Month == 0) | (Day == 0))  {
		return false;
	}

	*this = CTime(Year, Month, Day);

	return true;
}

*/

// Description: Return milli-seconds past midnight

Int32 CTime::GetMilliSecondsPastMidnight() const
{
	REPASMSPM(*this);
	return m_Time;
}


// Description: Convert internal representation to milli-seconds past midnight

void CTime::InternalToMSPM() const
{
	// Should only call this if currently in time representation mode
	assert(m_Time < 0);
	Int32 Hour = GETCOMPONENT(m_Time, BITOFFSETHOUR, BITSIZEHOUR);
	Int32 Minute = GETCOMPONENT(m_Time, BITOFFSETMINUTE, BITSIZEMINUTE);
	Int32 Second = GETCOMPONENT(m_Time, BITOFFSETSECOND, BITSIZESECOND);
	Int32 MilliSecond = GETCOMPONENT(m_Time, BITOFFSETMILLISECOND, BITSIZEMILLISECOND);
	m_Time = MilliSecond + 1000*(Second + 60*(Minute + 60*Hour));
}

// Description: Convert internal representation to time parts

void CTime::InternalToTime() const
{
	// Should only call this if currently in milli-seconds representation mode
	assert(m_Time >= 0);

	// Convert to time parts
	Int32 MilliSecond = m_Time % 1000; m_Time /= 1000;
	Int32 Second = m_Time % 60; m_Time /= 60;
	Int32 Minute = m_Time % 60; m_Time /= 60;
	Int32 Hour = m_Time;

	// Copy calculated values
	Int32 TimeRep =
		  ((MilliSecond) << BITOFFSETMILLISECOND)
		+ ((Second) << BITOFFSETSECOND)
		+ ((Minute) << BITOFFSETMINUTE)
		+ ((Hour) << BITOFFSETHOUR)
		+ (1 << 31);

	m_Time = TimeRep;
}
