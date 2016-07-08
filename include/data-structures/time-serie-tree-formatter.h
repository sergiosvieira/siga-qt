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

#ifndef __TIME_SERIE_TREE_FORMATTER__
#define __TIME_SERIE_TREE_FORMATTER__

/** SIGA **/
#include "SIGA/SigaConverter/TimeSerieTree.h"
#include "SIGA/import-types.h"

/** STL **/
#include <vector>
#include <string>
#include <functional>

class TimeSerieTreeFormatter
{
public:
	/*! InputStructure
	 *  \param PeriodType (NONE = 0x0000, HOURLY_TYPE  = 0x1111, DAILY_TYPE  = 0x0111, MONTHLY_TYPE  = 0x0011, YEARLY_TYPE  = 0x0001)
	 *  \param DateFormat - std::string (Examples: dd/mm/yyyy, mm/yyyy, yyyy)
	 *  \param Field Separator - std::string (Examples: "," "\t")
	 */
	typedef struct InputStructure
	{
		// PeriodType (NONE = 0x0000, HOURLY_TYPE  = 0x1111, DAILY_TYPE  = 0x0111, MONTHLY_TYPE  = 0x0011, YEARLY_TYPE  = 0x0001)
		PeriodType periodType;
		std::string dateFormat;
		std::string fieldSeparator;
		InputStructure():periodType(DAILY_TYPE),
						 dateFormat("yyy-mm-dd"),
						 fieldSeparator("\t"){};					
		InputStructure(PeriodType a_periodType,
					   std::string a_dateFormat,
					   std::string a_fieldSeparator):
					   periodType(a_periodType),
					   dateFormat(a_dateFormat),
					   fieldSeparator(a_fieldSeparator){};
	} InputStructure;
	static std::vector<std::vector<std::string>> matrix(TimeSerieTree& a_tree,
														const InputStructure& a_inputOptions);
	static std::vector<std::vector<std::string>> serie(TimeSerieTree & a_tree, 
												const InputStructure & a_inputOptions, 
												std::function<bool(long, long)> a_progress);
private:
	typedef struct DateStruct
	{
		int hour;
		int day;
		int month;
		int year;
	} DateStructure;
	typedef std::function<void(std::string)> ValueFunction;
	static void dateFromTreeDepth(DateStructure& a_date, 
								  const TreeNode& a_node, 
								  const int& a_depth);
	static int treeDepthFromPeriodType(const PeriodType& a_periodType);
};

#endif /** __TIME_SERIE_TREE_FORMATTER__ **/
