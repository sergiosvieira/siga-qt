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
#include "../../include/data-structures/time-serie-tree-formatter.h"

/** SIGA **/
#include "../../include/utils/string-utils.h"
#include "../../include/data-structures/tree-node.h"

using namespace SIGA::DS;


/** Public Methods **/
//TimeSerieTreeFormatter::MatrixOfString TimeSerieTreeFormatter::matrix(TimeSerieTree& tree,
//                                              const Input& options)
//{
//    MatrixOfString result;
//    tree.sortValues();
//    for (tree<TreeNode>::pre_order_iterator it = tree.begin();
//		 it != a_tree.end();
//		 ++it)
//	{
//		TreeNode& node = *it;
//	}
//	return result;
//}

TimeSerieTreeFormatter::MatrixOfString TimeSerieTreeFormatter::serie(TimeSerieTree& tsTree,
                                                                     const TypeFormatSeparatorInput &options,
                                                                     std::function<bool(long, long)> a_progress)
{	
    MatrixOfString result;
    PeriodType type = get<0>(options);
    string dateFormat = get<1>(options);
    string separator = get<2>(options);
    result.push_back(tsTree.stationLabels());
    tsTree.sortValues();
    int stopTreeDepth = treeDepthFromPeriodType(type);
    long total = tsTree.size() * tsTree.stationsLength();
    long currentProgress = 0;
    for (tree<TreeNode>::pre_order_iterator it = tsTree.begin();
         it != tsTree.end();
		 ++it)
	{
		TreeNode& node = *it;
        int currentDepth = tsTree.depth(it);
		if (currentDepth == stopTreeDepth)
		{						
            CDate date = dateFromTreeDepth(node, currentDepth);
			std::vector<std::string> rowVector;
            rowVector.push_back(date.ToStringWithFormat(dateFormat));
            for (int index = 0; index < tsTree.stationsLength(); ++index)
			{               
                float value = node.value(0, index);
                string valueString = std::to_string(value);
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
CDate TimeSerieTreeFormatter::dateFromTreeDepth(const TreeNode& node,
                                                const int& depth)
{
    CDate result;
    switch(depth)
	{
		case 0:
		{
            result = CDate(node.label(), 1, 1);
		} break;
		case 1:
		{
            result = CDate(0, node.label(), 1);
		} break;
		case 2:
		{
            result = CDate(0, 0, node.label());
		} break;
		case 3:
		{
            result = CDate(0, 0, 0);
		} break;
	}	
}

int TimeSerieTreeFormatter::treeDepthFromPeriodType(const PeriodType& a_periodType)
{
	int result = 0;
	switch (a_periodType)
	{
        case PeriodType::MONTHLY_TYPE:
		{
			result = 1;
		} break;
        case PeriodType::DAILY_TYPE:
		{
			result = 2;
		} break;
        case PeriodType::HOURLY_TYPE:
		{
			result = 3;
		} break;
	}
	return result;
}
