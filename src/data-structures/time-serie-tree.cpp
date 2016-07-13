/****************************************************************************
 Copyright (c) 2016 Funceme
 Author: Sérgio Vieira - sergiosvieira@gmail.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "../../include/data-structures/time-serie-tree.h"

/** SIGA **/
#include "../../include/date/cdatecalc.h"

#include <tuple>
#include <algorithm>


using namespace std::placeholders;
using namespace SIGA::DS;

/** Public Methods **/
TimeSerieTree::TimeSerieTree()
{
}

TimeSerieTree::TimeSerieTree(int year,
                             PeriodType type): m_type(type)
{
    createTreeNodes(year, type);
}

TimeSerieTree::~TimeSerieTree()
{
}

void TimeSerieTree::createTreeNodes(int year,
                                    PeriodType type)
{
    bool isLeapYear = CDateCalc::IsLeapYear(year);
    TreeNodeIterator yearIt = std::find_if(m_tree.begin(),
                                           m_tree.end(),
                                           find_label(year));

    if (yearIt == m_tree.end())
    {
		++m_yearsCounter;
        yearIt = m_tree.insert(m_tree.begin(), TreeNode(year));
        for (int month = 1; month <= 12; ++month)
        {
            TreeNodeIterator monthIt = m_tree.append_child(yearIt, TreeNode(month));
            for (int day = 1; day <= CDateCalc::DaysInMonth(month, isLeapYear); ++day)
            {
                m_tree.append_child(monthIt, TreeNode(day));
            }
        }
        m_rows += CDateCalc::IsLeapYear(year) ? 366 : 365;
	}
}

bool TimeSerieTree::setDateValue(const CDate& date,
                                 const int& id,
                                 const float& value)
{
    insertID(id);
    // day, month and year nodes
    DayMonthYearNodes nodes = nodesFromDate(date);
    DateIDValueParameters parameters = make_tuple(date, id, value);
    switch (m_type)
    {
        case PeriodType::YEARLY_TYPE:
            return insertYearlyValue(nodes, parameters);
        case PeriodType::MONTHLY_TYPE:
            return insertMonthlyValue(nodes, parameters);
        case PeriodType::DAILY_TYPE:
            return insertDailyValue(nodes, parameters);
    }
    return false;
}


void TimeSerieTree::clearStations()
{
	m_stations.clear();
}

DayMonthYearValue TimeSerieTree::dateValues(const CDate& date,
                                            const int& id)
{
    DayMonthYearValue result;
    DayMonthYearNodes dateTuple = nodesFromDate(date);
	float dayValue = -999.f;
	float monthValue = -999.f;
	float yearValue = -999.f;
	TreeNode* dayNode = std::get<0>(dateTuple);
    TreeNode* monthNode = std::get<1>(dateTuple);
    TreeNode* yearNode = std::get<2>(dateTuple);
    int index = stationIndex(id);
	if (dayNode != nullptr)
	{
        dayValue = dayNode->value(0, index);
	}
	if (monthNode != nullptr)
	{
        monthValue = monthNode->value(0, index);
	}
    if (yearNode != nullptr)
	{
        yearValue = yearNode->value(0, index);
	}
	result = std::make_tuple(dayValue, monthValue, yearValue);
    return result;
}

float TimeSerieTree::dayValue(const CDate &date,
                              const int &id)
{
    DayMonthYearNodes dateTuple = nodesFromDate(date);
    TreeNode* dayNode = std::get<0>(dateTuple);
    int index = stationIndex(id);
    return dayNode->value(0, index);
}

float TimeSerieTree::monthValue(const CDate &date,
                                const int &id)
{
    DayMonthYearNodes dateTuple = nodesFromDate(date);
    TreeNode* monthNode = std::get<1>(dateTuple);
    int index = stationIndex(id);
    return monthNode->value(0, index);
}

float TimeSerieTree::yearValue(const CDate &date,
                               const int &id)
{
    DayMonthYearNodes dateTuple = nodesFromDate(date);
    TreeNode* yearNode = std::get<2>(dateTuple);
    int index = stationIndex(id);
    return yearNode->value(0, index);
}

void TimeSerieTree::sortValues()
{
	tree<TreeNode>::sibling_iterator siblingBegin = m_tree.begin();
	tree<TreeNode>::sibling_iterator siblingEnd = m_tree.end();
	m_tree.sort(siblingBegin, siblingEnd, false);	
}

int TimeSerieTree::depth(TreeNodeIterator& a_nodeIterator) const
{
	return m_tree.depth(a_nodeIterator);
}

int TimeSerieTree::stationsLength() const
{
	return m_stations.size();
}

int TimeSerieTree::rowsLength() const
{
	return m_rows;
}

TimeSerieTree::VectorOfString TimeSerieTree::stationLabels() const
{
	std::vector<std::string> result;
	for (const int& stationID: m_stations)
	{
		result.push_back(std::to_string(stationID));
	}
	return result;
}

int TimeSerieTree::stationID(int a_index) const
{
	assert(a_index < m_stations.size());
	return m_stations.at(a_index);
}

