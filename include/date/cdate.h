#ifndef Date_H 
#define Date_H

#include "cdatetimedefs.h"
#include <string>
#include <cassert>
//---------------------------------------------------------------------------
//
// Description:
// CDate is a class for representing standard Gregorian calendar dates.
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
//
// CDate consists purely of date information. No time 
//	information is associated with it. It can be broken down into:
//	* Year
//	* Month
//	* Day
//	* Day of Year
//	* Week of Year
//	* Year of "week of year"
//	* Day of Week
//
// See below for details on 'week of year' curiosities
//
// Trying to create an invalid date (eg. 29th Feb in a non-leap year) is
//	not validated, but is asserted in debug mode. The default constructor
//	creates the date with julian day 0. You can't convert this to a
//  year/month/day because it is out of range. The current system date
//	can be obtained with the static method CDate::GetSystemDate(). CDate
//	uses the pivot year set in the CDateCalc class to convert 2 digit
//	years to 4 digit years. See CDateCalc for more information.
//
// Where possible, CDate uses the International Standard ISO 8601.
//	This is mostly in the definition of the week of year component
//	of a date. See http://www.cl.cam.ac.uk/~mgk25/iso-time.html
//	for some useful docs.
//
// CDate differences can be calculated and a signed Int32 value is
//	used to represent the number of days difference between any two
//	dates.
//
// Implementation notes:
//
// Internally, the date is represented in one of two forms:
//	* A Julian day number
//	* A series of date components: year, day of year, etc
//
// These are stored in a single 32 bit integer.
//	The most significant bit determines if the structure is currently in
//	'Julain day' representation mode or 'date parts' representation mode.
//
// The internal representation can be changed by calling the
//	InternalToDate() or InternalToJD() methods. These methods are
//	const, but do modify the internal values of the class because the
//	m_Date member variable is mutable.
//
// In general, when calling a routine that wants a 'Julian day' value
//	(eg GetJulianDay(), operator+(), etc), the internal representation
//	is first converted to 'Julian day' and the operation performed.
//	Similarily, calling a routine that wants a 'date part' (eg GetYear(),
//	GetMonth(), etc), the internal representation is first converted
//	to 'date parts' and then the appropriate value returned. This seems
//	to give good performance, because you tend to use methods that
//	require a particular representation near each other.
//
// Week of year oddities:
//	Week 01 of a year is per definition the first week that has the Thursday
//	in this year, which is equivalent to the week that contains the fourth
//	day of January. In other words, the first week of a new year is the week
//	that has the majority of its days in the new year
//
//	The week of the year is odd in that week 01 might also contain days from
//	the previous year and the week before week 01 of a year is the last week
//	(52 or 53) of the previous year even if it contains days from the new year.
//	A week starts with Monday (day 1) and ends with Sunday (day 7). For example,
//	the first week of the year 1997 lasts from 1996-12-30 to 1997-01-05
//
// Multithread safety:
//
// Because even const CDate objects can have their internal
//	representation changed, a CDate object is not-thread safe, even
//	as a const read only object! If you know what you're doing, you
//	can ensure you call InternalToDate() or InternalToJD() methods
//	and then only access methods that use that internal representation
//	in a multi-threaded environment
//
//---------------------------------------------------------------------------
//
class CDate
{
public:
	// Group=Constructors

	// Description: Constructors.
	// Arguments:
	//  copy - CDate object to create copy from
	//	jd - Julian day number
	//	year - year date represents. Years (00-99) converted to 4 digit year.
	//	month - month of year date represents (1..12)
	//	day - day of month date represents (1..28/29/30/31)
	//	yearDay - day of year date represents (1-365/366 if leap year) 		
	inline CDate(const CDate & copy)
		: m_Date(copy.m_Date) {}
	inline CDate(Int32 julianDay = 0)
		: m_Date(julianDay) { assert(julianDay >= 0); }
	CDate(Int32 year, Int32 month, Int32 day);
	CDate(Int32 year, Int32 yearDay);
	CDate(const std::string& a_dateString, const std::string& a_dateFormatString);
	// Description: Returns a CDate instance that represents the current local system date.
	static CDate GetSystemDate();

	// Group=Destructor
	inline ~CDate() {}

	// Group=Public Operators

	// Description: assignment
	inline CDate& operator=(const CDate& assign)
		{ m_Date = assign.m_Date; return *this; }

	// Description: Test if dates equal
	bool operator==(const CDate & compare) const;
	// Description: Test if one date less than
	bool operator<(const CDate & compare) const;

	// Description: Add days to date and return new date
	// Arguments:
	//	dateOffset - number of days to add to date (can be negative)
	CDate operator+(Int32 dateOffset) const;

	// Description: Subraction operators
	// Arguments:
	//	dateOffset - Number of days to subtract from date (can be negative)
	//	otherDate - Date to subtract. Returns number of days between dates
	CDate operator-(Int32 dateOffset) const;
	Int32 operator-( const CDate & otherDate) const;

	// Description: Add given number of days to current date
	// Arguments:
	//	dateOffset - Number of days to add to current date (can be negative)
	CDate& operator+=(Int32 dateOffset);		
	// Description: Subtract given number of days from current date
	// Arguments:
	//	dateOffset - Number of days to subtract from date (can be negative)
	CDate& operator-=(Int32 dateOffset);

	bool operator!=(const CDate& otherDate) const;

	// Group=Public Member Functions

	// Description: Returns the year represented by this date (1500-2500)
	Int32 GetYear() const;
	// Description: Returns the quarter represented by this date (1-4)
	Int32 GetQuarter() const;
	// Description: Returns the month in the year represented by this date (1-12)
	Int32 GetMonth() const;
	// Description: Returns the day in the month represented by this date (1-31)
	Int32 GetDay() const;
	// Description: Returns the day of the year represented by this date (1-365, 366 if leap year)
	Int32 GetDayOfYear() const;

	// Description: Returns the week of the year reprsented by this date (1-53).
	//	See CDate class description for more details
	Int32 GetWeekOfYear() const;
	// Description: Returns the year of for the current week of the year. This
	//	may be different to GetYear() for certain cross-over days.
	//	See CDate class description for more details
	Int32 GetYearForWeekOfYear() const;
	// Description: Returns the weekday of the week represented by this date
	//	(1-7) => (Monday-Sunday)
	Int32 GetDayOfWeek() const;

	// Description: Return Julian day number
	Int32 GetJulianDay() const;

	// Description: 
    std::string ToString() const;
    std::string ToStringWithFormat(const std::string& a_format) const;
	bool FromString(const std::string & dateString);
	bool FromStringWithFormat(const std::string& dateString,
							  const std::string& dateFormat);

	// Description: Convert internal representation to Julian day number
	void InternalToJD() const;
	// Description: Convert internal representation to date parts
	void InternalToDate() const;
	static const std::string convertDateFormat(const std::string& a_stringDate,
											   const std::string& a_inputFormat,
											   const std::string& a_outputFormat);
	private:
	std::string toLower(const std::string& s);
	// Group=Private Member Data

	// Description: The actual date, stored as either Julian day number or
	//	as actual date components depending on highest bit
	//
	//		Item					Value		Bits		Bit
	//								Range		required	offset 
	//		Storage type			0-1			1			31 
	//		Is leap year?			0-1			1			30 
	//		Week year difference	-1 - 1		2			28-29 
	//		Month					1-12		4			24-27 
	//		Day of week				1-7			3			21-23 
	//		Day						1-31		5			16-20 
	//		Week of year			1-53		6			10-15 
	//		Year					1500-2500	10			0-9
	mutable Int32 m_Date;
};

#endif 
