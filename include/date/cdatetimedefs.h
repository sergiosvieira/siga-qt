#ifndef DateTimeDefs_H
#define DateTimeDefs_H

//---------------------------------------------------------------------------
//
// Description:
//	This file holds typedefs and constants for dates and times. The day
//	numbers follow ISO 8601 convention. See
//	http://www.cl.cam.ac.uk/~mgk25/iso-time.html for more details
//
// Author: Rob Mueller
// Date: 13-Aug-2001
//
//---------------------------------------------------------------------------

typedef int Int32;
typedef unsigned int UInt32;
#if defined(__GNUC__)
typedef long long Int64;
#elif defined(_MSC_VER)
typedef __int64 Int64;
#else
#error "Don't know what a 64 bit int is sorry..."
#endif

// Description: Enumerates the days of the week. Monday = 1, ...
enum DayOfWeekEnum {
	strMonday = 1,
	strTuesday = 2,
	strWednesday = 3,
	strThursday = 4,
	strFriday = 5,
	strSaturday = 6,
	strSunday = 7
};

// Description: Enumerates the months of the year. January = 1, ...
enum MonthOfYearEnum {
	strJanuary = 1,
	strFebruary = 2,
	strMarch = 3,
	strApril = 4,
	strMay = 5,
	strJune = 6,
	strJuly = 7,
	strAugust = 8,
	strSeptember = 9,
	strOctober = 10,
	strNovember = 11,
	strDecember = 12
};

#endif

