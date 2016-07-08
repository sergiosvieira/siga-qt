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

TimeSerieTree::TimeSerieTree(int a_year,
                             PeriodType a_type)
{
    createTreeNodes(a_year, a_type);
}

TimeSerieTree::~TimeSerieTree()
{
	destroyValues();
}

void TimeSerieTree::createTreeNodes(int year,
                                    PeriodType type)
{
    m_type = type;
    TreeNodeIterator yearIt = std::find_if(m_tree.begin(),
                                            m_tree.end(),
                                            find_label(year));
	bool isYearNotFound = yearIt == m_tree.end();
	if (isYearNotFound == true)
	{
		++m_yearsCounter;
        TreeNodeIterator yearIt = m_tree.begin();
        yearIt = m_tree.insert(m_tree.begin(), TreeNode(year));
		HourFunction hourFunction = nullptr;
		DayFunction dayFunction = nullptr;
        switch((int)type & 0x1111)
		{
			case 0x1111: // HOUR
			{
                hourFunction = std::bind(&TimeSerieTree::appendHours,
                                         this,
                                         _1);
			} break;
		}
        dayFunction = std::bind(&TimeSerieTree::appendDays,
                                this,
                                _1,
                                _2,
                                _3);
        appendMonths(year, yearIt, dayFunction, hourFunction);
        m_rows += CDateCalc::IsLeapYear(year) ? 366 : 365;
	}
}

bool TimeSerieTree::insertValueOnStation(const CDate& a_date, 
										 const int& a_stationID, 
										 const float& a_value)
{
	bool result = true;
	// day, month, year
	std::tuple<TreeNode*, TreeNode*, TreeNode*> dateTuple = nodesFromDate(a_date);
	TreeNode* day = std::get<0>(dateTuple);
	TreeNode* month = std::get<1>(dateTuple);
	TreeNode* year = std::get<2>(dateTuple);
	if (year != nullptr)
	{
        std::vector<int>::iterator stationIt = std::find(m_stations.begin(),
                                                         m_stations.end(),
                                                         a_stationID);
		if (stationIt != m_stations.end())
		{
			int stationIndex = stationIt - m_stations.begin();
			updateNodeValue(year, a_value, stationIndex);
			updateNodeValue(month, a_value, stationIndex);
			if (day != nullptr
                && !day->isEmpty(0l, stationIndex))
			{
				// data duplicada, o valor foi sobrescrito
				return false;
			}
			if (m_type == PeriodType::MONTHLY_TYPE)
			{
				bool isLeapYear = CDateCalc::IsLeapYear(a_date.GetYear()) > 0;
				int daysInMonth = CDateCalc::DaysInMonth(a_date.GetMonth(), isLeapYear);
				float dayValue = a_value / (float)daysInMonth;
				CDate currentDate(a_date);
				for (int i = 0; i < daysInMonth; ++i)
				{
					std::tuple<TreeNode*, TreeNode*, TreeNode*> currentDateTuple = nodesFromDate(currentDate);
					TreeNode* currentDay = std::get<0>(currentDateTuple);
					updateNodeValue(currentDay, dayValue, stationIndex);
					currentDate += 1;
				}
			}
			else
			{
				updateNodeValue(day, a_value, stationIndex);
			}
		}
	}
	else
	{
		result = false;
	}
	return result;
}

void TimeSerieTree::insertStationID(const int& a_stationID)
{
    if (std::find(m_stations.begin(),
                  m_stations.end(),
                  a_stationID) == m_stations.end())
	{
		m_stations.push_back(a_stationID);
	}
}

void TimeSerieTree::clearStations()
{
	m_stations.clear();
}

std::tuple<float, float, float> TimeSerieTree::valueOnStation(const CDate& date,
                                                              const int& stationID)
{
	std::tuple<float, float, float> result;
    std::tuple<TreeNode*, TreeNode*, TreeNode*> dateTuple = nodesFromDate(date);
	float dayValue = -999.f;
	float monthValue = -999.f;
	float yearValue = -999.f;
	TreeNode* dayNode = std::get<0>(dateTuple);
	TreeNode* monthNode = std::get<0>(dateTuple);
	TreeNode* yearNode = std::get<0>(dateTuple);
	if (dayNode != nullptr)
	{
        dayValue = dayNode->value(0, stationID);
	}
	if (monthNode != nullptr)
	{
        monthValue = monthNode->value(0, stationID);
	}
	if (yearNode != nullptr)
	{
        yearValue = yearNode->value(0, stationID);
	}
	result = std::make_tuple(dayValue, monthValue, yearValue);
	return result;
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

std::vector<std::string> TimeSerieTree::stationLabels() const
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

int TimeSerieTree::yearsLenght() const 
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
void TimeSerieTree::appendMonths(int a_year,
								 TreeNodeIterator& a_yearIt, 
								 DayFunction a_dayFunction, 
								 HourFunction a_hourFunction)
{
	for (int monthInt = 1; monthInt <= 12; ++monthInt)
	{
		TreeNodeIterator dayIt = m_tree.append_child(a_yearIt, TreeNode(monthInt));
		if (a_dayFunction != nullptr)
		{
			bool isLeapYear = CDateCalc::IsLeapYear(a_year) > 0;
			int daysInMonth = CDateCalc::DaysInMonth(monthInt, isLeapYear);
			if (a_dayFunction != nullptr)
			{
				a_dayFunction(dayIt, daysInMonth, a_hourFunction);
			}
		}
	}
}

void TimeSerieTree::appendDays(TreeNodeIterator& a_monthIt, 
							   int a_daysInMonth,
							   HourFunction a_hourFunction)
{
	for (int dayInt = 1; dayInt <= a_daysInMonth; ++dayInt)
	{
        TreeNodeIterator dayIt = m_tree.append_child(a_monthIt,
                                                     TreeNode(dayInt));
		if (a_hourFunction != nullptr)
		{
			a_hourFunction(dayIt);
		}
	}
}

void TimeSerieTree::appendHours(TreeNodeIterator& a_dayIt)
{
	for (int hourInt = 0; hourInt < 24; ++hourInt)
	{
		m_tree.append_child(a_dayIt, TreeNode(hourInt));
	}
}

void TimeSerieTree::destroyValues()
{
	for (tree<TreeNode>::pre_order_iterator it = m_tree.begin();
		 it != m_tree.end();
		 ++it)
	{			
		TreeNode& node = *it;
        node.destroyValues();
	}
}

void TimeSerieTree::updateNodeValue(TreeNode* node,
                                    const float& value,
                                    const int& stationIndex)
{
    if (node != nullptr)
	{
        node->setValue(0, stationIndex, make_shared<float>(value));
	}
}

std::tuple<TreeNode*, TreeNode*, TreeNode*> TimeSerieTree::nodesFromDate(const CDate& a_date)
{
	std::tuple<TreeNode*, TreeNode*, TreeNode*> result;
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
	result = std::make_tuple(dayNode, monthNode, yearNode);
	return result;
}
