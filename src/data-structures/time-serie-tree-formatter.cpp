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

#include "SIGA/SigaConverter/TimeSerieTreeFormatter.h"

/** SIGA **/
#include "SIGA/string-utils.h"


/** Public Methods **/
std::vector<std::vector<std::string>> TimeSerieTreeFormatter::matrix(TimeSerieTree& a_tree,
																	 const InputStructure& a_inputOptions)
{
	std::vector<std::vector<std::string>> result;
	a_tree.sortValues();
	for (tree<TreeNode>::pre_order_iterator it = a_tree.begin();
		 it != a_tree.end();
		 ++it)
	{
		TreeNode& node = *it;
	}
	return result;
}

std::vector<std::vector<std::string>> TimeSerieTreeFormatter::serie(TimeSerieTree& a_tree,
																	const InputStructure& a_inputOptions,
																	std::function<bool(long, long)> a_progress)
{	
	std::vector<std::vector<std::string>> result;
	result.push_back(a_tree.stationLabels());
	a_tree.sortValues();
	int stopTreeDepth = treeDepthFromPeriodType(a_inputOptions.periodType);
	DateStructure dateStructure = {};
	long total = a_tree.size() * a_tree.stationsLength();
	long currentProgress = 0;
	for (tree<TreeNode>::pre_order_iterator it = a_tree.begin();
		 it != a_tree.end();
		 ++it)
	{
		TreeNode& node = *it;
		int currentDepth = a_tree.depth(it);
		dateFromTreeDepth(dateStructure, node, currentDepth);
		if (currentDepth == stopTreeDepth)
		{						
			CDate date(dateStructure.year, dateStructure.month, dateStructure.day);
			std::vector<std::string> rowVector;
			rowVector.push_back(date.ToStringWithFormat(a_inputOptions.dateFormat));
			for (int index = 0; index < a_tree.stationsLength(); ++index)
			{
				std::string valueString = "-999";
				float* value = node.m_matrix[0][index] != nullptr ? node.m_matrix[0][index] : nullptr;
				if (value != nullptr)
				{
					valueString = std::to_string(*value);
				}
				rowVector.push_back(valueString);
				++currentProgress;
				if (a_progress != nullptr)
				{
					bool continue_ = a_progress((double)currentProgress/(double)total * 100., total);
					if (continue_ != 1)
					{
						return result;
					}
				}
			}
			result.push_back(rowVector);
		}
	}
	return result;
}

/** Private Methods **/
void TimeSerieTreeFormatter::dateFromTreeDepth(DateStructure& a_date, 
											   const TreeNode& a_node, 
											   const int& a_depth)
{
	switch(a_depth)
	{
		case 0:
		{
			a_date.year = a_node.label;
			a_date.month = 1;
			a_date.day = 1;
		} break;
		case 1:
		{
			a_date.month = a_node.label;
			a_date.day = 1;
		} break;
		case 2:
		{
			a_date.day = a_node.label;
			a_date.hour = 0;
		} break;
		case 3:
		{
			a_date.hour = a_node.label;
		} break;
	}	
}

int TimeSerieTreeFormatter::treeDepthFromPeriodType(const PeriodType& a_periodType)
{
	int result = 0;
	switch (a_periodType)
	{
		case MONTHLY_TYPE:
		{
			result = 1;
		} break;
		case DAILY_TYPE:
		{
			result = 2;
		} break;
		case HOURLY_TYPE:
		{
			result = 3;
		} break;
	}
	return result;
}
