
#ifndef Time_H
#define Time_H

#include "cdatetimedefs.h"

//---------------------------------------------------------------------------
//
// Description:
// CTime is a class for representing the time of day as a 24 hour
// clock time with millisecond precision.
//
// Author: Rob Mueller
// Date: 25-Jul-2001
//
// Multithread Safe: No (with conditions, see below)
// Mutable Variables: Yes
//
// Copyright:
//	 Copyright (c) 2001 by Robert Mueller.
//
//	 Permission to  use,
//	 copy, modify,  distribute  and  sell  this  software  and  its
//	 documentation for any purpose is hereby granted  without  fee,
//	 provided that the above copyright notice appear in all  copies
//	 and that both that copyright notice and this permission notice
//	 appear in supporting documentation. I make no  representations
//	 about the suitability of this software for any purpose. It  is
//	 provided "as is" without express or implied warranty.
//
// Remarks:
// CTime consists purely of time information. No date
//	information is associated with it. It can be broken down into:
//	* Hour
//	* Minute
//	* Second
//	* Milli-second
//
//  CTime objects can be constructed by specifing either:
//	* hour (0-23), minute (0-59), second (0-59), millisecond (0-999)
//  * total milliseconds past midnight (0-86399999)
//
//	Hours, minutes, seconds and total seconds are not validated, but are
//	asserted in debug mode. The default constructor creates time 00:00:00
//	(eg midnight)
//
//  The current system time can also be obtained with the static method
//	CTime::GetSystemTime()
//
//	Any overflows/underflows wrap the time around
//	eg 00:00:00 - 1 second = 23:59:59
//
//	Internally, time is stored in a Int32 as number of milli-seconds
//	past midnight
//
//---------------------------------------------------------------------------
//
class CTime
{
public:
	// Group=Constructors

	// Description: Constructors.
	// Arguments:
	//  copy - CDate object to create copy from
	//	jd - Julian day number
	//  hour - hour of the day (0-23)
	//	minute - minute of the hour (0-59)
	//	second - seconds of the minute (0-59)
	//	millisecond - milli-seconds of the second (0-999)
	inline CTime(const CTime & copy)
		: m_Time(copy.m_Time) {}
	inline CTime(Int32 millisecPastMidnight = 0)
		: m_Time(millisecPastMidnight) { assert(millisecPastMidnight >= 0); }
	CTime( Int32 hour, Int32 minute, Int32 second, Int32 millisecond = 0 );

	// Description: Returns a CTime instance that represents the current local system time.
	static CTime GetSystemTime();

	// Group=Destructor
	inline ~CTime() {}

	// Group=Public Operators

	// Description: assignment
	inline CTime& operator=(const CTime& assign)
		{ m_Time = assign.m_Time; return *this; }

	// Description: Test if times equal
	bool operator==(const CTime & compare) const;
	// Description: Test if one time less than
	bool operator<(const CTime & compare) const;

	// Description: Add mill-seconds to time and return new time
	// Arguments:
	//	timeOffset - number of milliseconds to add to time (can be negative)
	CTime operator+(Int32 timeOffset) const;

	// Description: Subraction operators
	// Arguments:
	//	timeOffset - Number of milli-seconds to subtract from time (can be negative)
	//	otherTime - Time to subtract. Returns number of mill-seconds between times
	CTime operator-(Int32 timeOffset) const;
	Int32 operator-( const CTime & otherTime) const;

	// Description: Add given number of milli-seconds to current time
	// Arguments:
	//	timeOffset - Number of milli-seconds to add to current time (can be negative)
	CTime& operator+=(Int32 timeOffset);		
	// Description: Subtract given number of milli-seconds from current time
	// Arguments:
	//	timeOffset - Number of milli-seconds to subtract from time (can be negative)
	CTime& operator-=(Int32 timeOffset);

	// Group=Public Member Functions

	// Description: returns hour of the day (0-23)
	Int32 GetHour() const;
	// Description: returns minute of the hour (0-59)
	Int32 GetMinute() const;
	// Description: returns seconds of the minute (0-59)
	Int32 GetSecond() const;
	// Description: returns mill-seconds of the second (0-999)
	Int32 GetMilliSecond() const;

	// Description: Return milli-seconds past midnight
	Int32 GetMilliSecondsPastMidnight() const;

	// Description: Convert internal representation to milli-second number
	void InternalToMSPM() const;
	// Description: Convert internal representation to time parts
	void InternalToTime() const;

	private:
	// Group=Private Member Data

	// Description: The actual time, stored as either milli-seconds
	//	past midnight number or as actual date components depending
	//	on highest bit
	//
	//		Item					Value		Bits		Bit
	//								Range		required	offset 
	//		Storage type			0-1			1			31 
	//		N/A	(always 0)									27-30
	//		Hour					0-23		5			22-26 
	//		Minute					0-59		6			16-21 
	//		Second					0-59		6			10-15 
	//		Milli-second			0-999		10			0-9
	mutable Int32 m_Time;
};

#endif