int TimeSerieTree::numberOfYears() const
{
	return m_yearsCounter;
}

PeriodType TimeSerieTree::periodType() const
{
	return m_type;
}

int TimeSerieTree::size() const
{
	return m_tree.size();
}

/** Private Methods **/
DayMonthYearNodes TimeSerieTree::nodesFromDate(const CDate& a_date)
{
    DayMonthYearNodes result;
	int year = a_date.GetYear();
	int month = a_date.GetMonth();
	int day = a_date.GetDay();
	TreeNode* yearNode = nullptr;
	TreeNode* monthNode = nullptr;
	TreeNode* dayNode = nullptr;
	TreeNodeIterator yearIt = std::find_if(m_tree.begin(), m_tree.end(), find_label(year));
	if (yearIt != m_tree.end())
	{
		yearNode = &(*yearIt);
		TreeNodeIterator monthIt = std::find_if(yearIt.begin(), yearIt.end(), find_label(month));
		if (monthIt != yearIt.end())
		{
			monthNode = &(*monthIt);
			TreeNodeIterator dayIt = std::find_if(monthIt.begin(), monthIt.end(), find_label(day));			
			if (dayIt != monthIt.end())
			{
				dayNode = &(*dayIt);
			}
		}
    }
    if (!dayNode || !monthNode || !yearNode)
    {
        throw std::invalid_argument("Invalid date!!");
    }
	result = std::make_tuple(dayNode, monthNode, yearNode);
    return result;
}

bool TimeSerieTree::insertYearlyValue(DayMonthYearNodes &nodes,
                                      DateIDValueParameters &parameters)
{
    TreeNode* yearNode = get<2>(nodes);
    CDate date = get<0>(parameters);
    int id = get<1>(parameters);
    float value = get<2>(parameters);
    int index = stationIndex(id);
    yearNode->setValue(0, index, value);
    TreeNodeIterator yearIt = find_if(m_tree.begin(), m_tree.end(), find_label(date.GetYear()));
    if (yearIt == m_tree.end()) return false;
    TreeNodeType::sibling_iterator monthIt = yearIt.begin();
    float days = CDateCalc::IsLeapYear(date.GetYear()) ? 366.f : 365.f;
    while (monthIt != yearIt.end())
    {
        TreeNode* monthNode = &(*monthIt);
        if (monthNode)
        {
            monthNode->setValue(0, index, value / 12.f);
        }
        TreeNodeIterator dayIt = monthIt.begin();
        float finalValue = value / days;
        while (dayIt != monthIt.end())
        {
            TreeNode* dayNode = &(*dayIt);
            if (dayNode)
            {
                dayNode->setValue(0, index, finalValue);
            }
            dayIt++;
        }
        monthIt++;
    }
    return true;
}

bool TimeSerieTree::insertMonthlyValue(DayMonthYearNodes &nodes,
                                       DateIDValueParameters &parameters)
{
    TreeNode* yearNode = get<2>(nodes);
    TreeNode* monthNode = get<1>(nodes);
    CDate date = get<0>(parameters);
    bool isLeapYear = CDateCalc::IsLeapYear(date.GetYear());
    int id = get<1>(parameters);
    float value = get<2>(parameters);
    int index = stationIndex(id);
    yearNode->sum(0, index, value);
    TreeNodeIterator yearIt = find_if(m_tree.begin(), m_tree.end(), find_label(date.GetYear()));
    if (yearIt == m_tree.end()) return false;
    TreeNodeType::sibling_iterator monthIt = find_if(yearIt.begin(), yearIt.end(), find_label(date.GetMonth()));
    float daysInMonth = CDateCalc::DaysInMonth(monthNode->label(), isLeapYear);
    if (monthNode)
    {
        monthNode->setValue(0, index, value);
    }
    TreeNodeIterator dayIt = monthIt.begin();
    float finalValue = value / daysInMonth;
    while (dayIt != monthIt.end())
    {
        TreeNode* dayNode = &(*dayIt);
        if (dayNode)
        {
            dayNode->setValue(0, index, finalValue);
        }
        dayIt++;
    }
    return true;
}

bool TimeSerieTree::insertDailyValue(DayMonthYearNodes &nodes,
                                     DateIDValueParameters &parameters)
{
    TreeNode* yearNode = get<2>(nodes);
    TreeNode* monthNode = get<1>(nodes);
    TreeNode* dayNode = get<0>(nodes);
    int id = get<1>(parameters);
    float value = get<2>(parameters);
    int index = stationIndex(id);
    yearNode->sum(0, index, value);
    monthNode->sum(0, index, value);
    dayNode->setValue(0, index, value);
    return true;
}

int TimeSerieTree::stationIndex(int id)
{
    VectorOfInt::iterator it = find(m_stations.begin(),
                                    m_stations.end(),
                                    id);
    return it == m_stations.end() ? -1 : it - m_stations.begin();
}

void TimeSerieTree::insertID(const int& id)
{
    if (std::find(m_stations.begin(),
                  m_stations.end(),
                  id) == m_stations.end())
    {
        m_stations.push_back(id);
    }
}
