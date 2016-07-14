#include "../../include/converter/converter-options.h"

using namespace SIGA;

Range ConverterOptions::rowRange() const
{
    return m_rowRange;
}

void ConverterOptions::setRowRange(const Range &rowRange)
{
    m_rowRange = rowRange;
}

Range ConverterOptions::colRange() const
{
    return m_colRange;
}

void ConverterOptions::setColRange(const Range &colRange)
{
    m_colRange = colRange;
}

Layout ConverterOptions::layout() const
{
    return m_layout;
}

void ConverterOptions::setLayout(const Layout &layout)
{
    m_layout = layout;
}

DateIdentifier ConverterOptions::dateIndex() const
{
    return m_date;
}

void ConverterOptions::setSingleDate(int dateIndex)
{
    m_date = make_pair(DateFieldCount::SINGLE_FIELD, vector<int>{dateIndex});
}

void ConverterOptions::setTribleDate(int dayIndex,
                                     int monthIndex,
                                     int yearIndex)
{
    m_date = make_pair(DateFieldCount::THREE_FIELDS, vector<int>{dayIndex, monthIndex, yearIndex});
}

string ConverterOptions::dateFormat() const
{
    return m_dateFormat;
}

void ConverterOptions::setDateFormat(const string &dateFormat)
{
    m_dateFormat = dateFormat;
}

bool ConverterOptions::header() const
{
    return m_header;
}

void ConverterOptions::setHeader(bool header)
{
    m_header = header;
}

Station ConverterOptions::station() const
{
    return m_station;
}

void ConverterOptions::setStation(const Station &station)
{
    m_station = station;
}
